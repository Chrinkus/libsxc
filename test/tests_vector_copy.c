#include <stdlib.h>
#include <assert.h>

#include "sxc_vector.h"

struct Int_vector {
	size_t siz;
	size_t cap;
	int* vec;
};

int main()
{
	struct Int_vector vi;
	sxc_vector_init(vi);

	sxc_vector_push(vi, 5);
	sxc_vector_push(vi, 10);
	sxc_vector_push(vi, 37);
	sxc_vector_push(vi, 67);
	sxc_vector_push(vi, 42);

	struct Int_vector vc;
	sxc_vector_copy(vc, vi);

	assert(*sxc_vector_getp(vc, 0) == 5);
	assert(*sxc_vector_getp(vc, 1) == 10);
	assert(*sxc_vector_getp(vc, 2) == 37);
	assert(*sxc_vector_getp(vc, 3) == 67);
	assert(*sxc_vector_getp(vc, 4) == 42);

	sxc_vector_free(vi);
	sxc_vector_free(vc);

	return EXIT_SUCCESS;
}

