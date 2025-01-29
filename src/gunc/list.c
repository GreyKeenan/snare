#include "./list.h"

#include <limits.h>
#include <stdint.h>

int Gunc_list_expand(
	void *data,
	size_t item_size,
	unsigned int *allocation_length
)
{
	if (*allocation_length == UINT_MAX) {
		return Gunc_list_MAX;
	}

	unsigned int newmax = *allocation_length << 1;
	if (newmax < *allocation_length) {
		newmax = UINT_MAX;
	}

	if (newmax > SIZE_MAX / item_size) {
		return Gunc_list_MAX;
	}
	void *newdata = realloc(*(void**)data, newmax * item_size);
	if (newdata == NULL) {
		return Gunc_list_ALLOCFAIL;
	}

	*(void**)data = newdata;
	*allocation_length = newmax;

	return 0;
}
