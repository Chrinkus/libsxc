#include <stdlib.h>
#include <assert.h>

#include "sxc_utils.h"

int main()
{
	struct sxc_charcount ca = sxc_charcount_init('a');

	assert(ca.ch == 'a');
	assert(ca.count == 0);

	struct sxc_charcount cb = sxc_charcount_init('b');
	cb.count = 5;

	assert(sxc_charcount_cmp(&cb, &ca) < 0);	// the greater moves left
	assert(sxc_charcount_cmp(&ca, &cb) > 0);	// the lesser moves right

	ca.count = 5;
	assert(sxc_charcount_cmp(&ca, &cb) == 0);	// equality detected

	return EXIT_SUCCESS;
}
