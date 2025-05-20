#pragma once

#include <stdlib.h>


void* allocate_vector(int length, size_t element_size);

void free_vector(void* vector);

void** allocate_2D_array(int rows, int cols, size_t element_size);

void free_2D_array(void** array, int rows);



void print_array_range(float* array, int i_start, int i_end);

void print_array(float* array, size_t length);



static inline void swap_values(float* value1, float* value2)
{
	float swap = *value1;
	*value1 = *value2;
	*value2 = swap;
}


inline void init_rng(unsigned int seed) { srand(seed); }

int get_rand_int(int range_min, int range_max);
int get_rand_int_mod(int range_min, int range_max);
float get_rand_float(float range_min, float range_max);