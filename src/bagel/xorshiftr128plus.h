#ifndef BAGEL_xorshiftr128plus
#define BAGEL_xorshiftr128plus

#include "./splitmx64.h"

struct Bagel_xorshiftr128plus {
	uint64_t x, y;
};

static inline struct Bagel_xorshiftr128plus Bagel_xorshiftr128plus_seed(uint64_t seed)
{
	return (struct Bagel_xorshiftr128plus) {
		.x = Bagel_splitmx64(&seed),
		.y = Bagel_splitmx64(&seed)
	};
}
static inline uint64_t Bagel_xorshiftr128plus_run(struct Bagel_xorshiftr128plus state[static 1])
{
	uint64_t x = state->x;
	state->x = state->y;
	
	x ^= x << 23;
	x ^= x >> 17;
	x ^= state->y;

	state->y += x;

	return x;
}

#endif
