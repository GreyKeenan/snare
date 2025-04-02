#ifndef ATOLL_point
#define ATOLL_point

#include <stdint.h>

struct atoll_point { uint16_t x, y; };
// NOTE: macro check in diagram.c expects sizeof(this) == 4

#endif
