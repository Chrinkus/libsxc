#pragma once

#include <stdio.h>
#include <ctype.h>

/**
 * Macro colors
 *
 * Good for on-the-fly color changing in printf calls.
 *
 * Naming convention:
 * TCNRED = Terminal Color Normal RED
 * TCBMAG = Terminal Color Bold MAGenta
 *
 * Special codes:
 * RES = Reset code
 * DEF = Default code
 *
 * Note:
 * I agonized over the macro names. Since they're inline I wanted them to 
 * be short enough to be "usable" but still unique enough to avoid clashes.
 */
#define TCRES "\033[0m"	
#define TCDEF "\033[0;39m"

#define TCNBLK "\033[0;30m"
#define TCNRED "\033[0;31m"
#define TCNGRN "\033[0;32m"
#define TCNYEL "\033[0;33m"
#define TCNBLU "\033[0;34m"
#define TCNMAG "\033[0;35m"
#define TCNCYN "\033[0;36m"
#define TCNWHT "\033[0;37m"

#define TCBBLK "\033[1;30m"
#define TCBRED "\033[1;31m"
#define TCBGRN "\033[1;32m"
#define TCBYEL "\033[1;33m"
#define TCBBLU "\033[1;34m"
#define TCBMAG "\033[1;35m"
#define TCBCYN "\033[1;36m"
#define TCBWHT "\033[1;37m"

/**
 * Enums and string colors
 *
 * Good for programmatic color changes.
 */
enum SXC_Term_color_index {
	// Special colors
	SXC_TC_RES,
	SXC_TC_DEF,
	// Normal colors
	SXC_TCN_BLK,
	SXC_TCN_RED,
	SXC_TCN_GRN,
	SXC_TCN_YEL,
	SXC_TCN_BLU,
	SXC_TCN_MAG,
	SXC_TCN_CYN,
	SXC_TCN_WHT,
	// Bold colors
	SXC_TCB_BLK,
	SXC_TCB_RED,
	SXC_TCB_GRN,
	SXC_TCB_YEL,
	SXC_TCB_BLU,
	SXC_TCB_MAG,
	SXC_TCB_CYN,
	SXC_TCB_WHT,
	// Size of array
	SXC_TC_NUM_COLORS,
};

const char* const sxc_color_strings[SXC_TC_NUM_COLORS] = {
	// Special colors
	[SXC_TC_RES]	= "\033[0m",
	[SXC_TC_DEF]	= "\033[0;39m",
	// Normal colors
	[SXC_TCN_BLK]	= "\033[0;30m",
	[SXC_TCN_RED]	= "\033[0;31m",
	[SXC_TCN_GRN]	= "\033[0;32m",
	[SXC_TCN_YEL]	= "\033[0;33m",
	[SXC_TCN_BLU]	= "\033[0;34m",
	[SXC_TCN_MAG]	= "\033[0;35m",
	[SXC_TCN_CYN]	= "\033[0;36m",
	[SXC_TCN_WHT]	= "\033[0;37m",
	// Bold colors
	[SXC_TCB_BLK]	= "\033[1;30m",
	[SXC_TCB_RED]	= "\033[1;31m",
	[SXC_TCB_GRN]	= "\033[1;32m",
	[SXC_TCB_YEL]	= "\033[1;33m",
	[SXC_TCB_BLU]	= "\033[1;34m",
	[SXC_TCB_MAG]	= "\033[1;35m",
	[SXC_TCB_CYN]	= "\033[1;36m",
	[SXC_TCB_WHT]	= "\033[1;37m",
};

/**
 * Semi-shorthand for passing the color string to a '%s' in a printf.
 */
#define termcolor(enum_val) sxc_color_strings[(enum_val)]

/**
 * Prints a string, alternating the non-whitespace characters through the 
 * provided array of colors.
 *
 * @param s		String to print
 * @param colors	Array of color enumerations
 * @param len		Lenght of array
 */
void sxc_termcolor_altc(const char* s, int* colors, int len)
{
	if (!colors || (len <= 0)) {
		fprintf(stderr, "No colors to print\n");
		return;
	}

	for (int i = 0; *s; ++s) {
		if (!isspace(*s))
			printf("%s%c", termcolor(colors[i++%len]), *s);
		else
			printf("%c", *s);
	}
	printf("%s", termcolor(SXC_TC_DEF));	// Reset to default color
}

void sxc_termcolor_altw(const char* s, int* colors, int len)
{
	if (!colors || (len <= 0)) {
		fprintf(stderr, "No colors to print\n");
		return;
	}

	printf("%s", termcolor(colors[0]));
	for (int i = 1; *s; ++s) {
		if (!isspace(*s))
			printf("%c", *s);
		else {
			printf("%c%s", *s, termcolor(colors[i++%len]));
		}
	}
	printf("%s", termcolor(SXC_TC_DEF));	// Reset to default color
}

