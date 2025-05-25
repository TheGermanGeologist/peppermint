#include "rng.h"

#include <limits.h> // For UINT32_MAX
#include <math.h>


// This was completely vibe coded
// I have no interest in learning random number generation atm
// so I see no reason to invest more time than I have to

// Internal function to get the next raw 32-bit random number from the Xorshift128 stream
static uint32_t xorshift128_next(RNG* generator)
{
	uint32_t t = generator->x ^ (generator->x << 11);
	generator->x = generator->y; generator->y = generator->z; generator->z = generator->w;
	generator->w = generator->w ^ (generator->w >> 19) ^ (t ^ (t >> 8));
	return generator->w;
}


void init_rng(RNG* generator, uint32_t seed)
{
	// Initialize state variables. This is a simple seeding method.
	// For critical applications requiring strong independence between streams
	// seeded with close values, a more robust seeding algorithm (e.g., using SplitMix64)
	// to generate the initial x,y,z,w would be better.
	generator->x = seed;
	generator->y = (seed ^ 0xDEADBEEF) * 0x41C64E6DU + 0x3039U; // Mix seed a bit
	generator->z = (generator->y ^ (seed >> 16)) * 0x41C64E6DU + 0x3039U;
	generator->w = (generator->z ^ (seed << 16)) * 0x41C64E6DU + 0x3039U;

	// It's good practice to run the generator a few times to "warm it up"
	// and further diffuse the initial seed across the state.
	for (int i = 0; i < 16; ++i)
		(void)xorshift128_next(generator);

}

int rng_int(RNG* generator, int range_min, int range_max)
{
	if (range_min > range_max) {
		return range_min; // Or handle error appropriately
	}
	if (range_min == range_max) {
		return range_min;
	}

	// Calculate the number of possible integer values in the range.
	unsigned int num_outcomes = (unsigned int)(range_max - range_min) + 1;

	uint32_t random_val = xorshift128_next(generator);

	// Debiasing method (based on Lemire's "Fast Random Integer Generation in an Interval")
	// to ensure uniform distribution when mapping a random uint32_t to a smaller range.
	// Calculate the largest multiple of num_outcomes that is <= UINT32_MAX.
	// (UINT32_MAX / num_outcomes) gives how many full sets of 'num_outcomes' fit in UINT32_MAX.
	uint32_t max_val_for_uniform_bins = num_outcomes * (UINT32_MAX / num_outcomes);

	// If random_val falls into the incomplete top range, regenerate.
	// This loop will execute very rarely on average.
	while (random_val >= max_val_for_uniform_bins)
	{
		random_val = xorshift128_next(generator);
	}

	return range_min + (int)(random_val % num_outcomes);
}


float rng_float(RNG* generator, float range_min, float range_max)
{
	if (range_min >= range_max) {
        return range_min; // Or handle error appropriately
    }

    uint32_t random_u32 = xorshift128_next(generator);

    // Convert to [0, 1) float.
    // (float)random_u32 / (UINT32_MAX + 1.0f)
    // Using (uint64_t) to ensure the +1 doesn't overflow before conversion to float for the divisor.
    float scale = 1.0f / ((float)((uint64_t)UINT32_MAX + 1));
    float random_0_to_1_exclusive = (float)random_u32 * scale;

    return range_min + random_0_to_1_exclusive * (range_max - range_min);
}


// Vibe coding END




float rng_normal_dist(RNGNORM* generator)
{
    if (generator->has_spare)
	{
        generator->has_spare = false;
        return generator->spare;
    }

    float u, v, s;
	u = v = s = 0.0;
	while (s >= 1.0 || s == 0.0)
	{
        u = rng_float((RNG*)generator, -1.0f, 1.0f);
        v = rng_float((RNG*)generator, -1.0f, 1.0f);
        s = u * u + v * v;
    }

    float const_factor = sqrtf(-2.0f * logf(s) / s);
    generator->spare = generator->mu + generator->sigma * v * const_factor;
    generator->has_spare = true;
    return generator->mu + generator->sigma * u * const_factor;
}


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
