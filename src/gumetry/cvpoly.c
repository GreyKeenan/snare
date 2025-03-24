#include "./cvpoly.h"

#include "./triangle.h"

#include <math.h>

// ==========

double gumetry_cvpoly_area(const double * restrict /*nonull*/ vertices, unsigned int vertex_count)
{
	if (vertex_count < 3) return -1;
	if (vertex_count == 3) return gumetry_triangle_area(vertices, vertices + 2, vertices + 4);

	//naive triangumetrylation of convex vertices
	//a triangle is vertices[0], vertices[2i], vertices[2(i - 1)]; i >= 1
	double total = 0;
	for (unsigned int i = 2; i < vertex_count; ++i) {
		total += gumetry_triangle_area(
			vertices, vertices + (2 * i), vertices + (2 * (i - 1))
		);
	}

	return total;
}

int gumetry_cvpoly_rpoints(
	const double * restrict /*nonull*/ vertices,
	unsigned int vertex_count,
	double * restrict /*nonull*/ output,
	unsigned int points,
	void *rstate, gu_randomizer r
)
{
	if (vertices == NULL
		|| vertex_count < 3
		|| output == NULL
		|| points == 0
		|| r == NULL
	) { return 2; }

	if (vertex_count == 3) {
		for (unsigned int i = 0; i < points; ++i) {
			gumetry_triangle_rpoint((output + i * 2),
				vertices, vertices + 2, vertices + 4,
				sqrt(gu_zerothroughone(r(rstate))),
				gu_zerothroughone(r(rstate))
			);
		}
		return 0;
	}

	//naive triangulation of convex vertices
	//a triangle is vertices[0], vertices[2i], vertices[2(i - 1)]; i >= 1

	uint64_t total_area = 0;
	uint64_t denominator = 1;
	unsigned int shift = 1;
	uint64_t area = 0;
	do {
		for (unsigned int i = 2; i < vertex_count; ++i) {
			area = gumetry_triangle_area(
				vertices, vertices + (2 * i), vertices + (2 * (i - 1))
				) / denominator;
			if (area > UINT64_MAX - total_area) {
				denominator <<= shift;
				if (denominator == 0) return 3;
				shift *= 2;
				total_area = 0;
				break;
			}
			total_area += area;
		}
	} while (total_area == 0);

	uint64_t rn = 0;
	for (unsigned int ip = 0; ip < points; ++ip) {
		rn = r(rstate) % total_area;

		for (unsigned int it = 2; it < vertex_count; ++it) {
			area = gumetry_triangle_area(
				vertices, vertices + (2 * it), vertices + (2 * (it - 1))
				) / denominator;
			if (rn < area) {
				gumetry_triangle_rpoint((output + ip * 2),
					vertices, vertices + (2 * it), vertices + (2 * (it - 1)),
					sqrt(gu_zerothroughone(r(rstate))),
					gu_zerothroughone(r(rstate))
				);
				break;
			}

			rn -= area;
		}
	}
	
	return 0;
}

