#include "parse_args.h"
#include "ft_ping.h"
#include "libft.h"

typedef struct ArgumentIterator {
	int size;
	int pos;
	const char** argp;
} ArgumentIterator;

static ArgumentIterator args_it_init(int argc, const char** argv) {
	ArgumentIterator it;
	it.size = argc;
	it.pos = 0;
	it.argp = argv;
	return it;
}

static bool args_has_next(ArgumentIterator* it) {
	return it->pos < it->size;
}

static const char* args_next(ArgumentIterator* it) {
	if (!args_has_next(it)) {
		return NULL;
	}
	return it->argp[it->pos++];
}

static const char* args_peek(ArgumentIterator* it) {
	if (!args_has_next(it)) {
		return NULL;
	}
	return it->argp[it->pos];
}

static Result parse_v(const char** option, Arguments* args, ArgumentIterator* it) {
	*option += 1;
	args->options['v'] = true;
	(void)it;
	return result_success();
}

static bool is_numeric_string(const char* s) {
	for (int i = 0; s[i] != '\0'; i++) {
		if (!ft_isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

// if `h` is the last character in the string: next argument should be a number
// if `h` is not the last character the rest of the string should be the number
static Result parse_h(const char** option, Arguments* args, ArgumentIterator* it) {
	*option += 1;
	const char* number;
	if (**option == '\0') {
		if (!args_has_next(it)) {
			return result_borrowed(InvalidArgument, "option requires an argument -- h");
		}
		number = args_next(it);
	} else {
		number = *option;
		// skip the string to the end
		*option += ft_strlen(*option);
	}
	if (!is_numeric_string(number)) {
		char* message = malloc_check(cstr_format("invalid increment size: `%s'", number));
		return result_owned(InvalidArgument, message);
	}
	args->sweep_incr_size = ft_atoi(number);
	args->options['h'] = true;
	return result_success();
}

typedef Result (*OptionParser)(const char**, Arguments*, ArgumentIterator*);

static Result parse_option(const char* option, Arguments* args, ArgumentIterator* it) {
	static const OptionParser parsers[255] = {
		['v'] = parse_v,
		['h'] = parse_h,
	};
	while (*option != '\0') {
		int ch = (unsigned char)*option;
		if (parsers[ch] == NULL) {
			char* message = malloc_check(cstr_format("invalid option -- %c", ch));
			return result_owned(InvalidArgument, message);
		}
		Result r = (parsers[ch])(&option, args, it);
		if (r.type != Success) {
			return r;
		}
	}
	return result_success();
}

#define USAGE_MESSAGE "usage: ping [-v] [-h sweepincrsize] host"

Result parse_args(int argc, const char* argv[], Arguments* args) {
	ft_memset(args->options, false, 255 * sizeof(bool));
	args->host = NULL;
	args->sweep_incr_size = 1;
	ArgumentIterator it = args_it_init(argc, argv);
	while (args_has_next(&it)) {
		const char* arg = args_next(&it);
		if (ft_starts_with(arg, "-")) {
			Result r = parse_option(arg + 1, args, &it);
			if (r.type != Success) {
				return r;
			}
		} else {
			if (args->host != NULL) {
				return result_borrowed(InvalidArgument, USAGE_MESSAGE);
			}
			args->host = arg;
		}
	}
	if (args->host == NULL) {
		return result_borrowed(InvalidArgument, USAGE_MESSAGE);
	}
	return result_success();
}
