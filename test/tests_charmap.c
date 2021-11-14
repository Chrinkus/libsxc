#include <stdlib.h>
#include <assert.h>

#include "sxc_utils.h"

int main()
{
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// lower case
	struct Charmap cml;
	if (!charmap_init(&cml, SXC_ALPHA_LOWER))
		return EXIT_FAILURE;

	assert(charmap_get_count(&cml, 'a') == 0);
	assert(charmap_get_count(&cml, 'h') == 0);
	assert(charmap_get_count(&cml, 'z') == 0);

	charmap_inc(&cml, 'm');
	assert(charmap_get_count(&cml, 'm') == 1);

	charmap_free(&cml);

	if (!charmap_init(&cml, SXC_ALPHA_LOWER))
		return EXIT_FAILURE;

	charmap_count_chars(&cml, "aabccccdddeefffff");
	charmap_sort(&cml);

	struct Charcount* most = charmap_sorted_most(&cml);
	assert(most->ch == 'f');
	assert(most->count == 5);

	struct Charcount* least = charmap_sorted_least(&cml);
	assert(least->ch == 'b');
	assert(least->count == 1);

	charmap_free(&cml);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// upper case
	struct Charmap cmu;
	if (!charmap_init(&cmu, SXC_ALPHA_UPPER))
		return EXIT_FAILURE;

	charmap_count_chars(&cmu, "MXUUPOEFEAEEB");
	assert(charmap_get_count(&cmu, 'M') == 1);
	assert(charmap_get_count(&cmu, 'E') == 4);
	assert(charmap_get_count(&cmu, 'U') == 2);
	assert(charmap_get_count(&cmu, 'C') == 0);

	charmap_sort(&cmu);
	assert(charmap_get_index(&cmu, 0)->ch == 'E');
	assert(charmap_get_index(&cmu, 1)->ch == 'U');

	charmap_free(&cmu);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	// digits
	struct Charmap cmd;
	if (!charmap_init(&cmd, SXC_DIGITS))
		return EXIT_FAILURE;

	charmap_count_chars(&cmd, "2,147,483,647");
	assert(charmap_get_count(&cmd, '0') == 0);
	assert(charmap_get_count(&cmd, '1') == 1);
	assert(charmap_get_count(&cmd, '2') == 1);
	assert(charmap_get_count(&cmd, '3') == 1);
	assert(charmap_get_count(&cmd, '4') == 3);
	assert(charmap_get_count(&cmd, '5') == 0);
	assert(charmap_get_count(&cmd, '6') == 1);
	assert(charmap_get_count(&cmd, '7') == 2);
	assert(charmap_get_count(&cmd, '8') == 1);
	assert(charmap_get_count(&cmd, '9') == 0);

	charmap_sort(&cmd);
	struct Charcount* top = charmap_get_index(&cmd, 0);
	assert(top->ch == '4');
	assert(top->count == 3);

	struct Charcount* found = charmap_find(&cmd, '5');
	assert(found->ch == '5');
	assert(found->count == 0);

	struct Charcount* not_found = charmap_find(&cmd, '?');
	assert(not_found == NULL);

	charmap_free(&cmd);

	return EXIT_SUCCESS;
}
