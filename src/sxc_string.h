#pragma once

#include <stdlib.h>

typedef struct sxc_string String;
struct sxc_string {
	char* str;
	size_t siz;
	size_t cap;
};

char* sxc_string_init(String* s);

void sxc_string_free(String* s);

char* sxc_string_push(String* s, int ch);

