#include <stdlib.h>
#include <assert.h>

#include "sxc_vector.h"

struct Point {
	int x;
	int y;
};

struct Point_vector {
	size_t siz;
	size_t cap;
	struct Point* vec;
};

int main()
{
	struct Point_vector vp;
	sxc_vector_init(vp);

	struct Point p1 = { 5, -2 };
	sxc_vector_push(vp, p1);

	struct Point* p2 = sxc_vector_getp(vp, 0);

	assert(p2 != &p1);
	assert(p2->x == p1.x);
	assert(p2->y == p1.y);

	sxc_vector_free(vp);

	return EXIT_SUCCESS;
}
