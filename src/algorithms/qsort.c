#include "algorithms/qsort.h"

#include <stdio.h>

inline void swap_values(float* value1, float* value2)
{
	float swap = *value1;
	*value1 = *value2;
	*value2 = swap;
}


inline int get_pivot(float* array, int i_start, int i_end)
{
	// median approach
	int i_middle = (i_end + i_start) / 2;
	// sort the three values at i_start, i_middle, i_end
	if (array[i_start] > array[i_middle])
		swap_values(&array[i_start], &array[i_middle]);
	if (array[i_middle] > array[i_end])
		swap_values(&array[i_middle], &array[i_end]);
	if (array[i_start] > array[i_middle])
		swap_values(&array[i_start], &array[i_middle]);

	return i_middle; // now use middle of range as pivot
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


void my_qsort(float* array, int i_start, int i_end)
{
	// check if nothing is left to do
	if (i_start == i_end)
		return;

	// if there are only two numbers left, sort them, then return
	if (i_end == i_start+1)
	{
		if (array[i_start] > array[i_end])
			swap_values(array + i_start, array + i_end);
		
		return;
	}

	// at least three numbers, get a pivot
	int pivot = get_pivot(array, i_start, i_end);

	// swap pivot and end so pivot is out of the way
	float pivot_value = array[pivot];
	swap_values(array + pivot, array + i_end);

	// now keep traversing each side of the pivot up and down and see if we have to swap
	int i_from_left, i_from_right;
	i_from_left = i_start; i_from_right = i_end - 1; // <- don't include the pivot
	
	while (1)
	{
		while (array[i_from_left] <= pivot_value)
			i_from_left++;
		
		while (array[i_from_right] > pivot_value)
			i_from_right--;
		
		if (i_from_left > i_from_right) // everything is sorted across the pivot
			break;

		swap_values(array + i_from_left, array + i_from_right);
	}

	// swap back the pivot
	swap_values(array + i_from_left, array + i_end);

	// recursive calls to quick sort
	// lower partition
	my_qsort(array,	i_start,		i_from_left-1	);
	my_qsort(array,	i_from_left+1,	i_end			);

	// finally, return
	return;
	
}


void insertion_sort(float* array, size_t length)
{
	int i_sorted = 0;
	int i_candidate = 1;
	int i_compare = i_sorted;

	while (i_sorted < length - 1)
	{
		float candidate_value = array[i_candidate];
		while (candidate_value < array[i_compare] && i_compare >= 0)
		{
			array[i_compare + 1] = array[i_compare];
			i_compare--;
		}
		array[i_compare + 1] = candidate_value;

		i_sorted++;
		i_candidate = i_sorted + 1;
		i_compare = i_sorted;
	}
	
}


inline static int left_node		(int i) { return 2*i + 1; }
inline static int right_node	(int i) { return 2*i + 2; }
inline static int parent_node	(int i) { return (i-1)/2; }