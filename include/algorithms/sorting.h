#pragma once


// void flex_sort(float* array, size_t length); // future wrapper for different sorting algos

// Quick Sort

void recursive_qsort(float* array, int i_start, int i_end);
void iterative_qsort(float* array, size_t length);
inline int get_pivot(float* array, int i_start, int i_end);


// Insertion Sort

void insertion_sort(float* array, size_t length);


// Heap Sort

void heap_sort(float* array, size_t length);


