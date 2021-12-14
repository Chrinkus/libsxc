#include <stdlib.h>
#include <assert.h>

#include "sxc_utils.h"

int main()
{
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// lower case
	struct sxc_charmap cml;
	if (!sxc_charmap_init(&cml, SXC_ALPHA_LOWER))
		return EXIT_FAILURE;

	assert(sxc_charmap_get_count(&cml, 'a') == 0);
	assert(sxc_charmap_get_count(&cml, 'h') == 0);
	assert(sxc_charmap_get_count(&cml, 'z') == 0);

	sxc_charmap_inc(&cml, 'm');
	assert(sxc_charmap_get_count(&cml, 'm') == 1);

	sxc_charmap_free(&cml);

	if (!sxc_charmap_init(&cml, SXC_ALPHA_LOWER))
		return EXIT_FAILURE;

	sxc_charmap_count_chars(&cml, "aabccccdddeefffff");
	sxc_charmap_sort(&cml);

	struct sxc_charcount* most = sxc_charmap_sorted_most(&cml);
	assert(most->ch == 'f');
	assert(most->count == 5);

	struct sxc_charcount* least = sxc_charmap_sorted_least(&cml);
	assert(least->ch == 'b');
	assert(least->count == 1);

	sxc_charmap_free(&cml);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// upper case
	struct sxc_charmap cmu;
	if (!sxc_charmap_init(&cmu, SXC_ALPHA_UPPER))
		return EXIT_FAILURE;

	sxc_charmap_count_chars(&cmu, "MXUUPOEFEAEEB");
	assert(sxc_charmap_get_count(&cmu, 'M') == 1);
	assert(sxc_charmap_get_count(&cmu, 'E') == 4);
	assert(sxc_charmap_get_count(&cmu, 'U') == 2);
	assert(sxc_charmap_get_count(&cmu, 'C') == 0);

	sxc_charmap_sort(&cmu);
	assert(sxc_charmap_get_index(&cmu, 0)->ch == 'E');
	assert(sxc_charmap_get_index(&cmu, 1)->ch == 'U');

	sxc_charmap_free(&cmu);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// digits
	struct sxc_charmap cmd;
	if (!sxc_charmap_init(&cmd, SXC_DIGITS))
		return EXIT_FAILURE;

	sxc_charmap_count_chars(&cmd, "2,147,483,647");
	assert(sxc_charmap_get_count(&cmd, '0') == 0);
	assert(sxc_charmap_get_count(&cmd, '1') == 1);
	assert(sxc_charmap_get_count(&cmd, '2') == 1);
	assert(sxc_charmap_get_count(&cmd, '3') == 1);
	assert(sxc_charmap_get_count(&cmd, '4') == 3);
	assert(sxc_charmap_get_count(&cmd, '5') == 0);
	assert(sxc_charmap_get_count(&cmd, '6') == 1);
	assert(sxc_charmap_get_count(&cmd, '7') == 2);
	assert(sxc_charmap_get_count(&cmd, '8') == 1);
	assert(sxc_charmap_get_count(&cmd, '9') == 0);

	sxc_charmap_sort(&cmd);
	struct sxc_charcount* top = sxc_charmap_get_index(&cmd, 0);
	assert(top->ch == '4');
	assert(top->count == 3);

	struct sxc_charcount* found = sxc_charmap_find(&cmd, '5');
	assert(found->ch == '5');
	assert(found->count == 0);

	struct sxc_charcount* not_found = sxc_charmap_find(&cmd, '?');
	assert(not_found == NULL);

	sxc_charmap_free(&cmd);

	return EXIT_SUCCESS;
}
