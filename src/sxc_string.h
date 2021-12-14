#pragma once

#include <stdlib.h>
#include <stdio.h>

struct sxc_string {
	char* str;
	size_t siz;
	size_t cap;
};

char* sxc_string_init(struct sxc_string* s);

void sxc_string_free(struct sxc_string* s);

inline
size_t sxc_string_size(const struct sxc_string* s)
{
	return s->siz;
}

inline
const char* sxc_string_str(const struct sxc_string* s)
{
	return s->str;
}

inline
char sxc_string_head(const struct sxc_string* s)
{
	return s->str[0];
}

inline
char sxc_string_tail(const struct sxc_string* s)
{
	return s->str[s->siz-1];
}

char* sxc_string_push(struct sxc_string* s, int ch);

void sxc_string_clear(struct sxc_string* s);

int sxc_getline(FILE* fp, struct sxc_string* s);

