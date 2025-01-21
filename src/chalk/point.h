#ifndef CHALK_Point_H
#define CHALK_Point_H

struct Chalk_Point {
	short x, y;
};

static inline _Bool Chalk_Point_equal(const struct Chalk_Point a, const struct Chalk_Point b) {
	return (a.x == b.x) && (a.y == b.y);
}

#endif
