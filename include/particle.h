#pragma once

#include <stdbool.h>

#define MAX_NR_NEIGHBORS	200
#define MAX_NR_BONDS 		 16

typedef struct
{
	int 	n;
	int* 	id;				// [n]
	int*	part;			// [n]

	float*	mass;			// [n]

	float** coordinates;	// [3][n]
	float** velocity;		// [3][n]
	float** force;			// [3][n]

	int*	nr_neighbors;	// [n]
	int**	neighbor_ids;	// [n][MAX_NR_NEIGHBORS]

	float* radius;			// [n]

} ContinuumParticleStruct;


typedef struct
{
	int 	n;
	int* 	id;				// [n]
	int*	part;			// [n]

	float*	mass;			// [n]

	float** coordinates;	// [3][n]
	float** velocity;		// [3][n]
	float** force;			// [3][n]

	int*	nr_bonds;		// [n]
	int**	bonded_ids;		// [n][MAX_NR_BONDS]
	float** rel_bond_lenght;// [n][MAX_NR_BONDS]
	bool**	bond_intact;	// [n][MAX_NR_BONDS]


} DiscreteParticleStruct;



// dummy structs to check memory / particle


typedef struct
{
	int 	id;
	int		part;

	float	mass;

	float 	coordinates[3];
	float 	velocity[3];
	float 	force[3];

	int		nr_neighbors[MAX_NR_NEIGHBORS];
	int		neighbor_ids[MAX_NR_NEIGHBORS];

	float 	radius;

} ContinuumParticleDummy;

typedef struct
{
	int 	id;
	int		part;

	float	mass;

	float 	coordinates[3];
	float 	velocity[3];
	float 	force[3];

	int		nr_bonds;
	int		bonded_ids[MAX_NR_BONDS];
	float 	rel_bond_lenght[MAX_NR_BONDS];
	bool	bond_intact[MAX_NR_BONDS];


} DiscreteParticleDummy;