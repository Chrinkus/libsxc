#include <stdlib.h>
#include <assert.h>

#include <sxc_vector.h>
#include <sxc_point.h>

int main()
{
	struct SXC_Point_vector vp;
	sxc_vector_init(vp);

	// Create a stack value and push it
	struct SXC_Point p1 = { 5, -2 };
	sxc_vector_push(vp, p1);	// Copies value to new vector element

	// Get a pointer to the vector element
	struct SXC_Point* p2 = sxc_vector_getp(vp, 0);

	assert(p2 != &p1);	// Different pointers, different objects
	assert(p2->x == p1.x);
	assert(p2->y == p1.y);

	// Copy a compound literal to the vector (wrap in parens!)
	sxc_vector_push(vp, ((struct SXC_Point){ .x = -10, .y = 6 }));

	assert(sxc_vector_size(vp) == 2);

	// Get a pointer to newest element and check that it was copied
	struct SXC_Point* p3 = sxc_vector_getp(vp, 1);
	assert(p3->x == -10);
	assert(p3->y == 6);

	// Allocate an object on the heap
	struct SXC_Point* p4 = malloc(sizeof(struct SXC_Point));
	p4->x = 7;
	p4->y = -3;

	// Push copy of heap object
	sxc_vector_push(vp, *p4);

	assert(sxc_vector_size(vp) == 3);

	// Get pointer to the newest element and check that they point to
	// different objects that are equal.
	struct SXC_Point* p5 = sxc_vector_getp(vp, 2);
	assert(p5 != p4);
	assert(p5->x == p4->x);
	assert(p5->y == p4->y);

	free(p4);
	sxc_vector_free(vp);

	return EXIT_SUCCESS;
}

