#ifndef FT_PING_H
#define FT_PING_H

#include <stdbool.h>

typedef enum ResultType {
	Success = 0,
	InvalidArgument
} ResultType;

typedef struct Result {
	const char* message;
	ResultType type;
	bool owned_string;
} Result;

Result result_success();
Result result_owned(ResultType result, const char* s);
Result result_borrowed(ResultType result, const char* s);
void result_destroy(Result* result);
ResultType result_log_and_destroy(Result* result);

void abort_program(const char* s);
void* malloc_check(void* p);

#endif
