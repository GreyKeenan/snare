#ifndef ORPHANS_halfedge
#define ORPHANS_halfedge

struct Orphans_halfedge {
	unsigned int cell;

	unsigned int prev;
	unsigned int next;

	unsigned int vertex[2];
};

static inline unsigned int Orphans_halfedge_other(unsigned int index)
{
	return index + (index % 2)? -1:1;
}

#endif
