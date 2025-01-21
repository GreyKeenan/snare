
#include "./point.h"
#include "./chalk.h"
#include "./rat.h"

#include <stdlib.h>
#include <stdio.h>

int main() {

	struct Chalk_Point bounds = {25,25};

	struct Chalk_Point south = {24,23};
	struct Chalk_Point north = {15,3};

	struct Chalk_Rat rat;
	Chalk_Rat_init(&rat, south, north);

	char *outstr = malloc(bounds.x * bounds.y);

	if (outstr == NULL) {
		printf("error: cant malloc\n");
		return 1;
	}

	for (int i = 0; i < bounds.x * bounds.y; ++i) {
		outstr[i] = '-';
	}

	outstr[rat.at.y * bounds.y + rat.at.x] = '(';
	// skipping check for if south == north
	struct Chalk_Point ratted;
	for (int i = 0; i < 100; ++i) {

		ratted = Chalk_Rat_step(&rat);
		outstr[ratted.y * bounds.y + ratted.x] = i + '0';

		printf("at: (%d, %d) gave: (%d, %d)\n", rat.at.x, rat.at.y, ratted.x, ratted.y);

		if (Chalk_Point_equal(ratted, north)) {
			outstr[ratted.y * bounds.y + ratted.x] = ')';
			break;
		}
	}

	for (int iy = bounds.y - 1; iy >= 0; --iy) {
		for (int ix = 0; ix < bounds.x; ++ix) {
			printf(" %c", outstr[iy * bounds.y + ix]);
		}
		printf("\n");
	}

	free(outstr);
}
