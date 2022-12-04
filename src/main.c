#include "parse_args.h"
#include <stdio.h> //TODO: remove

int main(int argc, const char *argv[]) {
	argc--; argv++;
	Arguments args;
	Result r = parse_args(argc, argv, &args);
	if (r.type != Success) {
		return (int)result_log_and_destroy(&r);
	}

	printf("Host: %s\n", args.host);
	for (int i = 0; i < 255; i++) {
		if (args.options[i]) {
			printf("Option enabled: %c\n", i);
		}
	}
	printf("Sweep increment size: %d\n", args.sweep_incr_size);

	return 0;
}
