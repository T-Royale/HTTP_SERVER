#pragma once

#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

#include <stdlib.h>
#include <stdio.h>
#include "tcp.h"

#define debug_log(...) printf(__VA_ARGS__);