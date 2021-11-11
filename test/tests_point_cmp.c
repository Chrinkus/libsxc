#include <stdlib.h>
#include <assert.h>

#include "sxc_point.h"

int main()
{
	struct SXC_Point p1 = { 0, 0 };
	struct SXC_Point p2 = { -5, 2 };
	struct SXC_Point p3 = { -5, -1 };
	struct SXC_Point p4 = { 7, -7 };
	struct SXC_Point p5 = { -5, 2 };

	assert(sxc_point_cmp(&p1, &p2) > 0);
	assert(sxc_point_cmp(&p3, &p4) < 0);
	assert(sxc_point_cmp(&p2, &p5) == 0);
	assert(sxc_point_cmp(&p2, &p3) > 0);

	return EXIT_SUCCESS;
}
