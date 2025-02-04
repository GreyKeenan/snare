#ifndef DOT_dot
#define DOT_dot

#include <stdint.h>
#include <stdbool.h>


#define Dot_BUILD_intradotmath(name, operator) \
	static inline int Dot_##name(const struct Dot d) \
	{ \
		return d.x operator d.y; \
	}

#define Dot_BUILD_interdotmath(name, operator) \
	static inline struct Dot Dot_##name(const struct Dot a, const struct Dot b) \
	{ \
		return (struct Dot) { \
			.x = a.x operator b.x, \
			.y = a.y operator b.y \
		}; \
	}


struct Dot { int16_t x, y; };


Dot_BUILD_intradotmath(sum, +)
Dot_BUILD_intradotmath(difference, -)
Dot_BUILD_intradotmath(product, *)
Dot_BUILD_intradotmath(quotient, /)
Dot_BUILD_intradotmath(remainder, %)

static inline struct Dot Dot_fakeout(const struct Dot d)
{
	return (struct Dot) {
		.x = d.y,
		.y = d.x
	};
}

Dot_BUILD_interdotmath(add, +)
Dot_BUILD_interdotmath(subtract, -)
Dot_BUILD_interdotmath(multiply, *)
Dot_BUILD_interdotmath(divide, /)
Dot_BUILD_interdotmath(modulo, %)

static inline bool Dot_equals(const struct Dot a, const struct Dot b)
{
	return a.x == b.x && a.y == b.y;
}

static inline int Dot_cross(const struct Dot a, const struct Dot b)
{
	return a.x * b.y - a.y * b.x;
}
static inline int Dot_dotprod(const struct Dot a, const struct Dot b)
{
	return Dot_sum(Dot_multiply(a, b));
}


#endif
