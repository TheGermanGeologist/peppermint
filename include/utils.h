#pragma once

#include <stdlib.h>
#include <stdio.h>


//typedef int intasdf;


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

static inline void swap_values_ki(int* value1, int* value2)
{
	int swap = *value1;
	*value1 = *value2;
	*value2 = swap;
}

inline int cmpfunc (const void * a, const void * b) //what is it returning?
{
	float val_a = *(const float*)a; // Good practice to cast to const float*
    float val_b = *(const float*)b;

    if (val_a < val_b) {
        return -1; // a comes before b
    } else if (val_a > val_b) {
        return 1;  // a comes after b
    } else {
        return 0;  // a and b are equivalent
    }
}

inline int check_sorting(float* array, size_t length)
{
	int not_sorted = 0;
	for (size_t i = 0; i < length-1; i++)
	{
		if (array[i] > array[i+1])
		{
			printf("Error: array not sorted at index %zi, i=%f,i+1=%f\n",i,array[i],array[i+1]);
			not_sorted = 1;
		}
		
	}
	return not_sorted;
}

inline int check_sorting_int(int* array, size_t length)
{
	int not_sorted = 0;
	for (size_t i = 0; i < length-1; i++)
	{
		if (array[i] > array[i+1])
		{
			printf("Error: array not sorted at index %zi, i=%i,i+1=%i\n",i,array[i],array[i+1]);
			not_sorted = 1;
		}
		
	}
	return not_sorted;
}

inline void check_array_identity(float* array1, float* array2, size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		if (array1[i] != array2[i])
		{
			printf("Error: arrays not identical at index %zi, array1=%f,array2=%f\n", i, array1[i], array2[i]);
		}

	}

}

inline void init_rng(unsigned int seed) { srand(seed); }

int get_rand_int(int range_min, int range_max);
int get_rand_int_mod(int range_min, int range_max);
float get_rand_float(float range_min, float range_max);