#include "./coast.h"

#include "gu/gu.h"


void atoll_coast_reset(struct atoll_coast *self)
{
	if (self == NULL) return;

	gu_free(self->beach);
	gu_free(self->circles);

	*self = (struct atoll_coast){0};
}


void atoll_coast_updateCircleIndices(struct atoll_coast self[static 1], unsigned int from, int by)
{
	for (unsigned int i = 0; i < self->circles_length; ++i) {
		if (self->circles[i].closing_arc < from) {
			continue;
		}
		self->circles[i].closing_arc += by;
	}
}
