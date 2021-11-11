#include "sxc_point.h"

int sxc_point_cmp(const struct SXC_Point* a, const struct SXC_Point* b)
{
	if (a->x < b->x)	// sort left to right first
		return -1;
	else if (b->x < a->x)
		return 1;
	else if (a->y < b->y)	// x's are equal, sort top to bottom
		return -1;
	else if (b->y < a->y)
		return 1;
	else
		return 0;	// the points are equal!
}

