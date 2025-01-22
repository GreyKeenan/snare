#ifndef BAGEL_Bagel
#define BAGEL_Bagel

#include <stdint.h>

static inline double Bagel_zeroThroughOne(const uint64_t i)
{
	return i / (0x8000000000000000u * 2.0);
}

#endif
