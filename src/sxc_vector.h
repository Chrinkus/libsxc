#pragma once

/**
 * Generic Vector solution
 *
 * All of these macros expect a vector struct of the following definition:
 *
 * struct TYPE_vector {
 * 	size_t siz;
 * 	size_t cap;
 * 	TYPE*  vec;
 * };
 */

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// private

enum SXC_Vector_Scalars {
	SXC_VECTOR_INITIAL_CAP = 8,
	SXC_VECTOR_GROWTH_RATE = 2,
};

#define sxc_vector_place(v, val) (v)->vec[(v)->siz++] = (val)

#define sxc_vector_grow(v)						\
	do {								\
		size_t new_cap = (v)->cap * SXC_VECTOR_GROWTH_RATE;	\
		(v)->vec = realloc((v)->vec,				\
				sizeof(*(v)->vec) * new_cap);		\
		(v)->cap = new_cap;					\
	} while (0)

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// public

#define sxc_vector_init(v)						\
	do {								\
		(v)->siz = 0;						\
		(v)->cap = SXC_VECTOR_INITIAL_CAP;			\
		(v)->vec = malloc(sizeof(*(v)->vec) * (v)->cap);	\
	} while (0)

/**
 * Sets 'siz' and 'cap' to 0 and frees the 'vec' pointer.
 */
#define sxc_vector_free(v)						\
	do {								\
		(v)->siz = 0;						\
		(v)->cap = 0;						\
		free((v)->vec);						\
	} while (0)

/**
 * Frees all elements of the vector then calls normal free on vector.
 *
 * Good for vectors of malloc'd strings and such.
 */
#define sxc_vector_freep(v)						\
	do {								\
		for (size_t i = 0; i < (v)->siz; ++i)			\
			free((v)->vec[i]);				\
		sxc_vector_free((v));					\
	} while (0)

#define sxc_vector_size(v) (v)->siz

#define sxc_vector_get(v, index) (v)->vec[(index)]

#define sxc_vector_getp(v, index) &(v)->vec[(index)]

/**
 * Push a value onto the end of the vector. Resize as necessary.
 */
#define sxc_vector_push(v, val)						\
	do {								\
		if ((v)->siz == (v)->cap)				\
			sxc_vector_grow((v));				\
		sxc_vector_place((v), (val));				\
	} while (0)

/**
 * Add an element to the vector and set 'p' to point to it.
 */
#define sxc_vector_emplace(v, p)						\
	do {								\
		if ((v)->siz == (v)->cap)				\
			sxc_vector_grow((v));				\
		(p) = sxc_vector_getp((v), (v)->siz);			\
		(v)->siz++;						\
	} while (0)	

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// algorithms

#define sxc_vector_foreach(v, func)					\
	do {								\
		for (size_t i = 0; i < (v)->siz; ++i)			\
			func(&(v)->vec[i]);				\
	} while (0)

#define sxc_vector_copy(dst, src)					\
	do {								\
		(dst)->vec = malloc(sizeof(*(src)->vec) * (src)->siz);	\
		(dst)->cap = (src)->siz;				\
		(dst)->siz = 0;						\
		for (size_t i = 0; i < (src)->siz; ++i)			\
			sxc_vector_place((dst), (src)->vec[i]);	\
	} while (0)

#define sxc_vector_find(v, tar, cmp, found)				\
	do {								\
		for (size_t i = 0; i < (v)->siz; ++i)			\
			if (cmp(&(v)->vec[i], tar) == 0) {		\
				found = sxc_vector_getp((v), i);	\
				break;					\
			}						\
	} while (0)

#define sxc_vector_sort(v, cmp)						\
	do {								\
		qsort((v)->vec, (v)->siz, sizeof(*(v)->vec), cmp);	\
	} while (0)

