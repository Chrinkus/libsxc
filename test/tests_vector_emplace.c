#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <sxc_vector.h>
#include <sxc_vector_types.h>
#include <sxc_point.h>

enum { NUMSTRINGS = 5 };

const char* holidays[NUMSTRINGS] = {
	"Christmas",
	"Valentines",
	"Easter",
	"Rememberance",
	"Halloween",
};

void add_a_point(struct SXC_Point_vector* v)
{
	struct SXC_Point* p = NULL;
	sxc_vector_emplace(v, p);
	p->x = 110;
	p->y = 25;
}

int main()
{
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// Dynamically allocated strings

	Charp_vector vc;
	sxc_vector_init(&vc);

	for (int i = 0; i < NUMSTRINGS; ++i) {
		char** p = NULL;
		sxc_vector_emplace(&vc, p);
		*p = strdup(holidays[i]);
	}

	assert(sxc_vector_size(&vc) == NUMSTRINGS);

	for (size_t i = 0; i < sxc_vector_size(&vc); ++i)
		assert(strcmp(sxc_vector_get(&vc, i), holidays[i]) == 0);

	sxc_vector_freep(&vc);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// Structs
	
	struct SXC_Point_vector vp;
	sxc_vector_init(&vp);

	struct SXC_Point* pt = NULL;
	sxc_vector_emplace(&vp, pt);
	pt->x = 53;
	pt->y = 80;

	add_a_point(&vp);

	sxc_vector_emplace(&vp, pt);
	pt->x = 22;
	pt->y = -37;

	assert(sxc_vector_size(&vp) == 3);
	assert(sxc_vector_getp(&vp, 0)->x == 53);
	assert(sxc_vector_getp(&vp, 0)->y == 80);
	assert(sxc_vector_getp(&vp, 1)->x == 110);
	assert(sxc_vector_getp(&vp, 1)->y == 25);
	assert(sxc_vector_getp(&vp, 2)->x == 22);
	assert(sxc_vector_getp(&vp, 2)->y == -37);

	sxc_vector_free(&vp);

	return EXIT_SUCCESS;
}
