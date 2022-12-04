#include <stdlib.h>
#include <stdio.h>

void abort_program(const char* s) {
	perror(s);
	exit(EXIT_FAILURE);
}

void* malloc_check(void* p) {
	if (!p) {
		abort_program("malloc");
	}
	return p;
}
