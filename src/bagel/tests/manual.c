
#include "../xorshiftr128plus.h"

#include <stdio.h>
#include <inttypes.h>

int main() {

	struct Bagel_xorshiftr128plus rstate = Bagel_xorshiftr128plus_seed(1);

	printf("%"PRIu64"\n", Bagel_xorshiftr128plus_run(&rstate));

	return 0;
}
