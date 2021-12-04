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
	sxc_vector_init(&vi);

	for (int i = 0, j = 1; i < 10; ++i, j *= 2)
		sxc_vector_push(&vi, j);

	assert(sxc_vector_size(&vi) == 10);
	assert(sxc_vector_get(&vi, 3) == 8);
	assert(sxc_vector_get(&vi, 6) == 64);

	sxc_vector_free(&vi);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

	struct Double_vector vd;
	sxc_vector_init(&vd);

	for (double i = 0, j = 1; i < 10; ++i, j /= 2)
		sxc_vector_push(&vd, j);

	assert(sxc_vector_size(&vd) == 10);

	//sxc_vector_foreach(&vd, print_double);

	sxc_vector_free(&vd);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// Pointers to static strings

	struct Charp_vector vcstatic;
	sxc_vector_init(&vcstatic);

	sxc_vector_push(&vcstatic, "hello vector");
	sxc_vector_push(&vcstatic, "these are static strings");
	sxc_vector_push(&vcstatic, "no reason why they shouldn't get pushed");

	assert(sxc_vector_size(&vcstatic) == 3);
	assert(strcmp(sxc_vector_get(&vcstatic, 0), "hello vector") == 0);

	sxc_vector_free(&vcstatic);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// Pointers to malloc'd strings
	
	struct Charp_vector vcmalloc;
	sxc_vector_init(&vcmalloc);

	char arr[] = "stack string";
	sxc_vector_push(&vcmalloc, strdup(arr));

	assert(sxc_vector_size(&vcmalloc) == 1);
	assert(strcmp(sxc_vector_get(&vcmalloc, 0), arr) == 0);

	char* s = malloc(16);
	for (int c = 'a', i = 0; i < 10 /* 'j' */; ++c, ++i)
		s[i] = c;
	s[10] = '\0';
	sxc_vector_push(&vcmalloc, s);
	assert(sxc_vector_size(&vcmalloc) == 2);
	assert(strcmp(sxc_vector_get(&vcmalloc, 1), "abcdefghij") == 0);

	sxc_vector_freep(&vcmalloc);

	return EXIT_SUCCESS;
}

