#include <stdlib.h>
#include <assert.h>

#include <sxc_vector.h>
#include <sxc_vector_types.h>

int int_cmp(const void* a, const void* b)
{
	return *(const int*)a - *(const int*)b;
}

int main()
{
	struct Int_vector vi;
	sxc_vector_init(vi);

	int arr[8] = { 10, 5, 37, -8, 2, 101, -67, 42 };
	for (int i = 0; i < 8; ++i)
		sxc_vector_push(vi, arr[i]);

	sxc_vector_sort(vi, int_cmp);

	assert(sxc_vector_get(vi, 0) == -67);
	assert(sxc_vector_get(vi, 1) == -8);
	assert(sxc_vector_get(vi, 2) == 2);
	assert(sxc_vector_get(vi, 3) == 5);
	assert(sxc_vector_get(vi, 4) == 10);
	assert(sxc_vector_get(vi, 5) == 37);
	assert(sxc_vector_get(vi, 6) == 42);
	assert(sxc_vector_get(vi, 7) == 101);

	sxc_vector_free(vi);

	return EXIT_SUCCESS;
}


