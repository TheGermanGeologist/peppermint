#pragma once

void my_qsort(float* array, int i_start, int i_end);
void insertion_sort(float* array, size_t length);

void print_array_range(float* array, int i_start, int i_end);

void print_array(float* array, size_t length);

inline void swap_values(float* value1, float* value2);

inline int get_pivot(float* array, int i_start, int i_end);