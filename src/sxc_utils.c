#include "sxc_utils.h"

#include <ctype.h>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// inline symbols

int64_t sxc_charmap_get_count(const struct sxc_charmap* cm, char ch);
 
struct sxc_charcount* sxc_charmap_get_index(const struct sxc_charmap* cm,
		size_t index);

void sxc_charmap_inc(struct sxc_charmap* cm, char ch);

void sxc_charmap_add(struct sxc_charmap* cm, char ch, int64_t n);

void sxc_charmap_sort(struct sxc_charmap* cm);

struct sxc_charcount* sxc_charmap_sorted_most(const struct sxc_charmap* cm);
struct sxc_charcount* sxc_charmap_sorted_least(const struct sxc_charmap* cm);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// definitions

int sxc_charcount_cmp(const void* a, const void* b)
{
	const struct sxc_charcount* cca = (const struct sxc_charcount*)a;
	const struct sxc_charcount* ccb = (const struct sxc_charcount*)b;

	int64_t res = ccb->count - cca->count;

	return res > 0 ? 1 : res < 0 ? -1 : 0;
}

struct sxc_charcount* sxc_charmap_init(struct sxc_charmap* cm,
		enum sxc_charset charset)
{
	switch (charset) {
	case SXC_ALPHA_LOWER:	cm->num_chars = 26;	cm->zero = 'a';	break;
	case SXC_ALPHA_UPPER:	cm->num_chars = 26;	cm->zero = 'A';	break;
	case SXC_DIGITS:	cm->num_chars = 10;	cm->zero = '0';	break;
	}

	cm->charset = charset;
	cm->cc = malloc(sizeof(struct sxc_charcount) * cm->num_chars);

	if (cm->cc)
		for (size_t i = 0; i < cm->num_chars; ++i)
			cm->cc[i] = sxc_charcount_init(cm->zero + i);

	return cm->cc;
}

void sxc_charmap_free(struct sxc_charmap* cm)
{
	free(cm->cc);
	cm->num_chars = 0;
}

void sxc_charmap_count_chars(struct sxc_charmap* cm, const char* s)
{
	for ( ; *s; ++s)
		switch(cm->charset) {
		case SXC_ALPHA_LOWER:
			if (isalpha(*s) && islower(*s))
				sxc_charmap_inc(cm, *s);
			break;
		case SXC_ALPHA_UPPER:
			if (isalpha(*s) && isupper(*s))
				sxc_charmap_inc(cm, *s);
			break;
		case SXC_DIGITS:
			if (isdigit(*s))
				sxc_charmap_inc(cm, *s);
			break;
		default:
			// its ok to read other characters
			break;
		}
}

struct sxc_charcount* sxc_charmap_find(struct sxc_charmap* cm, char ch)
{
	for (struct sxc_charcount* p = cm->cc, * sen = p + cm->num_chars;
			p != sen; ++p)
		if (p->ch == ch)
			return p;

	return NULL;
}

