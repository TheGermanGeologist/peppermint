#pragma once

#include <stdlib.h>
#include "utils.h"

// for now: ONLY FLOATS, ONLY vec[3] !


void zero_vector(float out[3])
{
	for (size_t i = 0; i < 3; i++)
		out[i] = .0f;
}


void init_vector(float out[3], const float value)
{
	for (size_t i = 0; i < 3; i++)
		out[i] = value;
}


void add_scalar(float out[3], const float value)
{
	for (size_t i = 0; i < 3; i++)
		out[i] += value;
}


void add_vectors(float out[3], const float vec1[3], const float vec2[3])
{
	for (size_t i = 0; i < 3; i++)
		out[i] = vec1[i] + vec2[i];
}
