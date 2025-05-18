#include "data_structures/heap.h"
#include "utils.h"

#include <stdio.h>

/**
 * @brief heapifies an array of size n starting at node i
 * 
 * To build a max heap from scratch call
 * heapify(arr, first_parent(n), n)
 *
 * @param array pointer to an array that gets heapified
 * @param i node index at which to start heapifying
 * @param n size of the array
 */
void heapify(float* array, size_t i, size_t n)
{
	// start at i, iterate backwards to 0, and call downsift on each node
	for (int node = (int)i; node >= 0; node--)
		downsift(array, node, n);

	// to heapify the entire array, pass first_parent(n) as i

}


void downsift(float* array, size_t i, size_t n)
{
	while (1)
	{
		size_t biggest = i;

		if (left_node(i) < n)
			if (array[i] < array[left_node(i)])
				biggest = left_node(i);

		if (right_node(i) < n)
			if (array[right_node(i)] > array[biggest])
				biggest = right_node(i);
		
		if (biggest != i)
		{
			swap_values(array+i, array+biggest);
			i = biggest;
		}
		else
			break;

	}
}


// not needed for max-heap
void upsift(float* array, size_t i, size_t n)
{
	fprintf(stderr,"WARNING: upsift not implemented.\n");
};