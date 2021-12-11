#include <stdlib.h>
#include <assert.h>

#include <sxc_vector.h>
#include <sxc_vector_types.h>

int main()
{
	Int_vector vi;
	sxc_vector_init(&vi);

	assert(vi.siz == 0);
	assert(vi.cap != 0);
	assert(vi.vec != NULL);

	sxc_vector_free(&vi);

	return EXIT_SUCCESS;
}

