#pragma once

#include <stdlib.h>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// Charcount - for counting occurances of characters.

struct Charcount {
	char ch;
	short count;
};

#define charcount_init(c) (struct Charcount){ .ch = (c), .count = 0 }

int charcount_cmp(const void* a, const void* b);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// Charmap - array of contiguous character counts
//
// Charmaps exist in two states, pre and post sorted. When counting characters
// we are in the pre-sort phase; Charcounts can be looked up randomly by
// subtracting from the 'zero' member. After sorting (by count) we can only
// look up specific chars with charmap_find, a linear search.

enum SXC_Charset {
	SXC_ALPHA_LOWER,	// a-z
	SXC_ALPHA_UPPER,	// A-Z
	SXC_DIGITS,		// 0-9
};

struct Charmap {
	enum SXC_Charset charset;
	char zero;
	struct Charcount* charcounts;
	size_t num_chars;
};

struct Charcount* charmap_init(struct Charmap* cm, enum SXC_Charset charset);

void charmap_free(struct Charmap* cm);

void charmap_count_chars(struct Charmap* cm, const char* s);

struct Charcount* charmap_find(struct Charmap* cm, char ch);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// Charmap inlines (symbols in sxc_utils.c)

inline
int charmap_get_count(const struct Charmap* cm, char ch)
{
	return cm->charcounts[ch - cm->zero].count;
}
 
inline
struct Charcount* charmap_get_index(const struct Charmap* cm, size_t index)
{
	return &cm->charcounts[index];
}

inline
void charmap_inc(struct Charmap* cm, char ch)
{
	++cm->charcounts[ch - cm->zero].count;
}

inline
void charmap_sort(struct Charmap* cm)
{
	qsort(cm->charcounts, cm->num_chars, sizeof(struct Charcount),
			charcount_cmp);
}

