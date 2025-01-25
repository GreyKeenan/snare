#include "random.h"

#include "bagel/bagel.h"
#include "bagel/xorshiftr128plus.h"

#include <stdlib.h>
#include <math.h>

int Chalk_randomPoints_cvpoly(
	const struct Chalk_Point *poly,
	unsigned int vertices,
	struct Chalk_Point *destination, //where to write points to
	unsigned int points, //how many points to generate
	struct Bagel_xorshiftr128plus *randomizer
)
{
	if (poly == NULL || destination == NULL || vertices < 3) {
		return 2;
	}

	if (vertices == 3) {
		for (unsigned int i_p = 0; i_p < points; ++i_p) {
			destination[i_p] = Chalk_randomPointInTriangle(
				poly[0], poly[1], poly[2],
				sqrt(Bagel_zeroThroughOne(Bagel_xorshiftr128plus_run(randomizer))),
				Bagel_zeroThroughOne(Bagel_xorshiftr128plus_run(randomizer))
			);
			break;
		}
		return 0;
	}

	unsigned int *triangle_areas = malloc(sizeof(int) * (vertices - 2));
	if (triangle_areas == NULL) {
		return 4;
	}

	//a triangle is (poly[0],poly[index],poly[index-1]) where index > 1
		//its area is areas[index - 2]
	
	uint64_t total_weight = 0;
	for (unsigned int i = 2; i < vertices; ++i) {
		triangle_areas[i - 2] = Chalk_area_triangle(poly[0], poly[i], poly[i - 1]);

		//if (UINT64_MAX - triangle_areas[i - 2] < total_weight) { return 1; }
		total_weight += (triangle_areas[i - 2]);
	}

	uint64_t r = 0;
	for (unsigned int i_p = 0; i_p < points; ++i_p) {
		r = Bagel_xorshiftr128plus_run(randomizer) % total_weight;

		for (unsigned int i_t = 2; i_t < vertices; ++i_t) {
			if (r < triangle_areas[i_t - 2]) {
				destination[i_p] = Chalk_randomPointInTriangle(
					poly[0], poly[i_t], poly[i_t - 1],
					sqrt(Bagel_zeroThroughOne(Bagel_xorshiftr128plus_run(randomizer))),
					Bagel_zeroThroughOne(Bagel_xorshiftr128plus_run(randomizer))
				);

				break;
			}
			r -= triangle_areas[i_t - 2];
		}
	}



	free(triangle_areas);
	return 0;
}
