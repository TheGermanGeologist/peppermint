#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// pseudo random number generator with independent streams
typedef struct
{
	uint32_t x, y, z, w;
} RNG;

typedef struct
{
	uint32_t x, y, z, w;
	float mu, sigma;
	float spare;
	bool has_spare;
} RNGNORM;

void init_rng(RNG* generator, uint32_t seed);

inline void init_rngnorm(RNGNORM* generator, uint32_t seed, float mu, float sigma)
{
	init_rng((RNG*)generator,seed);
	generator->has_spare = false;
	generator->mu = mu;
	generator->sigma = sigma;
}

int rng_int(RNG* generator, int range_min, int range_max);
float rng_float(RNG* generator, float range_min, float range_max);

float rng_normal_dist(RNGNORM* generator);


// basic rng using srand and rand()
inline void init_rng_old(unsigned int seed) { srand(seed); }

int get_rand_int(int range_min, int range_max);
int get_rand_int_mod(int range_min, int range_max);
float get_rand_float(float range_min, float range_max);