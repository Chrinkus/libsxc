#pragma once

#include <stddef.h>

struct SXC_Point {
	int x;
	int y;
};

struct SXC_Point_vector {
	size_t siz;
	size_t cap;
	struct SXC_Point* vec;
};

int sxc_point_cmp(const struct SXC_Point* a, const struct SXC_Point* b);

