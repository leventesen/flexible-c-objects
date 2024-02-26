#ifndef __COMMON_H__
#define __COMMON_H__

#include "../lib/fco.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define TEST_PASS() do { puts("Test passed"); exit(0); } while (0)
#define TEST_FAIL() do { printf(__func__); puts(" failed"); exit(1); } while (0)

#endif