#include "rng.h"

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
