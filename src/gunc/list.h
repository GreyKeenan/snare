#ifndef GUNC_List
#define GUNC_List

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct Gunc_List {
	uint8_t *data;
	unsigned int length;
	unsigned int cap;
	size_t item_size;
};


int Gunc_List_init(struct Gunc_List *self, size_t item_size, unsigned int initial_allocation);
int Gunc_List_expand(struct Gunc_List *self);
static inline void Gunc_List_destroy(struct Gunc_List *self)
{
	if (self->data != NULL) {
		free(self->data);
	}
	*self = (struct Gunc_List){ .data = NULL };
}

static inline int Gunc_List_trim(struct Gunc_List *self)
{
	void *newdata = realloc(self->data, self->length * self->item_size);
	if (newdata == NULL) {
			return 2;
	}

	self->data = newdata;
	self->cap = self->length;

	return 0;
}

static inline int Gunc_List_add(struct Gunc_List *self, const void *item)
{
	int e = 0;

	if (self->length >= self->cap) {
		e = Gunc_List_expand(self);
		if (e) {
			return 2;
		}
	}

	memcpy(self->data + (self->length * self->item_size), item, self->item_size);
	self->length++;

	return 0;
}

static inline void *Gunc_List_access(const struct Gunc_List * self, unsigned int index)
{
	if (index >= self->length) {
		return NULL;
	}
	return self->data + (index * self->item_size);
}

/*
static inline int Gunc_List_get(const struct Gunc_List *self, unsigned int index, void *item)
{
	if (index >= self->length) {
		return 2;
	}

	memcpy(item, self->data + (self->length * self->item_size), self->item_size);

	return 0;
}
*/

#endif
