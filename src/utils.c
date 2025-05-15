#include "utils.h"


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