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

static inline void Orphans_half_append(struct Orphans_half *halves, unsigned int head, unsigned int tail)
/*
	assumes:
		head & tail are valid indices to the array at *halves

	if the linked list from head is only 1 element long,
	head.prev == head.next == head
*/
{
	halves[tail].next = head;
	halves[tail].prev = halves[head].prev;

	halves[halves[head].prev].next = tail;
	halves[head].prev = tail;
}


#endif
