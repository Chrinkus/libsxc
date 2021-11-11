#include <stdlib.h>
#include <assert.h>

#include "sxc_vector.h"
#include "sxc_point.h"

/*
struct Point {
	int x;
	int y;
};

struct Point_vector {
	size_t siz;
	size_t cap;
	struct Point* vec;
};

const struct Point* point_cmp_eq(const struct Point* a, const struct Point* b)
{
	if ((a->x == b->x) && (a->y == b->y))
		return a;
	return NULL;
}
*/

int main()
{
	struct SXC_Point_vector vp;
	sxc_vector_init(vp);

	for (int i = -50; i < 50; ++i)
		for (int j = -50; j < 50; ++j) {
			struct SXC_Point p = { j, i };
			sxc_vector_push(vp, p);
		}

	struct SXC_Point tar1 = { 37, -37 };	// Should be found
	struct SXC_Point tar2 = { 100, 0 };	// Should not be found

	struct SXC_Point* p1 = NULL;
	sxc_vector_find(vp, &tar1, sxc_point_cmp, p1);
	assert(p1 != NULL);
	assert(p1->x == tar1.x);
	assert(p1->y == tar1.y);

	struct SXC_Point* p2 = NULL;
	sxc_vector_find(vp, &tar2, sxc_point_cmp, p2);
	assert(p2 == NULL);

	sxc_vector_free(vp);

	return EXIT_SUCCESS;
}

