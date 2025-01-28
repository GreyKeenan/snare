
#include "point.h"

int Chalk_Point_compL_y(const void *a, const void *b)
{
	return ((struct Chalk_Point *)a)->y - ((struct Chalk_Point *)b)->y;
}
int Chalk_Point_compG_y(const void *a, const void *b)
{
	return ((struct Chalk_Point *)b)->y - ((struct Chalk_Point *)a)->y;
}
int Chalk_Point_compL_x(const void *a, const void *b)
{
	return ((struct Chalk_Point *)a)->x - ((struct Chalk_Point *)b)->x;
}
int Chalk_Point_compG_x(const void *a, const void *b)
{
	return ((struct Chalk_Point *)b)->x - ((struct Chalk_Point *)a)->x;
}
