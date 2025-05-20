#include "utils.h"

#include <stdio.h>


void* allocate_vector(int length, size_t element_size)
{
	if (length <= 0 || element_size == 0)
						return NULL;

	void* new_vector =  (void*)malloc(length * element_size);

	if (!new_vector)    return NULL;
	else                return new_vector;
}

void free_vector(void* vector)
{
	free(vector);
	vector = NULL;
}

void** allocate_2D_array(int rows, int cols, size_t element_size)
{
	void** array = (void**)malloc(rows * sizeof(void*));

	if (!array)
		return NULL;

	for (int ii = 0; ii < rows; ii++)
	{
		array[ii] = (void*)malloc(cols * element_size);

		if (!array[ii])
		{
			for (int jj = 0; jj < ii; jj++)
				free(array[jj]);

			free(array);
			return NULL;
		}
	}
	
	return array;

}

void free_2D_array(void** array, int rows)
{
	if (array == NULL || rows <= 0)
		return;

	for (int ii = 0; ii < rows; ii++)
		free_vector(array[ii]);

	free(array);
	array = NULL;
}



void print_array_range(float* array, int i_start, int i_end)
{
	for (int i = i_start; i <= i_end; i++)
		printf("%f ",array[i]);
	
	printf("\n");
	
	return;
}

void print_array(float* array, size_t length)
{
	for (size_t i = 0; i < length; i++)
		printf("%f ",array[i]);
	
	printf("\n");
	
	return;
}


int get_rand_int(int range_min, int range_max)
{
	return range_min + rand() / ( (RAND_MAX + 1u) / (range_max - range_min + 1) );
}

int get_rand_int_mod(int range_min, int range_max)
{
	return range_min + rand() % (range_max - range_min + 1);
}

float get_rand_float(float range_min, float range_max)
{
	return range_min + ((float)rand() / (float)(RAND_MAX + 1u)) * (range_max - range_min);
}
