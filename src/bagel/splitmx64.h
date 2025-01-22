#ifndef BAGEL_splitmx64
#define BAGEL_splitmx64

#include <stdint.h>

static inline uint64_t Bagel_splitmx64(uint64_t s[static 1])
{
	*s += 0x9e779b97f4a7c15;
	uint64_t result = *s;
	result ^= (result >> 30) * 0xbf58476d1ce4e5b9;
	result ^= (result >> 27) * 0x94d049bb133111eb;
	result ^= result >> 31;
	return result;
}

#endif
