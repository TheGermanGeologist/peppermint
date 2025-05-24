#pragma once

#include <stdlib.h>

inline void init_rng(unsigned int seed) { srand(seed); }

int get_rand_int(int range_min, int range_max);
int get_rand_int_mod(int range_min, int range_max);
float get_rand_float(float range_min, float range_max);