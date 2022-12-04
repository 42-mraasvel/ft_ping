#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#include "ft_ping.h"
#include "stdbool.h"

typedef struct Arguments {
	bool options[255];
	const char* host;
	int sweep_incr_size;
} Arguments;

Result parse_args(int argc, const char* argv[], Arguments* args);

#endif
