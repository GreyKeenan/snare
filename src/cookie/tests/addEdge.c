
#include "chalk/point.h"
#include "gunc/list.h"

#include <stdio.h>
#include <stdlib.h>

int Cookie_addEdgeEvent(struct Chalk_Point point, struct Chalk_Point **list, unsigned int *length, unsigned int *allocation);

int main(void)
{
	int e = 0;


	unsigned int length = 0;
	unsigned int allocation = 1;
	struct Chalk_Point *data = malloc(sizeof(*data) * allocation);
	if (data == NULL) {
		printf("alloc failed\n");
		goto fin;
	}

	#define NSTATIC 10
	struct Chalk_Point staticarr[] = {
		(struct Chalk_Point) { 28, -1 },
		(struct Chalk_Point) { 25, 0 },
		(struct Chalk_Point) { 22, 1 },
		(struct Chalk_Point) { 22, 2 },
		(struct Chalk_Point) { 19, 11 },
		(struct Chalk_Point) { 15, 4 },
		(struct Chalk_Point) { 11, 5 },
		(struct Chalk_Point) { 7, 4 },
		(struct Chalk_Point) { 4, 7 },
		(struct Chalk_Point) { 1, 5 },
	};

	for (int i = 0; i < NSTATIC; ++i) {
		e = Gunc_push(&data, &length, &allocation, staticarr + i);
		if (e) {
			printf("push failed %d %d\n", i, e);
			goto fin;
		}
	}

	struct Chalk_Point add = { 17, 100 };
	e = Cookie_addEdgeEvent(add, &data, &length, &allocation);
	if (e) {
		printf("addEvent() failed: %d\n", e);
		goto fin;
	}
	printf("\n""added (%d, %d)\n""\n", add.x, add.y);
	for (unsigned int i = 0; i < length; ++i) {
		printf("(%d, %d)\n", data[i].x, data[i].y);
	}



	fin:

	if (data != NULL) {
		free(data);
	}

	return (_Bool)e;
}
