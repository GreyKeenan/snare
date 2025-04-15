#include "./cvpoly.h"

#include "./triangle.h"

#include <math.h>

// ==========

double gumetry_cvpoly_area(const struct gumetry_point * restrict /*nonull*/ vertices, unsigned int vertex_count)
{
	//naive triangulation of convex vertices
	//a triangle is vertices[0], vertices[i], vertices[i - 1], i >= 2
	double total = 0;
	for (unsigned int i = 2; i < vertex_count; ++i) {
		total += gumetry_triangle_area(vertices[0], vertices[i], vertices[i - 1]);
	}
	return total;
}

int gumetry_cvpoly_rpoints(
	const struct gumetry_point * restrict /*nonull*/ vertices,
	unsigned int vertex_count,
	struct gumetry_point * restrict /*nonull*/ output,
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
			output[i] = gumetry_triangle_rpoint(
				vertices[0], vertices[2], vertices[1],
				sqrt(gu_zerothroughone(r(rstate))),
				gu_zerothroughone(r(rstate))
			);
		}
		return 0;
	}

	//naive triangulation of convex vertices
	//a triangle is vertices[0], vertices[i], vertices[i - 1], i >= 2

	uint64_t total_area = 0;
	uint16_t denominator = 1;
	unsigned int shift = 1;
	uint64_t area = 0;
	do {
		for (unsigned int i = 2; i < vertex_count; ++i) {
			area = gumetry_triangle_area(vertices[0], vertices[i], vertices[i - 1]) / denominator;
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
			area = gumetry_triangle_area(vertices[0], vertices[it], vertices[it - 1]) / denominator;
			if (rn < area) {
				output[ip] = gumetry_triangle_rpoint(
					vertices[0], vertices[it], vertices[it - 1],
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

