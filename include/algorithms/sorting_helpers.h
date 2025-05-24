#pragma once

#include <stdio.h>

typedef int KeyType;

typedef struct 
{
	int lt;
	int gt;
} qsort_iterators;


int* new_index_array(size_t length);

static inline void swap_values(float* value1, float* value2)
{
	float swap = *value1;
	*value1 = *value2;
	*value2 = swap;
}

static inline void swap_values_ki(KeyType* value1, KeyType* value2)
{
	KeyType swap = *value1;
	*value1 = *value2;
	*value2 = swap;
}


static inline void swap_values_int(int* value1, int* value2)
{
	int swap = *value1;
	*value1 = *value2;
	*value2 = swap;
}


// for stdlib qsrot
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


int check_sorting(float* array, size_t length);

int check_sorting_int(KeyType* array, size_t length);

void check_array_identity(float* array1, float* array2, size_t length);