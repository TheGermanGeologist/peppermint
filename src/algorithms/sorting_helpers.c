#include "algorithms/sorting_helpers.h"
#include "utils.h"

int* new_index_array(size_t length)
{
	int* indices = (int*)allocate_vector((int)length,sizeof(int));

	for (size_t i = 0; i < length; i++)
	{
		indices[i] = (int)i;
	}
	return indices;
}


int check_sorting(float* array, size_t length)
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

int check_sorting_int(KeyType* array, size_t length)
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

void check_array_identity(float* array1, float* array2, size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		if (array1[i] != array2[i])
		{
			printf("Error: arrays not identical at index %zi, array1=%f,array2=%f\n", i, array1[i], array2[i]);
		}

	}

}