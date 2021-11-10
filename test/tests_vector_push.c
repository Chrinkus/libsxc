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

	for (int i = 0; i < 50; ++i)
		sxc_vector_push(vi, i * 10);

	assert(vi.siz == 50);
	assert(vi.vec != NULL);

	int* p = sxc_vector_getp(vi, 20);
	assert(*p == 200);

	assert(*sxc_vector_getp(vi, 0) == 0);
	assert(*sxc_vector_getp(vi, 1) == 10);
	assert(*sxc_vector_getp(vi, 49) == 490);

	sxc_vector_free(vi);

	return EXIT_SUCCESS;
}
