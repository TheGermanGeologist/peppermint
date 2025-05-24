#pragma once

#include "utils.h"

// void flex_sort(float* array, size_t length); // future wrapper for different sorting algos

// Quick Sort

void recursive_qsort(float* array, int i_start, int i_end);
void iterative_qsort(float* array, size_t length);
inline int get_pivot(float* array, int i_start, int i_end);


// Insertion Sort

void insertion_sort(float* array, size_t length);


// Heap Sort

void heap_sort(float* array, size_t length);

// Adaptive sorting

void adapt_sort(float* array, size_t length);


inline int get_pivot_ki(KeyType* key_arr, int* index_arr, int i_start, int i_end);
void insertion_sort_ki(KeyType* key_arr, int* index_arr, size_t length);
void heap_sort_ki(KeyType* key_arr, int* index_arr, size_t length);
void adapt_sort_ki(KeyType* key_arr, int* index_arr, size_t length);
