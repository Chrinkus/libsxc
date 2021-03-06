#pragma once

#include <sxc_vector.h>

// sxc_vectors for standard 'C' types

SXC_NEW_VECTOR(Int_vector, int);

SXC_NEW_VECTOR(Double_vector, double);

SXC_NEW_VECTOR(Charp_vector, char*);
/*
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
*/

