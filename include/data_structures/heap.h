#pragma once

#include <stdlib.h>
#include "utils.h"


// inline helper functions to get indices
inline static size_t left_node		(size_t i) { return 2*i + 1; }
inline static size_t right_node		(size_t i) { return 2*i + 2; }

inline static size_t parent_node	(size_t i)
{
	if (i == 0) return i;

	return (i-1)/2;
}

inline static size_t first_parent  	(size_t n)
{
	if (n < 2) return 0;

	return (n/2) -1;
}


void heapify(float* array, size_t i, size_t n);

void downsift(float* array, size_t i, size_t n);

void upsift(float* array, size_t i, size_t n);

void heapify_ki(int* key_arr, size_t i, size_t n);

void downsift_ki(int* key_arr, size_t i, size_t n);
