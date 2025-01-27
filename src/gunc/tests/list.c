
#include "../list.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

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


int main(const int argc, const char **argv) {
	(void)argc;
	(void)argv;

	int e = 0;

	struct Gunc_List list = {0};
	e = Gunc_List_init(&list, sizeof(int), 0);
	if (e) {
		fprintf(stderr, "_init() failed: %d\n", e);
		goto fin;
	}

	printList(&list);
	fprintf(stderr, "\n");

	int i = 556;
	e = Gunc_List_add(&list, &i);
	if (e) {
		fprintf(stderr, "_add(%d) failed: %d\n", i, e);
		goto fin;
	}

	printList(&list);
	fprintf(stderr, "\n");

	int *p = Gunc_List_access(&list, 0);
	if (p == NULL) {
		fprintf(stderr, "access( ) failed\n");
		e = 1;
		goto fin;
	}
	fprintf(stderr, "List[%p]: %d\n", p, *p);

	i = 789;
	e = Gunc_List_add(&list, &i);
	if (e) {
		fprintf(stderr, "_add(%d) failed: %d\n", i, e);
		goto fin;
	}

	printList(&list);
	fprintf(stderr, "\n");

	p = Gunc_List_access(&list, 1);
	if (p == NULL) {
		fprintf(stderr, "access( ) failed\n");
		e = 1;
		goto fin;
	}
	fprintf(stderr, "List[%p]: %d\n", p, *p);

	fin:

	return (_Bool)e;
}
