# Peppermint

## Goal of the project

Given a point cloud representing fragments:
- identify contiguous regions of points which belong to the same fragment based on neighborhood criteria
- extract surfaces from each fragment
- mesh these surfaces with a suitable triangulation method
- have a basic mock simulation of fragment travel and break up
- implement an alogrithm which efficiently updates the:
    - fragment list (particle / fragment membership)
	- surface mesh (node positions)
	- surface topology

I use this project to teach myself C and a bunch of data structures and algorithms, but I'm (still) optimistic that the end result will implement the goals above well enough for production code.

I called it peppermint because of the large quantity of peppermint gum consumed while working on this project.

## Features
- Not many, so far

## TO DO
- finish implementing basic helper function for sorting, vector math, memory management
- decide on a data structure for the particles
    - probably struct of long vectors instead of vector of structs for sorting
	- consider potential addition of bonds in this decision
- add shape generation which fills various geometric shapes with particles for testing purposes later on
- implement various data structures and algorithms for efficient neighborhood search etc
    - k d tree
	- i j k search grid
	- marching cubes
	- octree
	- flood fill
	- other voxel based methods
- output writer and python script for results visualization
- identification of contiguous fragments in particle cloud
- vtk output writer for results visualization
- implement marching cubes for surface construction on fragments
- use octree chunk elimination and flood fill to discard inner surfaces
- implement poisson disk sampling and GreedyProjectionTriangulation for surface (re)meshing
- worry about my sanity, probably
- add mock particle simulation
    - something like two bananas crashing into each other and "fragmenting" should provide sufficient complexity for testing
- write algorithm for adaptive
    - fragment updates
	- surface mesh modification
	- surface mesh reconstruction
- add OMP and SIMD parallelization
- potentially look into CUDA as well
- explore PCL and see how it compares

## License
All rights reserved.