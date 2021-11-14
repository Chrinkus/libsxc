#include "sxc_utils.h"

#include <ctype.h>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// inline symbols

int charmap_get_count(const struct Charmap* cm, char ch);
 
struct Charcount* charmap_get_index(const struct Charmap* cm, size_t index);

void charmap_inc(struct Charmap* cm, char ch);

void charmap_sort(struct Charmap* cm);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// definitions

int charcount_cmp(const void* a, const void* b)
{
	const struct Charcount* cca = (const struct Charcount*)a;
	const struct Charcount* ccb = (const struct Charcount*)b;

	return ccb->count - cca->count;
}

struct Charcount* charmap_init(struct Charmap* cm, enum SXC_Charset charset)
{
	switch (charset) {
	case SXC_ALPHA_LOWER:	cm->num_chars = 26;	cm->zero = 'a';	break;
	case SXC_ALPHA_UPPER:	cm->num_chars = 26;	cm->zero = 'A';	break;
	case SXC_DIGITS:	cm->num_chars = 10;	cm->zero = '0';	break;
	}

	cm->charset = charset;
	cm->charcounts = malloc(sizeof(struct Charcount) * cm->num_chars);

	if (cm->charcounts)
		for (size_t i = 0; i < cm->num_chars; ++i)
			cm->charcounts[i] = charcount_init(cm->zero + i);

	return cm->charcounts;
}

void charmap_free(struct Charmap* cm)
{
	free(cm->charcounts);
	cm->num_chars = 0;
}

void charmap_count_chars(struct Charmap* cm, const char* s)
{
	for ( ; *s; ++s)
		switch(cm->charset) {
		case SXC_ALPHA_LOWER:
			if (isalpha(*s) && islower(*s))
				charmap_inc(cm, *s);
			break;
		case SXC_ALPHA_UPPER:
			if (isalpha(*s) && isupper(*s))
				charmap_inc(cm, *s);
			break;
		case SXC_DIGITS:
			if (isdigit(*s))
				charmap_inc(cm, *s);
			break;
		default:
			// its ok to read other characters
			break;
		}
}

struct Charcount* charmap_find(struct Charmap* cm, char ch)
{
	for (struct Charcount* p = cm->charcounts, * sen = p + cm->num_chars;
			p != sen; ++p)
		if (p->ch == ch)
			return p;

	return NULL;
}

