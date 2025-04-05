#ifndef ATOLL_treasure
#define ATOLL_treasure


struct atoll_diagram;
struct atoll_coast;

struct gu_echo;


/*heap*/ struct gu_echo *atoll_treasure(struct atoll_diagram * /*nonull*/ diagram, struct atoll_coast * /*nonull*/ coast);
/*
assumes:
	the diagram & coast have been initialized

An implementation of fortune's algorithm.

* does *not* terminate infinite edges.
  Call <TODO> for that.
* None of the sub-functions have any special floating-point-rounding protection,
  so it is recommended to keep the input sites fairly small, perhaps within an int8_t.

*/

#endif
