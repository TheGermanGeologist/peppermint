#include "algorithms/sorting_helpers.h"
#include "utils.h"
#include <string.h>

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


void map_farray_to_indices(float* array, int* indices, bool* visited, size_t length)
{
	// the reordering dictated by the indices array can be thought of
	// as a number of permutation chains
	// when we jump around the array following one re-mapped index to the next
	// we eventually arrive at an index we have already mapped
	// we then traverse the index array until we hit another index which we
	// havent mapped yet, which marks the start of a new permutation cycle
	// for visualization / application see 100 prisoners problem

	// visisted is a re-useable bookkeeper array provided by the caller to check if
	// we have already visited an index
	memset(visited, 0, length*sizeof(bool));
	float buffer;
	size_t starting_index , next_index, current_index;

	for (size_t i = 0; i < length; i++)
	{
		starting_index = i;
		current_index = starting_index;
		next_index = indices[starting_index];

		if (starting_index == next_index)
			visited[i] = true;

		if (visited[i])
			continue;

		buffer = array[current_index];
		while (next_index != starting_index)
		{
			array[current_index] = array[next_index];

			visited[current_index] = true;
			current_index = next_index;
			next_index = indices[current_index];
		}
		array[current_index] = buffer;
		visited[current_index] = true;
	}
}


void map_iarray_to_indices(int* array, int* indices, bool* visited, size_t length)
{
	memset(visited, 0, length*sizeof(bool));
	int buffer;
	size_t starting_index , next_index, current_index;

	for (size_t i = 0; i < length; i++)
	{
		starting_index = i;
		current_index = starting_index;
		next_index = indices[starting_index];

		if (starting_index == next_index)
			visited[i] = true;

		if (visited[i])
			continue;

		buffer = array[current_index];
		while (next_index != starting_index)
		{
			array[current_index] = array[next_index];

			visited[current_index] = true;
			current_index = next_index;
			next_index = indices[current_index];
		}
		array[current_index] = buffer;
		visited[current_index] = true;
	}
}

void map_barray_to_indices(bool* array, int* indices, bool* visited, size_t length)
{
	memset(visited, 0, length*sizeof(bool));
	bool buffer;
	size_t starting_index , next_index, current_index;

	for (size_t i = 0; i < length; i++)
	{
		starting_index = i;
		current_index = starting_index;
		next_index = indices[starting_index];

		if (starting_index == next_index)
			visited[i] = true;

		if (visited[i])
			continue;

		buffer = array[current_index];
		while (next_index != starting_index)
		{
			array[current_index] = array[next_index];

			visited[current_index] = true;
			current_index = next_index;
			next_index = indices[current_index];
		}
		array[current_index] = buffer;
		visited[current_index] = true;
	}
}


void map_varray_to_indices(void* array, int* indices, bool* visited, size_t length, size_t el_size)
{
	memset(visited, 0, length*sizeof(bool));
	void* buffer = malloc(el_size);
	size_t starting_index , next_index, current_index;

	char* byte_array = (char*)array;

	for (size_t i = 0; i < length; i++)
	{
		starting_index = i;
		current_index = starting_index;
		next_index = indices[starting_index];

		if (starting_index == next_index)
			visited[i] = true;

		if (visited[i])
			continue;

		memcpy(buffer, byte_array + current_index * el_size, el_size);
		while (next_index != starting_index)
		{
			memcpy(byte_array + current_index * el_size, 
                   byte_array + next_index * el_size, 
                   el_size);

			visited[current_index] = true;
			current_index = next_index;
			next_index = indices[current_index];
		}
		memcpy(byte_array + current_index * el_size, buffer, el_size);

		visited[current_index] = true;
	}
	free(buffer);
}