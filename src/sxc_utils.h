#pragma once

#include <stdlib.h>
#include <stdint.h>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// Charcount - for counting occurances of characters.

struct Charcount {
	int64_t count;
	char ch;
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
int64_t charmap_get_count(const struct Charmap* cm, char ch)
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
void charmap_add(struct Charmap* cm, char ch, int64_t n)
{
	cm->charcounts[ch - cm->zero].count += n;
}

inline
void charmap_sort(struct Charmap* cm)
{
	qsort(cm->charcounts, cm->num_chars, sizeof(struct Charcount),
			charcount_cmp);
}

inline
struct Charcount* charmap_sorted_most(const struct Charmap* cm)
{
	return &cm->charcounts[0];
}

inline
struct Charcount* charmap_sorted_least(const struct Charmap* cm)
{
	struct Charcount* p = &cm->charcounts[cm->num_chars-1];
	for ( ; p >= cm->charcounts; --p)
		if (p->count != 0)
			break;
	return p;
}

