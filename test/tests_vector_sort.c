#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <sxc_vector.h>

SXC_NEW_VECTOR(int_vec, int);
SXC_NEW_VECTOR(ccs_vec, const char*);

int int_cmp(const void* a, const void* b)
{
	return *(const int*)a - *(const int*)b;
}

int string_sort_cmp(const void* a, const void* b)
	// a and b are const char**
{
	const char* s1 = *(const char**)a;
	const char* s2 = *(const char**)b;
	return strcmp(s1, s2);
}

int main()
{
	int_vec vi;
	sxc_vector_init(&vi);

	int arr[8] = { 10, 5, 37, -8, 2, 101, -67, 42 };
	for (int i = 0; i < 8; ++i)
		sxc_vector_push(&vi, arr[i]);

	sxc_vector_sort(&vi, int_cmp);

	assert(sxc_vector_get(&vi, 0) == -67);
	assert(sxc_vector_get(&vi, 1) == -8);
	assert(sxc_vector_get(&vi, 2) == 2);
	assert(sxc_vector_get(&vi, 3) == 5);
	assert(sxc_vector_get(&vi, 4) == 10);
	assert(sxc_vector_get(&vi, 5) == 37);
	assert(sxc_vector_get(&vi, 6) == 42);
	assert(sxc_vector_get(&vi, 7) == 101);

	sxc_vector_free(&vi);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	
	const char* defence[11] = {
		"warren",
		"traylor",
		"seymour",
		"mcginest",
		"johnson",
		"bruschi",
		"vrabel",
		"law",
		"gay",
		"harrison",
		"wilson",
	};
	
	ccs_vec vs;
	sxc_vector_init(&vs);

	for (int i = 0; i < 11; ++i)
		sxc_vector_push(&vs, defence[i]);

	assert(sxc_vector_size(&vs) == 11);

	sxc_vector_sort(&vs, string_sort_cmp);
	assert(strcmp(sxc_vector_get(&vs, 0), "bruschi") == 0);
	assert(strcmp(sxc_vector_get(&vs, 1), "gay") == 0);
	assert(strcmp(sxc_vector_get(&vs, 2), "harrison") == 0);
	assert(strcmp(sxc_vector_get(&vs, 3), "johnson") == 0);
	assert(strcmp(sxc_vector_get(&vs, 4), "law") == 0);
	assert(strcmp(sxc_vector_get(&vs, 5), "mcginest") == 0);
	assert(strcmp(sxc_vector_get(&vs, 6), "seymour") == 0);
	assert(strcmp(sxc_vector_get(&vs, 7), "traylor") == 0);
	assert(strcmp(sxc_vector_get(&vs, 8), "vrabel") == 0);
	assert(strcmp(sxc_vector_get(&vs, 9), "warren") == 0);
	assert(strcmp(sxc_vector_get(&vs, 10), "wilson") == 0);

	sxc_vector_free(&vs);

	return EXIT_SUCCESS;
}


