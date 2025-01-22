#ifndef CARRIE_boint_H
#define CARRIE_boint_H

#define Carrie_boint_MAX 7

static inline signed char Carrie_boint_x(const unsigned char boint)
{
	return (
		Carrie_boint_MAX
	) * ((boint & 0x20)? -1: 1);
}
static inline signed char Carrie_boint_y(const unsigned char boint)
{
	return (
		Carrie_boint_MAX
	) * ((boint & 0x01)? -1 : 1);
}


/*

000000XY

*/

#endif
