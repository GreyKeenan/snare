
#include "../list.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/*
void printList(struct Gunc_List *list) {
	fprintf(stderr,
		"<Gunc_List> %p {"
		"\n\t""data:%p"
		"\n\t""length: %u"
		"\n\t""cap: %u"
		"\n\t""item_size: %zu"
		"\n""}",
		list,
		list->data,
		list->length,
		list->cap,
		list->item_size
	);
}
*/

int main(const int argc, const char **argv) {
	(void)argc;
	(void)argv;

	int e = 0;


	#define STATICLEN (sizeof(staticarr) / sizeof(*staticarr))
	int staticarr[] = { 1, 2, 3, 4, 5 };

	unsigned int length = 0;
	unsigned int allocation = STATICLEN;
	int *arr = malloc(sizeof(int) * allocation);
	if (arr == NULL) {
		printf("allocation failed\n");
		return 1;
	}

	printf("initialized without values!\n");
	printf("length: %d / allocation: %d\n", length, allocation);

	for (unsigned int i = 0; i < STATICLEN; ++i) {
		e = Gunc_push(&arr, &length, &allocation, staticarr + i);
		if (e) {
			printf("push() #%d failed: %d\n", i, e);
			goto fin;
		}
	}

	printf("%zu values entered.\n", STATICLEN);
	printf("length: %d / allocation: %d\n", length, allocation);

	int n = 50;
	e = Gunc_push(&arr, &length, &allocation, &n);
	if (e) {
		printf("additional push() failed: %d\n", e);
		goto fin;
	}
	
	printf("additional push() completed. index %zu should == %d\n", STATICLEN, n);
	printf("length: %d / allocation: %d\n", length, allocation);

	printf("\n""actual array:\n");
	for (unsigned int i = 0; i < length; ++i) {
		printf("%d\n", arr[i]);
	}
	printf("\n");

	int popped = 0;
	while (length > 2) {
		printf("pre-pop: ");
		printf("length: %d / allocation: %d\n", length, allocation);
		e = Gunc_pop(&arr, &length, &popped);
		if (e) {
			e = 0;
			break;
		}

		printf("popped: %d\n", popped);
		printf("length: %d / allocation: %d\n", length, allocation);
		printf("\n");
	}

	e = Gunc_expand(&arr, &allocation);
	if (e) {
		printf("expand() failed: %d\n", e);
	}
	printf("post-expand: ");
	printf("length: %d / allocation: %d\n", length, allocation);

	e = Gunc_fit(&arr, &allocation, length);
	if (e) {
		printf("fit() failed! %d\n", e);
	}
	printf("post-fit (length): ");
	printf("length: %d / allocation: %d\n", length, allocation);

	#define FIT 13
	e = Gunc_fit(&arr, &allocation, FIT);
	if (e) {
		printf("fit() failed! %d\n", e);
	}
	printf("post-fit (%d): ", FIT);
	printf("length: %d / allocation: %d\n", length, allocation);





	fin:

	free(arr);

	return (_Bool)e;
}
