#include "logging.h"

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

void print_array_int(int* array, size_t length)
{
	for (size_t i = 0; i < length; i++)
		printf("%i ",array[i]);
	
	printf("\n");
	
	return;
}
