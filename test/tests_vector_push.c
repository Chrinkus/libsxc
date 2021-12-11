#include <stdlib.h>
#include <assert.h>

#include <sxc_vector.h>
#include <sxc_vector_types.h>

int main()
{
	Int_vector vi;
	sxc_vector_init(&vi);

	for (int i = 0; i < 50; ++i)
		sxc_vector_push(&vi, i * 10);

	assert(vi.siz == 50);
	assert(vi.vec != NULL);

	int* p = sxc_vector_getp(&vi, 20);
	assert(*p == 200);

	assert(sxc_vector_get(&vi, 0) == 0);
	assert(sxc_vector_get(&vi, 1) == 10);
	assert(sxc_vector_get(&vi, 49) == 490);

	sxc_vector_free(&vi);

	return EXIT_SUCCESS;
}
