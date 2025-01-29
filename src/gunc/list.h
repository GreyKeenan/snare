#ifndef GUNC_list
#define GUNC_list

#include <stdlib.h>
#include <string.h>

enum Gunc_list_error {
	Gunc_list_MAX = 1
	, Gunc_list_ALLOCFAIL
};

#define Gunc_expand(data, allocation_length) \
	Gunc_list_expand((data), sizeof(**(data)), (allocation_length))

#define Gunc_fit(data, allocation_length, cap) \
	Gunc_list_fit((data), sizeof(**(data)), (allocation_length), cap)

#define Gunc_push(data, length, allocation_length, item) \
	Gunc_list_push((data), sizeof(**(data)), (length), (allocation_length), (item))

#define Gunc_pop(data, length, nItem) \
	Gunc_list_pop((data), sizeof(**(data)), (length), (nItem))

int Gunc_list_expand(
	void *data, // item**
	size_t item_size,
	unsigned int *allocation_length
);

static inline int Gunc_list_fit(
	void *data,
	size_t item_size,
	unsigned int *allocation_length,
	unsigned int cap
)
{
	void *newdata = realloc(*(void**)data, cap * item_size);
	if (newdata == NULL) {
		return Gunc_list_ALLOCFAIL;
	}

	*(void**)data = newdata;
	*allocation_length = cap;

	return 0;
}

static inline int Gunc_list_push(
	void *data, // item**
	size_t item_size,
	unsigned int *length,
	unsigned int *allocation_length,
	void *item
)
{
	int e;
	if (*length >= *allocation_length) {
		e = Gunc_list_expand(data, item_size, allocation_length);
		if (e) {
			return e;
		}

		/*
		if (*length >= *allocation_length) {
			return ASSUMES_THIS_WONT_HAPPEN_SINCE_WOULD_BE_EARLIER_ERROR
		}
		*/
	}

	memcpy(*(char**)data + (*length * item_size), item, item_size);
	*length += 1;

	return 0;
}

static inline int Gunc_list_pop(
	const void *data, // item**
	size_t item_size,
	unsigned int *length,
	void *nItem
)
{
	if (*length == 0) {
		return Gunc_list_MAX;
	}

	*length -= 1;

	if (nItem == NULL) {
		return 0;
	}

	memcpy(nItem, *(char*const*)data + (*length * item_size), item_size);

	return 0;
}


#endif
