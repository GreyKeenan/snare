
#include "./dot.h"


int Dot_sort_x_ascending(const void * restrict /*nonull*/ a, const void * restrict /*nonull*/ b)
{
	return ((const struct Dot*)a)->x - ((const struct Dot*)b)->x;
}
int Dot_sort_x_descending(const void * restrict /*nonull*/ a, const void * restrict /*nonull*/ b)
{
	return ((const struct Dot*)b)->x - ((const struct Dot*)a)->x;
}
int Dot_sort_y_ascending(const void * restrict /*nonull*/ a, const void * restrict /*nonull*/ b)
{
	return ((const struct Dot*)a)->y - ((const struct Dot*)b)->y;
}
int Dot_sort_y_descending(const void * restrict /*nonull*/ a, const void * restrict /*nonull*/ b)
{
	return ((const struct Dot*)b)->y - ((const struct Dot*)a)->y;
}
