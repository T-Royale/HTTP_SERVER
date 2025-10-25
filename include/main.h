#pragma once

#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <getopt.h>

#define debug_log(...) printf(__VA_ARGS__);