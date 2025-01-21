
#include "./point.h"
#include "./chalk.h"
#include "./rat.h"

#include <stdlib.h>
#include <stdio.h>

int main() {

	struct Chalk_Point bounds = { 10, 10 };

	struct Chalk_Point south = {9,9};
	struct Chalk_Point north = {3,5};

	struct Chalk_Rat rat;
	Chalk_Rat_init(&rat, south, north);

	char *outstr = malloc(bounds.x * bounds.y);

	if (outstr == NULL) {
		printf("error: cant malloc\n");
		return 1;
	}

	for (int i = 0; i < bounds.x * bounds.y; ++i) {
		outstr[i] = '.';
	}

	struct Chalk_Point ratted;
	for (int i = 0; i < 100; ++i) {

		outstr[rat.at.y * bounds.y + rat.at.x] = i + '0';
		printf("(%d, %d)\n", rat.at.x, rat.at.y);

		if (Chalk_Point_equal(rat.at, north)) {
			break;
		}
		Chalk_Rat_step(&rat);
	}

	for (int iy = bounds.y - 1; iy >= 0; --iy) {
		for (int ix = 0; ix < bounds.x; ++ix) {
			printf(" %c", outstr[iy * bounds.y + ix]);
		}
		printf("\n");
	}

	free(outstr);
}
