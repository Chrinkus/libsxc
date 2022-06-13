#pragma once

#include <stddef.h>

#ifndef SXC_UNUSED
#define SXC_UNUSED(x) (void)(x)
#endif

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

/**
 * Absolute blackest of magic. This macro sets up a new vector type in the
 * current file.
 *
 * @param name	Desired name of the new vector type. It is strongly suggested
 * 		that this name is unique and indicates the type of the elements
 * 		contained within.
 * @param typ	The type of object that this vector will contain.
 */
#define SXC_NEW_VECTOR(name, type)					\
	typedef struct {						\
		size_t siz;						\
		size_t cap;						\
		type* vec;						\
	} name

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
 * Transfer's ownership of memory allocation to pointer 'p'. Set cap to
 * zero. Size is left as is for querying if needed. Vector may be init'd
 * from this state.
 */
#define sxc_vector_xfer(v, p)						\
	do {								\
		(p) = (v)->vec;						\
		(v)->vec = NULL;					\
		(v)->cap = 0;						\
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

#define sxc_vector_getp(v, index) (&(v)->vec[(index)])

/**
 * Pop an element off the end of the vector. Does not erase popped data.
 */
#define sxc_vector_pop(v, p)						\
	do {								\
		if ((v)->siz > 0)					\
			(p) = (v)->vec[--(v)->siz];			\
	} while (0)

/**
 * Pop front, for when you should have written a queue..
 */
#define sxc_vector_pop_front(v, p)					\
	do {								\
		if ((v)->siz > 0) {					\
			(p) = (v)->vec[0];				\
			for (size_t i = 1; i < (v)->siz; ++i)		\
				(v)->vec[i-1] = (v)->vec[i];		\
			--(v)->siz;					\
		}							\
	} while (0)

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

// typedef void (*foreach_func)(type*, void*)

#define sxc_vector_foreach(v, func, data)				\
	do {								\
		for (size_t i = 0; i < (v)->siz; ++i)			\
			func(&(v)->vec[i], (data));			\
	} while (0)

#define sxc_vector_copy(dst, src)					\
	do {								\
		(dst)->vec = malloc(sizeof(*(src)->vec) * (src)->siz);	\
		(dst)->cap = (src)->siz;				\
		(dst)->siz = 0;						\
		for (size_t i = 0; i < (src)->siz; ++i)			\
			sxc_vector_place((dst), (src)->vec[i]);		\
	} while (0)

// typedef int (*cmp)(const void*, const void*)

#define sxc_vector_find(v, tar, cmp, found)				\
	do {								\
		for (size_t i = 0; i < (v)->siz; ++i)			\
			if (cmp(&(v)->vec[i], (tar)) == 0) {		\
				(found) = sxc_vector_getp((v), i);	\
				break;					\
			}						\
	} while (0)

#define sxc_vector_sort(v, cmp)						\
	do {								\
		qsort((v)->vec, (v)->siz, sizeof(*(v)->vec), cmp);	\
	} while (0)

#define sxc_vector_binary_search(v, tar, cmp, found)			\
	do {								\
		for (int _beg = 0, _end = (v)->siz, _mid = _end / 2;	\
				!found && _beg < _end;			\
				_mid = (_beg + _end) / 2) {		\
			int res = cmp(&(v)->vec[_mid], (tar));		\
			if (res == 0)					\
				found = &(v)->vec[_mid];		\
			else if (res > 0)				\
				_end = _mid;				\
			else						\
				_beg = _mid + 1;			\
		}							\
	} while (0)

