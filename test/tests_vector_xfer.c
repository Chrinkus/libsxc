#include <stdlib.h>
#include <assert.h>

#include <sxc_vector.h>
#include <sxc_vector_types.h>

int main()
{
	Int_vector vi;
	sxc_vector_init(&vi);

	sxc_vector_push(&vi, 5);
	sxc_vector_push(&vi, 10);
	sxc_vector_push(&vi, 37);
	sxc_vector_push(&vi, 67);
	sxc_vector_push(&vi, 42);

	int* p = NULL;
	sxc_vector_xfer(&vi, p);

	assert(vi.siz == 5);
	assert(vi.cap == 0);
	assert(vi.vec == NULL);

	assert(p[0] == 5);
	assert(p[1] == 10);
	assert(p[2] == 37);
	assert(p[3] == 67);
	assert(p[4] == 42);


	// This will free the vector's prior memory
	free(p);
	// Not necessary but here to test double-free detection
	sxc_vector_free(&vi);

	return EXIT_SUCCESS;
}

