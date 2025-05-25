#pragma once

#include <stdlib.h>
#include <stdint.h>

// pseudo random number generator with independent streams
typedef struct
{
	uint32_t x, y, z, w;
} RNG;

void init_rng(RNG* generator, uint32_t seed);

int rng_int(RNG* generator, int range_min, int range_max);
float rng_float(RNG* generator, float range_min, float range_max);


// basic rng using srand and rand()
inline void init_rng_old(unsigned int seed) { srand(seed); }

int get_rand_int(int range_min, int range_max);
int get_rand_int_mod(int range_min, int range_max);
float get_rand_float(float range_min, float range_max);