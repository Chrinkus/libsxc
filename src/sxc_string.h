#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct sxc_string String;
struct sxc_string {
	char* str;
	size_t siz;
	size_t cap;
};

char* sxc_string_init(String* s);

void sxc_string_free(String* s);

inline
size_t sxc_string_size(const String* s)
{
	return s->siz;
}

inline
const char* sxc_string_str(const String* s)
{
	return s->str;
}

inline
char sxc_string_head(const String* s)
{
	return s->str[0];
}

inline
char sxc_string_tail(const String* s)
{
	return s->str[s->siz-1];
}

char* sxc_string_push(String* s, int ch);

void sxc_string_clear(String* s);

int sxc_getline(FILE* fp, String* s);

