#include <stdlib.h>
#include <assert.h>

#include <sxc_vector.h>
#include <sxc_vector_types.h>

void double_int(int* n)
{
	*n *= 2;
}

int main()
{
	Int_vector vi;
	sxc_vector_init(&vi);

	for (int i = 0; i < 100; ++i)
		sxc_vector_push(&vi, i);

	sxc_vector_foreach(&vi, double_int);

	assert(sxc_vector_get(&vi, 0) == 0);
	assert(sxc_vector_get(&vi, 1) == 2);
	assert(sxc_vector_get(&vi, 98) == 196);
	assert(sxc_vector_get(&vi, 99) == 198);

	sxc_vector_free(&vi);

	return EXIT_SUCCESS;
}
