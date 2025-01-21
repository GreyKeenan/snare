
#include "./point.h"
#include "./chalk.h"
#include "./rat.h"

#include <stdio.h>

int main() {

	struct Chalk_Point origin = { 0, 1 };
	struct Chalk_Point slope = { 6, 3 };

	short max_x = 6;

	struct Chalk_Rat rat;
	Chalk_Rat_init(&rat, origin, slope);

	struct Chalk_Point ratted;
	for (int i = 0; i < max_x; ++i) {
		printf("(%d, %d)\n", rat.at.x, rat.at.y);
		Chalk_Rat_step(&rat);
	}
}
