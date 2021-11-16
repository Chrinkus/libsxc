#include <stdlib.h>
#include <assert.h>
#include <stdio.h>	// printf
#include <string.h>	// strcmp, strdup

#include <sxc_vector.h>
#include <sxc_vector_types.h>

void print_double(double* d)
{
	printf("%.10f\n", *d);
}

int main()
{
	struct Int_vector vi;
	sxc_vector_init(vi);

	for (int i = 0, j = 1; i < 10; ++i, j *= 2)
		sxc_vector_push(vi, j);

	assert(sxc_vector_size(vi) == 10);
	assert(sxc_vector_get(vi, 3) == 8);
	assert(sxc_vector_get(vi, 6) == 64);

	sxc_vector_free(vi);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

	struct Double_vector vd;
	sxc_vector_init(vd);

	for (double i = 0, j = 1; i < 10; ++i, j /= 2)
		sxc_vector_push(vd, j);

	assert(sxc_vector_size(vd) == 10);

	//sxc_vector_foreach(vd, print_double);

	sxc_vector_free(vd);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

	struct Charp_vector vc;
	sxc_vector_init(vc);

	sxc_vector_push(vc, "hello vector");
	sxc_vector_push(vc, "these are static strings");
	sxc_vector_push(vc, "no reason why they shouldn't get pushed");

	assert(sxc_vector_size(vc) == 3);
	assert(strcmp(sxc_vector_get(vc, 0), "hello vector") == 0);

	char arr[] = "stack string";
	sxc_vector_push(vc, strdup(arr));

	assert(sxc_vector_size(vc) == 4);
	assert(strcmp(sxc_vector_get(vc, 3), arr) == 0);

	// Hmm.. how to free vectors of different string sources..?
	free(sxc_vector_get(vc, 3));

	sxc_vector_free(vc);

	return EXIT_SUCCESS;
}

