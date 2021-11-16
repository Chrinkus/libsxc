#pragma once

#include <stddef.h>

// sxc_vectors for standard 'C' types

struct Int_vector {
	size_t siz;
	size_t cap;
	int* vec;
};

struct Double_vector {
	size_t siz;
	size_t cap;
	double* vec;
};

struct Charp_vector {
	size_t siz;
	size_t cap;
	char** vec;
};

