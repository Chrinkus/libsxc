#pragma once

#include <stdlib.h>
#include <stdint.h>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// sxc_charcount - for counting occurances of characters.

struct sxc_charcount {
	int64_t count;
	char ch;
};

#define sxc_charcount_init(c) (struct sxc_charcount){ .ch = (c), .count = 0 }

int sxc_charcount_cmp(const void* a, const void* b);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// sxc_charmap - array of contiguous character counts
//
// sxc_charmaps exist in two states, pre and post sorted. When counting
// characters we are in the pre-sort phase; sxc_charcounts can be looked up
// randomly by subtracting from the 'zero' member. After sorting (by count) we
// can only look up specific chars with sxc_charmap_find, a linear search.

enum sxc_charset {
	SXC_ALPHA_LOWER,	// a-z
	SXC_ALPHA_UPPER,	// A-Z
	SXC_DIGITS,		// 0-9
};

struct sxc_charmap {
	enum sxc_charset charset;
	char zero;
	struct sxc_charcount* cc;
	size_t num_chars;
};

struct sxc_charcount* sxc_charmap_init(struct sxc_charmap* cm,
		enum sxc_charset charset);

void sxc_charmap_free(struct sxc_charmap* cm);

void sxc_charmap_count_chars(struct sxc_charmap* cm, const char* s);

struct sxc_charcount* sxc_charmap_find(struct sxc_charmap* cm, char ch);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// sxc_charmap inlines (symbols in sxc_utils.c)

inline
int64_t sxc_charmap_get_count(const struct sxc_charmap* cm, char ch)
{
	return cm->cc[ch - cm->zero].count;
}
 
inline
struct sxc_charcount* sxc_charmap_get_index(const struct sxc_charmap* cm,
		size_t index)
{
	return &cm->cc[index];
}

inline
void sxc_charmap_inc(struct sxc_charmap* cm, char ch)
{
	++cm->cc[ch - cm->zero].count;
}

inline
void sxc_charmap_add(struct sxc_charmap* cm, char ch, int64_t n)
{
	cm->cc[ch - cm->zero].count += n;
}

inline
void sxc_charmap_sort(struct sxc_charmap* cm)
{
	qsort(cm->cc, cm->num_chars, sizeof(struct sxc_charcount),
			sxc_charcount_cmp);
}

inline
struct sxc_charcount* sxc_charmap_sorted_most(const struct sxc_charmap* cm)
{
	return &cm->cc[0];
}

inline
struct sxc_charcount* sxc_charmap_sorted_least(const struct sxc_charmap* cm)
{
	struct sxc_charcount* p = &cm->cc[cm->num_chars-1];
	for ( ; p >= cm->cc; --p)
		if (p->count != 0)
			break;
	return p;
}

