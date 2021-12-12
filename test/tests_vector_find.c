#include <stdlib.h>
#include <assert.h>

#include <sxc_vector.h>
#include <sxc_vector_types.h>
#include <sxc_point.h>

int int_cmp(const void* a, const void* b)
{
	return *(const int*)a - *(const int*)b;
}

int main()
{
	struct SXC_Point_vector vp;
	sxc_vector_init(&vp);

	for (int i = -50; i < 50; ++i)
		for (int j = -50; j < 50; ++j) {
			struct SXC_Point p = { j, i };
			sxc_vector_push(&vp, p);
		}

	struct SXC_Point tar1 = { 37, -37 };	// Should be found
	struct SXC_Point tar2 = { 100, 0 };	// Should not be found

	struct SXC_Point* p1 = NULL;
	sxc_vector_find(&vp, &tar1, sxc_point_cmp, p1);
	assert(p1 != NULL);
	assert(p1->x == tar1.x);
	assert(p1->y == tar1.y);

	struct SXC_Point* p2 = NULL;
	sxc_vector_find(&vp, &tar2, sxc_point_cmp, p2);
	assert(p2 == NULL);

	sxc_vector_free(&vp);
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	Int_vector vi;
	sxc_vector_init(&vi);

	int arr[] = { 5, 2, -10, -42, 37 };
	for (size_t i = 0; i < sizeof(arr); ++i)
		sxc_vector_push(&vi, arr[i]);

	int n1 = -42;
	int n2 = -2;

	int* p = NULL;
	sxc_vector_find(&vi, &n1, int_cmp, p);
	assert(p != NULL);
	assert(*p == -42);

	int* q = NULL;
	sxc_vector_find(&vi, &n2, int_cmp, q);
	assert(q == NULL);

	sxc_vector_free(&vi);

	return EXIT_SUCCESS;
}

