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

static inline void Fortune_half_append(struct Fortune_half * /*nonull*/ halves, unsigned int head, unsigned int tail)
{
	halves[tail].next = head;
	halves[tail].previous = halves[head].previous;

	halves[halves[head].previous].next = tail;
	halves[head].previous = tail;
}

#endif
