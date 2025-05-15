#pragma once

#include <stdlib.h>


void* allocate_vector(int length, size_t element_size);

void free_vector(void* vector);

void** allocate_2D_array(int rows, int cols, size_t element_size);

void free_2D_array(void** array, int rows);