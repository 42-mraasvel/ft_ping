#include "ft_ping.h"
#include <stdlib.h>
#include <stdio.h>

static Result result_construct(const char* message, bool owned, ResultType type) {
	Result result;
	result.message = message;
	result.owned_string = owned;
	result.type = type;
	return result;
}

Result result_success() {
	return result_construct(NULL, false, Success);
}

Result result_owned(ResultType result, const char* s) {
	return result_construct(s, true, result);
}

Result result_borrowed(ResultType result, const char* s) {
	return result_construct(s, false, result);
}

ResultType result_log_and_destroy(Result* result) {
	if (result->message) {
		fprintf(stderr, "%s\n", result->message);
	}
	ResultType type = result->type;
	result_destroy(result);
	return result->type;
}

void result_destroy(Result* result) {
	if (result->owned_string) {
		free((void*)result->message);
	}
}
