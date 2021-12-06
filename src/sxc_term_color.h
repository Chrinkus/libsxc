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
 *
 * Middle Mode:
 * TC<B>MAG
 * - N	normal
 * - B	bold
 * - BG	background
 * -	none for RES and DEF
 * - X	aixterm bright
 *
 * Special codes:
 * RES = Reset code
 * DEF = Default code
 *
 * Note:
 * I agonized over the macro names. Since they're inline I wanted them to 
 * be short enough to be "usable" but still unique enough to avoid clashes.
 */
#define TCRES	"\033[0m"	
#define TCDEF	"\033[0;39m"
#define TCBGDEF	"\033[0;49m"

#define TCDIM	"\033[2m"
#define TCRDIM	"\033[22m"
#define TCBLNK	"\033[5m"
#define TCRBLNK	"\033[25m"
#define TCINV	"\033[7m"
#define TCRINV	"\033[27m"

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

#define TCBGBLK	"\033[40m"
#define TCBGRED	"\033[41m"
#define TCBGGRN	"\033[42m"
#define TCBGYEL	"\033[43m"
#define TCBGBLU	"\033[44m"
#define TCBGMAG	"\033[45m"
#define TCBGCYN	"\033[46m"
#define TCBGWHT	"\033[47m"

// Experimental 256 colors
#define TC5YEL "\033[38;5;226m"
#define TC5ORG "\033[38;5;208m"
#define TC5GRY "\033[38;5;245m"

// Experimental bright colors
#define TCXBLK "\033[90m"
#define TCXRED "\033[91m"
#define TCXGRN "\033[92m"
#define TCXYEL "\033[93m"
#define TCXBLU "\033[94m"
#define TCXMAG "\033[95m"
#define TCXCYN "\033[96m"
#define TCXWHT "\033[97m"

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
	[SXC_TC_DEF]	= "\033[39m",
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
void sxc_termcolor_altc(const char* s, const int* colors, int len)
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
	printf("%s", termcolor(SXC_TC_RES));	// Reset to default color
}

void sxc_termcolor_altw(const char* s, const int* colors, int len)
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
	printf("%s", termcolor(SXC_TC_RES));	// Reset to default color
}

