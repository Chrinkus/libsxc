#include <stdlib.h>
#include <assert.h>

#include "sxc_string.h"

int main()
{
	struct sxc_string s;
	sxc_string_init(&s);

	assert(s.siz == 0);
	assert(s.cap != 0);
	assert(s.str != NULL);

	sxc_string_free(&s);

	return EXIT_SUCCESS;
}
