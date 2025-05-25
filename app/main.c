/*
	    ____                                       _       __ 
	   / __ \___  ____  ____  ___  _________ ___  (_)___  / /_
	  / /_/ / _ \/ __ \/ __ \/ _ \/ ___/ __ `__ \/ / __ \/ __/
	 / ____/  __/ /_/ / /_/ /  __/ /  / / / / / / / / / / /_  
	/_/    \___/ .___/ .___/\___/_/  /_/ /_/ /_/_/_/ /_/\__/  
	          /_/   /_/                                       
*/


#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "time.h"
#include <windows.h> // for timings

#include "particle.h"
#include "utils.h"
#include "algorithms/sorting.h"
#include "logging.h"
#include "rng.h"



int main()
{
	RNG rng1;
	init_rng(&rng1,(int)time(NULL));

	RNGNORM rng2;
	init_rngnorm(&rng2,(int)time(NULL),0,250);

	int* random_ints = (int*)allocate_vector(100000,sizeof(int));
	float* norm_dist = (float*)allocate_vector(100000,sizeof(float));
	for (size_t i = 0; i < 100000; i++)
	{
		norm_dist[i] = rng_normal_dist(&rng2);
		random_ints[i] = rng_int(&rng1,-500,500);
	}
	

	int bins[11];
	for (size_t i = 0; i < 11; i++)
	{
		bins[i] = 0;
	}

	for (size_t i = 0; i < 100000; i++)
	{
		float shifted_value = norm_dist[i] + 500.0f;
		int bin_index = (int)(shifted_value * 11.0 / 1001.0);
		// if (bin_index < 0) bin_index = 0;
        // if (bin_index > 10) bin_index = 10;
		if (bin_index > 10 || bin_index < 0)
			continue;
		bins[bin_index] += 1;
	}
	
	int max = -10000000;
	for (size_t i = 0; i < 11; i++)
	{
		if (bins[i] > max)
			max = bins[i];
	}

	// bin length: 30
	for (size_t i = 0; i < 11; i++)
	{
		bins[i] = bins[i] * 30 / max;
	}

	for (size_t i = 0; i < 11; i++)
	{
		if(-5+(int)i >= 0)
			printf(" ");
		printf("%zi: ",-5+i);
		for (size_t j = 0; j < bins[i]; j++)
		{
			printf("#");
		}
		printf("\n");
	}
	

	return 0;
}



// LARGE_INTEGER freq, t_start, t_end;
    // QueryPerformanceFrequency(&freq);

	// int Ni = 1000;
	// int array_size_i = 10000;

	// for (int kk = 0; kk < Ni; kk++)
	// {
	// 	double elapsed_time = 0.0;
	// 	int* large_array = allocate_vector(array_size_i, sizeof(int));
	// 	for (size_t i = 0; i < array_size_i; i++)
	// 	{
	// 		large_array[i] = get_rand_int(-1000, 1000);
	// 	}
	// 	QueryPerformanceCounter(&t_start);
	// 	adapt_sort_ki(large_array,array_size_i);
	// 	QueryPerformanceCounter(&t_end);

	// 	elapsed_time = (double)(t_end.QuadPart - t_start.QuadPart) / freq.QuadPart *1e6;
	// 	printf("Sorted using adapt_sort_ki in %.6f us\n", elapsed_time);
	// 	check_sorting_int(large_array, array_size_i);


	// 	free(large_array);
	// }
	


	// double qsort_time, insersort_time, heapsort_time, recursivesort_time, iterativesort_time, adaptsort_time;
	// qsort_time = insersort_time = heapsort_time = recursivesort_time = iterativesort_time = adaptsort_time = 0.0;
	
	// int N = 1000;
	// int array_size = 10000;
	// for (int kk= 0; kk < N; kk++)
	// {
	// 	float* large_array = allocate_vector(array_size, sizeof(float));
	// 	float* large_array2 = allocate_vector(array_size, sizeof(float));
	// 	float* large_array3 = allocate_vector(array_size, sizeof(float));
	// 	float* large_array4 = allocate_vector(array_size, sizeof(float));
	// 	float* large_array5 = allocate_vector(array_size, sizeof(float));
	// 	float* large_array6 = allocate_vector(array_size, sizeof(float));
	// 	float* large_array_static = allocate_vector(array_size, sizeof(float));

	// 	for (size_t i = 0; i < array_size; i++)
	// 	{
	// 		large_array[i] = get_rand_float(-100.0, 100.0);
	// 	}
	// 	memcpy(large_array2, large_array, array_size * sizeof(float));
	// 	memcpy(large_array3, large_array, array_size * sizeof(float));
	// 	memcpy(large_array4, large_array, array_size * sizeof(float));
	// 	memcpy(large_array5, large_array, array_size * sizeof(float));
	// 	memcpy(large_array6, large_array, array_size * sizeof(float));
	// 	memcpy(large_array_static, large_array, array_size * sizeof(float));
	// 	check_array_identity(large_array, large_array2, array_size);

		

	// 	double elapsed_time;

	// 	QueryPerformanceCounter(&t_start);
	// 	qsort(large_array, array_size, sizeof(float), cmpfunc);
	// 	QueryPerformanceCounter(&t_end);

	// 	elapsed_time = (double)(t_end.QuadPart - t_start.QuadPart) / freq.QuadPart *1e6;
	// 	qsort_time += elapsed_time;
	// 	printf("Sorted using std qsort in %.6f us\n", elapsed_time);
	// 	//printf("Sorted using std qsort in: %f ms\n", elapsed_time);

	// 	if (check_sorting(large_array, array_size))
	// 	{
	// 		printf("Error: std qsort not sorted\n");
	// 		printf("This was the input array:\n");
	// 		print_array(large_array_static, array_size);
	// 		break;
	// 	}


	// 	QueryPerformanceCounter(&t_start);
	// 	heap_sort(large_array3, array_size);
	// 	QueryPerformanceCounter(&t_end);
	// 	elapsed_time = (double)(t_end.QuadPart - t_start.QuadPart) / freq.QuadPart *1e6;
	// 	heapsort_time += elapsed_time;
	// 	printf("Sorted using heap_sort in %.6f us\n", elapsed_time);
	// 	//printf("Sorted using heap_sort in: %f ms\n", elapsed_time);

	// 	check_sorting(large_array3, array_size);

	// 	QueryPerformanceCounter(&t_start);
	// 	insertion_sort(large_array4, array_size);
	// 	QueryPerformanceCounter(&t_end);
	// 	elapsed_time = (double)(t_end.QuadPart - t_start.QuadPart) / freq.QuadPart *1e6;
	// 	insersort_time += elapsed_time;
	// 	printf("Sorted using insertion_sort in %.6f us\n", elapsed_time);
	// 	//printf("Sorted using insertion_sort in: %f ms\n", elapsed_time);

	// 	check_sorting(large_array4, array_size);

	// 	QueryPerformanceCounter(&t_start);
	// 	recursive_qsort(large_array6, 0, array_size - 1);
	// 	QueryPerformanceCounter(&t_end);
	// 	elapsed_time = (double)(t_end.QuadPart - t_start.QuadPart) / freq.QuadPart *1e6;
	// 	recursivesort_time += elapsed_time;
	// 	printf("Sorted using recursive_qsort in %.6f us\n", elapsed_time);
	// 	//printf("Sorted using recursive_qsort in: %f ms\n", elapsed_time);

	// 	if (check_sorting(large_array6, array_size))
	// 	{
	// 		printf("Error: recursive_qsort not sorted\n");
	// 		printf("This was the input array:\n");
	// 		print_array(large_array_static, array_size);
	// 		printf("This is the array sorted by qsort:\n");
	// 		print_array(large_array, array_size);
	// 		printf("This is the array sorted by recursive_qsort:\n");
	// 		print_array(large_array6, array_size);
	// 		break;
	// 	}

	// 	QueryPerformanceCounter(&t_start);
	// 	iterative_qsort(large_array2, array_size);
	// 	QueryPerformanceCounter(&t_end);
	// 	elapsed_time = (double)(t_end.QuadPart - t_start.QuadPart) / freq.QuadPart *1e6;
	// 	iterativesort_time += elapsed_time;
	// 	printf("Sorted using iterative_qsort in %.6f us\n", elapsed_time);
	// 	//printf("Sorted using recursive_qsort in: %f ms\n", elapsed_time);

	// 	if (check_sorting(large_array2, array_size))
	// 	{
	// 		printf("Error: iterative_qsort not sorted\n");
	// 		printf("This was the input array:\n");
	// 		print_array(large_array_static, array_size);
	// 		printf("This is the array sorted by qsort:\n");
	// 		print_array(large_array, array_size);
	// 		printf("This is the array sorted by iterative_qsort:\n");
	// 		print_array(large_array2, array_size);
	// 		break;
	// 	}

	// 	QueryPerformanceCounter(&t_start);
	// 	adapt_sort(large_array2, array_size);
	// 	QueryPerformanceCounter(&t_end);
	// 	elapsed_time = (double)(t_end.QuadPart - t_start.QuadPart) / freq.QuadPart *1e6;
	// 	adaptsort_time += elapsed_time;
	// 	printf("Sorted using adapt_sort in %.6f us\n", elapsed_time);
	// 	//printf("Sorted using recursive_qsort in: %f ms\n", elapsed_time);

	// 	if (check_sorting(large_array2, array_size))
	// 	{
	// 		printf("Error: adapt_sort not sorted\n");
	// 		printf("This was the input array:\n");
	// 		print_array(large_array_static, array_size);
	// 		printf("This is the array sorted by qsort:\n");
	// 		print_array(large_array, array_size);
	// 		printf("This is the array sorted by adapt_sort:\n");
	// 		print_array(large_array2, array_size);
	// 		break;
	// 	}

	// 	free(large_array);
	// 	free(large_array2);
	// 	free(large_array3);
	// 	free(large_array4);
	// 	free(large_array5);
	// 	free(large_array6);
	// 	free(large_array_static);

	// }

	// printf("\n\nAverage sorting times for l = %i, N = %i:\n",array_size,N);
	// printf("\t Std qsort:\t\t %.3f us\n", qsort_time/N);
	// printf("\t Insertion sort:\t %.3f us\n", insersort_time/N);
	// printf("\t Heap sort:\t\t %.3f us\n", heapsort_time/N);
	// printf("\t Recursive qsort:\t %.3f us\n", recursivesort_time/N);
	// printf("\t Iterative qsort:\t %.3f us\n", iterativesort_time/N);
	// printf("\t Adaptive sort:\t\t %.3f us\n", adaptsort_time/N);

// OLD TESTS
/*
	init_rng((int)time(NULL));
	
	// check particle structs
	printf("Size of Continuum Particle: %zi\n",sizeof(ContinuumParticleDummy));
	printf("Size of Discrete Particle: %zi\n",sizeof(DiscreteParticleDummy));


	// test array on the stack

	float test_array[15] = {0.7f, -0.2f, 1.3f, 1.5f, 0.33f, 0.75f, 0.33f, -2.0f, 0.25f, 0.5f, 0.9f, 1.2f, 3.0f, 0.0f, 0.66f};
	int   test_array_int[15] = {2, -15, 2, 2, 9, 0, -1, 10, 1000, -4, 3, 8, 7, 12, 21};
	//int   test_array_int_orig[15] = {2, -15, 2, 2, 9, 0, -1, 10, 1000, -4, 3, 8, 7, 12, 21};
	int* indices = new_index_array(15);
	
	
	print_array_int(test_array_int,15);
	adapt_sort_ki(test_array_int,indices,15);

	bool* bookkeeper = (bool*)allocate_vector(15,sizeof(bool));
	map_farray_to_indices(test_array, indices, bookkeeper, 15);

	//recursive_qsort(test_array,0,14);
	printf("done sorting\n");
	//print_array(test_array,15);
	print_array_int(test_array_int,15);
	print_array_int(indices,15);
	print_array(test_array,15);




	Particle p = {1.0, 2.0, 3.0, 0.1};
	printf("Particle position: (%f, %f, %f)\n", p.x, p.y, p.z);
	printf("Particle radius: %f\n", p.radius);


	// test array alloaction for particles

	clock_t t_start, t_end;
	double elapsed_time;

	int rows = 1200;
	int columns = 700;

	t_start = clock();

	Particle** particle_array = (Particle**)allocate_2D_array(rows, columns, sizeof(Particle));

	t_end = clock();
	elapsed_time = (double)t_end - (double)t_start;
	elapsed_time /= CLOCKS_PER_SEC;

	printf("Time to allocate memory for n=%i particles: %f\n",rows*columns,elapsed_time);

	t_start = clock();
	for (int ii = 0; ii < rows; ii++)
	{
		for (int jj = 0; jj < columns; jj++)
		{
			particle_array[ii][jj] = (Particle){1.0, 2.0, 3.0, 0.1};
		}
		
	}
	t_end = clock();
	elapsed_time = (double)t_end - (double)t_start;
	elapsed_time /= CLOCKS_PER_SEC;

	printf("Time to fill array with n=%i particles: %f\n",rows*columns,elapsed_time);

	printf("%f",particle_array[5][3].radius);
	free_2D_array((void**)particle_array,rows);

	// test rng
	for (size_t i = 0; i < 3000; i++)
	{
		int val = get_rand_int(-5, 5);
		if (val == 5)
			printf("%i ",val);
	}
	printf("\n\n");
	for (size_t i = 0; i < 100; i++)
	{
		printf("%f ",get_rand_float(0.0, 3.0));
	}
	printf("\n\n");


	int bins[11];
	for (size_t i = 0; i < 11; i++)
	{
		bins[i] = 0;
	}

	for (size_t i = 0; i < 100000; i++)
	{
		bins[5+get_rand_int_mod(-5,5)] += 1;
	}
	
	int max = -10000000;
	for (size_t i = 0; i < 11; i++)
	{
		if (bins[i] > max)
			max = bins[i];
	}

	// bin length: 30
	for (size_t i = 0; i < 11; i++)
	{
		bins[i] = bins[i] * 30 / max;
	}

	for (size_t i = 0; i < 11; i++)
	{
		if(-5+(int)i >= 0)
			printf(" ");
		printf("%zi: ",-5+i);
		for (size_t j = 0; j < bins[i]; j++)
		{
			printf("#");
		}
		printf("\n");
	}
	


	//float* test_array = (float*)allocate_vector(15,sizeof(float));

*/