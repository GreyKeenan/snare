#ifndef ORPHANS_half
#define ORPHANS_half

struct Orphans_edge {
	unsigned int vertex[2];
};

struct Orphans_half {
	unsigned int cell;

	unsigned int prev;
	unsigned int next;

	unsigned int edge;
};

static inline unsigned int Orphans_half_opposite(unsigned int index)
{
	return index + (index % 2)? -1:1;
}

#endif
