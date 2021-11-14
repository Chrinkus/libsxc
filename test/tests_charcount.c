#include <stdlib.h>
#include <assert.h>

#include "sxc_utils.h"

int main()
{
	struct Charcount ca = charcount_init('a');

	assert(ca.ch == 'a');
	assert(ca.count == 0);

	struct Charcount cb = charcount_init('b');
	cb.count = 5;

	assert(charcount_cmp(&cb, &ca) < 0);	// the greater moves left
	assert(charcount_cmp(&ca, &cb) > 0);	// the lesser moves right

	ca.count = 5;
	assert(charcount_cmp(&ca, &cb) == 0);	// equality detected

	return EXIT_SUCCESS;
}
