#include <stdlib.h>
#include <assert.h>
#include <string.h>	// strcmp

#include "sxc_string.h"

int main()
{
	String s;
	sxc_string_init(&s);

	for (char ch = 'a'; ch < 'f'; ++ch)
		sxc_string_push(&s, ch);

	assert(strcmp(sxc_string_str(&s), "abcde") == 0);
	assert(sxc_string_size(&s) == 5);

	sxc_string_push(&s, '1');
	sxc_string_push(&s, '2');
	sxc_string_push(&s, '3');

	assert(strcmp(sxc_string_str(&s), "abcde123") == 0);
	assert(sxc_string_size(&s) == 8);

	sxc_string_clear(&s);
	assert(sxc_string_size(&s) == 0);
	assert(strcmp(sxc_string_str(&s), "") == 0);

	sxc_string_free(&s);

	return EXIT_SUCCESS;
}

