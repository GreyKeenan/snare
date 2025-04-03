#ifndef ATOLL_point
#define ATOLL_point

#include <stdint.h>

struct atoll_point { int16_t x, y; };
// NOTE: macro check in diagram.c expects sizeof(this) == 4

struct atoll_podouble { double x, y; };

#endif
