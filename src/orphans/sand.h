#ifndef ORPHANS_Sand
#define ORPHANS_Sand


#include <stdbool.h>


struct Dot;

struct Orphans_Sand {
	unsigned int site_index;
	struct Dot *destinations[2];
};


static inline bool Orphans_Sand_isNull(const struct Orphans_Sand self[static 1])
{
	return self->destinations[0] == NULL;
}


#endif
