#include "sxc_string.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// inline symbols

size_t sxc_string_size(const struct sxc_string* s);

const char* sxc_string_str(const struct sxc_string* s);

char sxc_string_head(const struct sxc_string* s);
char sxc_string_tail(const struct sxc_string* s);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// private

enum sxc_string_defaults {
	SXC_STRING_DEFAULT_CAPACITY = 16,
	SXC_STRING_GROWTH_RATE = 2,
};

static char* sxc_string_resize(struct sxc_string* s)
{
	size_t new_cap = s->cap > 0 ? s->cap * SXC_STRING_GROWTH_RATE
		: SXC_STRING_DEFAULT_CAPACITY;
	char* p = realloc(s->str, new_cap);
	if (p) {
		s->str = p;
		s->cap = new_cap;
	}
	return p;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// public

char* sxc_string_init(struct sxc_string* s)
{
	if ((s->str = malloc(SXC_STRING_DEFAULT_CAPACITY))) {
		s->str[0] = '\0';
		s->siz = 0;
		s->cap = SXC_STRING_DEFAULT_CAPACITY;
	}
	return s->str;
}

void sxc_string_free(struct sxc_string* s)
{
	free(s->str);
	s->str = NULL;
	s->siz = 0;
	s->cap = 0;
}

char* sxc_string_push(struct sxc_string* s, int ch)
{
	if (s->siz + 1 == s->cap && !sxc_string_resize(s))
		return NULL;
	s->str[s->siz++] = ch;
	s->str[s->siz] = '\0';
	return s->str;
}

void sxc_string_clear(struct sxc_string* s)
{
	for (char* p = s->str; *p; ++p)
		*p = '\0';

	s->siz = 0;
}

int sxc_getline(FILE* fp, struct sxc_string* s)
{
	int count = 0;
	for (int c; (c = fgetc(fp)) != EOF && c != '\n'; ++count)
		sxc_string_push(s, c);
	return count;
}

