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

	assert(strcmp(s.str, "abcde") == 0);
	assert(s.siz == 5);

	sxc_string_push(&s, '1');
	sxc_string_push(&s, '2');
	sxc_string_push(&s, '3');

	assert(strcmp(s.str, "abcde123") == 0);
	assert(s.siz == 8);

	sxc_string_free(&s);

	return EXIT_SUCCESS;
}

