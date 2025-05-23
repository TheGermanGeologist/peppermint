#include "algorithms/sorting.h"
#include "data_structures/heap.h"
#include "utils.h"

#include <stdio.h>

// for iterative_qsort, probably still quite conservative
#define STACK_ALLOC_THRESHOLD 1024

#define INSERTION_SWITCH 20

#define STACK_BAILOUT_RATIO 5

/**
 * @brief Defines iterators for quicksort partitioning.
 */
typedef struct 
{
	int lt;
	int gt;
} qsort_iterators;


/**
 * @brief Partitions a subarray using the 3-way (Dutch National Flag) partitioning scheme.
 * @param array The array to be partitioned.
 * @param i_start The starting index of the subarray.
 * @param i_end The ending index of the subarray.
 * @return A struct containing the lt (less than) and gt (greater than) iterators.
 */
qsort_iterators qsort_core(float* array, int i_start, int i_end)
{
	// at least three numbers, get a pivot
	int pivot = get_pivot(array, i_start, i_end);

	// swap pivot and end so pivot is out of the way
	float pivot_value = array[pivot];
	swap_values(array + pivot, array + i_end);

	// now keep traversing each side of the pivot up and down and see if we have to swap
	int lt, i, gt;
	lt = i = i_start; gt = i_end; // include the pivot, dutch flag should handle it
	
	while (i <= gt)
	{
		if (array[i] < pivot_value)
		{
			swap_values(array + i, array + lt);
			lt++;
			i++;
		}
		else if (array[i] > pivot_value)
		{
			swap_values(array + i, array + gt);
			gt--;
		}
		else
		{
			i++;
		}
	}
	qsort_iterators result = {lt,gt};
	return result;
}



/**
 * @brief Selects a pivot element from a subarray using the median-of-three method.
 * @param array The array containing the subarray.
 * @param i_start The starting index of the subarray.
 * @param i_end The ending index of the subarray.
 * @return The index of the pivot element.
 */
inline int get_pivot(float* array, int i_start, int i_end)
{
	// median approach
	int i_middle = (i_end + i_start) / 2;
	// sort the three values at i_start, i_middle, i_end
	if (array[i_start] > array[i_middle])
		swap_values(array+i_start, array+i_middle);
	if (array[i_middle] > array[i_end])
		swap_values(array+i_middle, array+i_end);
	if (array[i_start] > array[i_middle])
		swap_values(array+i_start, array+i_middle);

	return i_middle; // now use middle of range as pivot
}



/**
 * @brief Sorts an array of floats using the recursive Quicksort algorithm.
 * @param array The array to be sorted.
 * @param i_start The starting index of the portion of the array to sort.
 * @param i_end The ending index of the portion of the array to sort.
 */
void recursive_qsort(float* array, int i_start, int i_end)
{
	// check if nothing is left to do
	if (i_start >= i_end)
		return;

	// if there are only two numbers left, sort them, then return
	if (i_end == i_start+1)
	{
		if (array[i_start] > array[i_end])
			swap_values(array + i_start, array + i_end);
		
		return;
	}

	qsort_iterators result = qsort_core(array, i_start, i_end);

	// recursive calls to quick sort
	recursive_qsort(array,	i_start,	result.lt - 1	); // lower partition
	recursive_qsort(array,	result.gt + 1,		i_end	); // upper partition

	// finally, return
	return;
}



/**
 * @brief Sorts an array of floats using the iterative Quicksort algorithm.
 * @param array The array to be sorted.
 * @param length The number of elements in the array.
 */
void iterative_qsort(float* array, size_t length)
{
	int* stack = NULL;
	int top = -1;

	// Decide whether to allocate the stack on the heap or the stack
	if (length <= STACK_ALLOC_THRESHOLD)
	{
		// Allocate the stack on the stack (hehe)
		int stack_local[STACK_ALLOC_THRESHOLD];
		stack = stack_local;
	}
	else
		stack = (int*)allocate_vector((int)length, sizeof(int));

	// Push the initial range (entire array) onto the stack
	stack[++top] = 0;
	stack[++top] = (int)length - 1;

	// Process ranges until the stack is empty
	while (top >= 0)
	{
		// Pop a range from the stack
		int i_end = stack[top--];
		int i_start = stack[top--];

		// already sorted
		if (i_start >= i_end)
			continue;

		qsort_iterators result = qsort_core(array, i_start, i_end);

		// Push the two new ranges onto the stack
		stack[++top] = i_start;			// Lower partition
		stack[++top] = result.lt - 1;

		stack[++top] = result.gt + 1;	// Upper partition
		stack[++top] = i_end;
	}

	if (length > STACK_ALLOC_THRESHOLD)
		free(stack);
}



/**
 * @brief Sorts an array of floats using the Insertion Sort algorithm.
 * @param array The array to be sorted.
 * @param length The number of elements in the array.
 */
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



/**
 * @brief Sorts an array of floats using the Heapsort algorithm.
 * @param array The array to be sorted.
 * @param length The number of elements in the array.
 */
void heap_sort(float* array, size_t length)
{
	if (length < 2)
		return;

	// first, build max heap
	heapify(array, first_parent(length), length);

	int heap_size = (int)length;
	// now recursively extract the root, swap back, reduce heap_size and downsift root

	while (heap_size > 1)
	{
		swap_values(array, array+(heap_size-1));
		heap_size--;
		downsift(array, 0, heap_size);
	}

}



/**
 * @brief Sorts an array of floats using an adaptive sorting algorithm.
 * Switches between Quicksort, Insertion Sort, and Heapsort based on heuristics.
 * @param array The array to be sorted.
 * @param length The number of elements in the array.
 */
void adapt_sort(float* array, size_t length)
{
	if (length < 2)
		return;
	
	if (length < INSERTION_SWITCH)
	{
		insertion_sort(array, length);
		return;
	}

	// start with the iterative qsort approach
	int critical_stack_size = (int)length / STACK_BAILOUT_RATIO;

	int* stack = NULL;
	int top = -1;

	// Decide whether to allocate the stack on the heap or the stack
	if ((critical_stack_size + 4) <= STACK_ALLOC_THRESHOLD)
	{
		// Allocate the stack on the stack (hehe)
		int stack_local[STACK_ALLOC_THRESHOLD];
		stack = stack_local;
	}
	else
		stack = (int*)allocate_vector((critical_stack_size + 4), sizeof(int));

	// Push the initial range (entire array) onto the stack
	stack[++top] = 0;
	stack[++top] = (int)length - 1;

	// Process ranges until the stack is empty
	while (top >= 1) // should always be >= 1 because we always pop two values from the stack
	{
		// Pop a range from the stack
		int i_end = stack[top--];
		int i_start = stack[top--];

		// already sorted
		if (i_start >= i_end)
			continue;

		int current_partition_size = i_end - i_start + 1;

		if (current_partition_size <= INSERTION_SWITCH)
		{
			insertion_sort(array+i_start,current_partition_size);
			continue;
		}

		qsort_iterators result = qsort_core(array, i_start, i_end);

		// Push the two new ranges onto the stack
		// further optimization: push larger partition first
		int left_start = i_start;
		int left_end = result.lt - 1;
		int right_start = result.gt + 1;
		int right_end = i_end;

		size_t left_size = (left_start <= left_end) ? (size_t)left_end - left_start + 1 : 0;
		size_t right_size = (right_start <= right_end) ? (size_t)right_end - right_start + 1 : 0;

		if (left_size > right_size) {
			// Push larger (left) partition first
			if (left_size > 0) {
				stack[++top] = left_start;
				stack[++top] = left_end;
			}
			// Push smaller (right) partition second (to be processed next)
			if (right_size > 0) {
				stack[++top] = right_start;
				stack[++top] = right_end;
			}
		} else {
			// Push larger (right) partition first
			if (right_size > 0) {
				stack[++top] = right_start;
				stack[++top] = right_end;
			}
			// Push smaller (left) partition second
			if (left_size > 0) {
				stack[++top] = left_start;
				stack[++top] = left_end;
			}
		}

		if (top < 1)
			continue; // fast forward to loop termination

		int partition_length = stack[top] - stack[top-1] + 1;

		// after one iteration, check conditions for switching to other sorting algos
		if (partition_length <= INSERTION_SWITCH && partition_length > 1)
		{
			insertion_sort(array+stack[top-1], partition_length);
			stack[top] = 0;
			stack[top-1] = 0;
			top -= 2;

		}
		else if (top > critical_stack_size)
		{
			heap_sort(array+stack[top-1], partition_length);
			stack[top] = 0;
			stack[top-1] = 0;
			top -= 2;
		}
		
	}

	if ((critical_stack_size + 4) > STACK_ALLOC_THRESHOLD)
		free(stack);
	
}

// END GENERIC SORTING FUNCTIONS









// SPECIALIZED VERSIONS OF ALL FUNCTIONS FOR SORTING PARTICLES BASED ON MORTON CODES


qsort_iterators qsort_core_ki(int* key_arr, int i_start, int i_end)
{
	// at least three numbers, get a pivot
	int pivot = get_pivot_ki(key_arr, i_start, i_end);

	// swap pivot and end so pivot is out of the way
	int pivot_value = key_arr[pivot];
	swap_values_ki(key_arr + pivot, key_arr + i_end);

	// now keep traversing each side of the pivot up and down and see if we have to swap
	int lt, i, gt;
	lt = i = i_start; gt = i_end; // include the pivot, dutch flag should handle it
	
	while (i <= gt)
	{
		if (key_arr[i] < pivot_value)
		{
			swap_values_ki(key_arr + i, key_arr + lt);
			lt++;
			i++;
		}
		else if (key_arr[i] > pivot_value)
		{
			swap_values_ki(key_arr + i, key_arr + gt);
			gt--;
		}
		else
		{
			i++;
		}
	}
	qsort_iterators result = {lt,gt};
	return result;
}



inline int get_pivot_ki(int* key_arr, int i_start, int i_end)
{
	// median approach
	int i_middle = (i_end + i_start) / 2;
	// sort the three values at i_start, i_middle, i_end
	if (key_arr[i_start] > key_arr[i_middle])
		swap_values_ki(key_arr+i_start, key_arr+i_middle);
	if (key_arr[i_middle] > key_arr[i_end])
		swap_values_ki(key_arr+i_middle, key_arr+i_end);
	if (key_arr[i_start] > key_arr[i_middle])
		swap_values_ki(key_arr+i_start, key_arr+i_middle);

	return i_middle; // now use middle of range as pivot
}


void insertion_sort_ki(int* key_arr, size_t length)
{
	int i_sorted = 0;
	int i_candidate = 1;
	int i_compare = i_sorted;

	while (i_sorted < length - 1)
	{
		int candidate_value = key_arr[i_candidate];
		while (candidate_value < key_arr[i_compare] && i_compare >= 0)
		{
			key_arr[i_compare + 1] = key_arr[i_compare];
			i_compare--;
		}
		key_arr[i_compare + 1] = candidate_value;

		i_sorted++;
		i_candidate = i_sorted + 1;
		i_compare = i_sorted;
	}
	
}


void heap_sort_ki(int* key_arr, size_t length)
{
	if (length < 2)
		return;

	// first, build max heap
	heapify_ki(key_arr, first_parent(length), length);

	int heap_size = (int)length;
	// now recursively extract the root, swap back, reduce heap_size and downsift root

	while (heap_size > 1)
	{
		swap_values_ki(key_arr, key_arr+(heap_size-1));
		heap_size--;
		downsift_ki(key_arr, 0, heap_size);
	}

}



void adapt_sort_ki(int* key_arr, size_t length)
{
	if (length < 2)
		return;
	
	if (length < INSERTION_SWITCH)
	{
		insertion_sort_ki(key_arr, length);
		return;
	}

	// start with the iterative qsort approach
	int critical_stack_size = (int)length / STACK_BAILOUT_RATIO;

	int* stack = NULL;
	int top = -1;

	// Decide whether to allocate the stack on the heap or the stack
	if ((critical_stack_size + 4) <= STACK_ALLOC_THRESHOLD)
	{
		// Allocate the stack on the stack (hehe)
		int stack_local[STACK_ALLOC_THRESHOLD];
		stack = stack_local;
	}
	else
		stack = (int*)allocate_vector((critical_stack_size + 4), sizeof(int));

	// Push the initial range (entire array) onto the stack
	stack[++top] = 0;
	stack[++top] = (int)length - 1;

	// Process ranges until the stack is empty
	while (top >= 1) // should always be >= 1 because we always pop two values from the stack
	{
		// Pop a range from the stack
		int i_end = stack[top--];
		int i_start = stack[top--];

		// already sorted
		if (i_start >= i_end)
			continue;

		int current_partition_size = i_end - i_start + 1;

		if (current_partition_size <= INSERTION_SWITCH)
		{
			insertion_sort_ki(key_arr+i_start,current_partition_size);
			continue;
		}

		qsort_iterators result = qsort_core_ki(key_arr, i_start, i_end);

		// Push the two new ranges onto the stack
		// further optimization: push larger partition first
		int left_start = i_start;
		int left_end = result.lt - 1;
		int right_start = result.gt + 1;
		int right_end = i_end;

		size_t left_size = (left_start <= left_end) ? (size_t)left_end - left_start + 1 : 0;
		size_t right_size = (right_start <= right_end) ? (size_t)right_end - right_start + 1 : 0;

		if (left_size > right_size) {
			// Push larger (left) partition first
			if (left_size > 0) {
				stack[++top] = left_start;
				stack[++top] = left_end;
			}
			// Push smaller (right) partition second (to be processed next)
			if (right_size > 0) {
				stack[++top] = right_start;
				stack[++top] = right_end;
			}
		} else {
			// Push larger (right) partition first
			if (right_size > 0) {
				stack[++top] = right_start;
				stack[++top] = right_end;
			}
			// Push smaller (left) partition second
			if (left_size > 0) {
				stack[++top] = left_start;
				stack[++top] = left_end;
			}
		}

		if (top < 1)
			continue; // fast forward to loop termination

		int partition_length = stack[top] - stack[top-1] + 1;

		// after one iteration, check conditions for switching to other sorting algos
		if (partition_length <= INSERTION_SWITCH && partition_length > 1)
		{
			insertion_sort_ki(key_arr+stack[top-1], partition_length);
			stack[top] = 0;
			stack[top-1] = 0;
			top -= 2;

		}
		else if (top > critical_stack_size)
		{
			heap_sort_ki(key_arr+stack[top-1], partition_length);
			stack[top] = 0;
			stack[top-1] = 0;
			top -= 2;
		}
		
	}

	if ((critical_stack_size + 4) > STACK_ALLOC_THRESHOLD)
		free(stack);
	
}







/* CODE ARCHIVE

// broken version using Hoare partitioning
void recursive_qsort(float* array, int i_start, int i_end)
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
	recursive_qsort(array,	i_start,		i_from_left-1	);
	recursive_qsort(array,	i_from_left+1,	i_end			);

	// finally, return
	return;
	
}
*/