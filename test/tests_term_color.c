#include <stdlib.h>
#include <assert.h>

#include <sxc_term_color.h>

/*
 * This is more to prove that the color changing functionality will compile
 * on a system. You'll need to manually run this file and verify that the
 * text prints in color.
 */

int main()
{
	// Macro tests
	printf(TCNBLK "This is black\n" TCDEF);
	printf(TCNRED "This is red\n" TCDEF);
	printf(TCNGRN "This is green\n" TCDEF);
	printf(TCNYEL "This is yellow\n" TCDEF);
	printf(TCNBLU "This is blue\n" TCDEF);
	printf(TCNMAG "This is magenta\n" TCDEF);
	printf(TCNCYN "This is cyan\n" TCDEF);
	printf(TCNWHT "This is white\n" TCDEF);
	printf("This is back to normal\n");

	printf(TCBBLK "This is bold black\n" TCDEF);
	printf(TCBRED "This is bold red\n" TCDEF);
	printf(TCBGRN "This is bold green\n" TCDEF);
	printf(TCBYEL "This is bold yellow\n" TCDEF);
	printf(TCBBLU "This is bold blue\n" TCDEF);
	printf(TCBMAG "This is bold magenta\n" TCDEF);
	printf(TCBCYN "This is bold cyan\n" TCDEF);
	printf(TCBWHT "This is bold white\n" TCDEF);
	printf("This is back to normal\n");

	// Alternating color tests
	int colors[3] = { SXC_TCN_MAG, SXC_TCN_GRN, SXC_TCN_WHT };
	sxc_termcolor_altw("Did you watch ", colors, 3);
	sxc_termcolor_altc("Squid Game?\n", colors, 3);

	return EXIT_SUCCESS;
}
