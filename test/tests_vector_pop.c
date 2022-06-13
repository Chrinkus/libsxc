#include <stdlib.h>
#include <assert.h>

#include <sxc_vector.h>

SXC_NEW_VECTOR(vec_int, int);

int main()
{
	vec_int vi;
	sxc_vector_init(&vi);

	sxc_vector_push(&vi, 110);
	sxc_vector_push(&vi, 123);
	sxc_vector_push(&vi, 139);
	sxc_vector_push(&vi, 143);
	sxc_vector_push(&vi, 161);
	sxc_vector_push(&vi, 162);

	assert(sxc_vector_size(&vi) == 6);

	int n = 0;
	sxc_vector_pop(&vi, n);

	assert(n == 162);
	assert(sxc_vector_size(&vi) == 5);

	sxc_vector_pop(&vi, n);
	assert(n == 161);
	assert(sxc_vector_size(&vi) == 4);

	sxc_vector_pop(&vi, n);
	assert(n == 143);
	assert(sxc_vector_size(&vi) == 3);

	sxc_vector_pop(&vi, n);
	assert(n == 139);
	assert(sxc_vector_size(&vi) == 2);

	sxc_vector_pop(&vi, n);
	assert(n == 123);
	assert(sxc_vector_size(&vi) == 1);

	sxc_vector_pop(&vi, n);
	assert(n == 110);
	assert(sxc_vector_size(&vi) == 0);

	n = 995;
	sxc_vector_pop(&vi, n);			// will silently fail
	assert(n == 995);			// n is un-changed
	assert(sxc_vector_size(&vi) == 0);	// size has not been decremented

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	
	sxc_vector_push(&vi, 389);
	sxc_vector_push(&vi, 443);
	sxc_vector_push(&vi, 465);
	sxc_vector_push(&vi, 514);
	sxc_vector_push(&vi, 636);

	assert(sxc_vector_size(&vi) == 5);

	sxc_vector_pop_front(&vi, n);
	assert(n == 389);
	assert(sxc_vector_size(&vi) == 4);

	sxc_vector_pop_front(&vi, n);
	assert(n == 443);
	assert(sxc_vector_size(&vi) == 3);

	sxc_vector_pop_front(&vi, n);
	assert(n == 465);
	assert(sxc_vector_size(&vi) == 2);

	sxc_vector_pop_front(&vi, n);
	assert(n == 514);
	assert(sxc_vector_size(&vi) == 1);

	sxc_vector_pop_front(&vi, n);
	assert(n == 636);
	assert(sxc_vector_size(&vi) == 0);

	n = 993;
	sxc_vector_pop_front(&vi, n);
	assert(n == 993);
	assert(sxc_vector_size(&vi) == 0);

	sxc_vector_free(&vi);

	return EXIT_SUCCESS;
}
