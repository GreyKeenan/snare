#include "./list.h"

#include <limits.h>


int Gunc_List_init(struct Gunc_List *self, size_t item_size, unsigned int initial_allocation)
{
	if (item_size < 1) {
		return 2;
	}

	if (initial_allocation == 0) {
		initial_allocation = 1;
	}

	if (initial_allocation > SIZE_MAX / item_size) {
		return 3;
	}
	uint8_t *newdata = malloc(item_size * initial_allocation);
	if (newdata == NULL) {
		return 4;
	}

	*self = (struct Gunc_List) {
		.data = newdata,
		.cap = initial_allocation,
		.item_size = item_size
	};

	return 0;
}

int Gunc_List_expand(struct Gunc_List *self)
{
	if (self->cap == UINT_MAX) {
		return 2;
	}

	unsigned int newcap = self->cap << 1;
	if (newcap < self->cap) {
		newcap = UINT_MAX;
	}
	
	if (newcap > SIZE_MAX / self->item_size) {
		return 3;
	}
	void *newdata = realloc(self->data, newcap * self->item_size);
	if (newdata == NULL) {
		return 4;
	}

	self->data = newdata;
	self->cap = newcap;

	return 0;
}
