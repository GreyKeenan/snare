#ifndef FORTUNE_half
#define FORTUNE_half

struct Fortune_edge {
	unsigned int head; // indices to vertices
	unsigned int tail;
};

struct Fortune_half {
	unsigned int cell;
	unsigned int edge; //index of an edge

	unsigned int previous;
	unsigned int next;
};

static inline unsigned int Fortune_half_opposite(unsigned int of)
{
	return of + (of % 2)? -1:1;
}

#endif
