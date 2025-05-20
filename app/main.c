#include <stdio.h>
#include "particle.h"
#include "utils.h"
#include "algorithms/sorting.h"

#include "time.h"

int main()
{
	init_rng(time(NULL));
	
	// check particle structs
	printf("Size of Continuum Particle: %zi\n",sizeof(ContinuumParticleDummy));
	printf("Size of Discrete Particle: %zi\n",sizeof(DiscreteParticleDummy));


	// test array on the stack

	float test_array[15] = {0.7f, -0.2f, 1.3f, 1.5f, 0.33f, 0.75f, 0.33f, -2.0f, 0.25f, 0.5f, 0.9f, 1.2f, 3.0f, 0.0f, 0.66f};

	//recursive_qsort(test_array,0,14);
	//insertion_sort(test_array,15);
	//iterative_qsort(test_array,15);

	heapsort(test_array,15);

	printf("done sorting\n");

	//print_array_range(test_array,0,14);
	print_array(test_array,15);

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


	return 0;
}


// OLD TESTS
/*
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

*/