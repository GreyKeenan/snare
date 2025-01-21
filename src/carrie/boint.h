#ifndef CARRIE_boint_H
#define CARRIE_boint_H

/*
A "boint" is a 4bit signed (x,y) pair packed into a single byte.
It is not meant for doing operations on the boint.

It is in the form `xxxXYyyy`, where the capital letters are the sign bits.
*/

#define Carrie_boint_MAX 7
#define Carrie_boint_MIN -7

static inline signed char Carrie_boint_x(const unsigned char boint)
{
	return (boint >> 5) * ((boint & 0x10)? -1: 1);
}
static inline signed char Carrie_boint_y(const unsigned char boint)
{
	return (boint & 0x07) * ((boint & 0x08)? -1 : 1);
}
static inline unsigned char Carrie_boint_set_x(const unsigned char boint, const signed char x)
{
	return (boint & 0x0f) | ((x << 5) & ((x < 0)? 0x10 : 0));
}
static inline unsigned char Carrie_boint_set_y(const unsigned char boint, const signed char y)
{
	return (boint & 0xf0) | ((y & 0x07) & ((y < 0)? 0x08 : 0));
}

#endif
