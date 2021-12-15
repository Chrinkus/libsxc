#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <sxc_vector.h>

SXC_NEW_VECTOR(int_vec, int);
SXC_NEW_VECTOR(chars_vec, const char*);

int int_cmp(const int* a, int b)
{
	return *a - b;
}

int string_sort_cmp(const void* a, const void* b)
{
	const char* s1 = *(const char**)a;
	const char* s2 = *(const char**)b;
	return strcmp(s1, s2);
}

int string_cmp(const char** a, const char* b)
{
	return strcmp(*a, b);
}

int main()
{
	int arr[10] = { -31, -8, 0, 2, 10, 13, 27, 37, 79, 100 };

	int_vec vi;
	sxc_vector_init(&vi);

	for (int i = 0; i < 10; ++i)
		sxc_vector_push(&vi, arr[i]);

	int* ptri = NULL;
	sxc_vector_binary_search(&vi, 37, int_cmp, ptri);

	assert(ptri != NULL);
	assert(*ptri == 37);

	for (int* found = NULL, i = 0; i < 10; ++i, found = NULL) {
		sxc_vector_binary_search(&vi, arr[i], int_cmp, found);
		assert(*found == arr[i]);
	}

	sxc_vector_free(&vi);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	
	const char* a2[15] = {
		"sunday",
		"monday",
		"tuesday",
		"wednesday",
		"thursday",
		"friday",
		"saturday",
		"red",
		"orange",
		"yellow",
		"green",
		"blue",
		"indigo",
		"violet",
		"rainbow",
	};

	chars_vec vs;
	sxc_vector_init(&vs);
	for (int i = 0; i < 15; ++i)
		sxc_vector_push(&vs, a2[i]);

	sxc_vector_sort(&vs, string_sort_cmp);
	assert(strcmp("blue", sxc_vector_get(&vs, 0)) == 0);	// sorted

	const char** ptrs = NULL;
	for (int i = 0; i < 15; ++i, ptrs = NULL) {
		sxc_vector_binary_search(&vs, a2[i], string_cmp, ptrs);
		assert(strcmp(*ptrs, a2[i]) == 0);
	}

	sxc_vector_free(&vs);

	return EXIT_SUCCESS;
}
