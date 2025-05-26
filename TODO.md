# TODOs

- [x] create a function which takes in an indices array and an array to be sorted and returns the array mapped to the indices

- [x] implement normal distribution rng (Box Muller transform)

- [ ] Particle cloud shape creation I
    - [ ]  define struct to hold geometric information for
        - [ ] sphere
        - [ ] brick
        - [ ] tetrahedron
        - [ ] toroid
        - [ ] banana
    - [ ]  implement naive shape filling
        - [ ] spawn particles in min max range of shape
        - [ ] discard if outside
- [ ] build vtk / paraview output writer for particles
- [ ] Particle cloud shape creation II
    - [ ] function shape_generator
        - [ ] takes in array of shapes + settings for shape filling
        - [ ] initializes particle SoA
- [ ] Write uniform / i j k grid data structure template
- [ ] Poisson Disk Sampling
    - [ ] implement generic PSD for 3D
    - [ ] apply to filling shapes with particles
- [ ] Morton codes
    - [ ] implement calculation algorithm
    - [ ] sort particle SoA based on Morton codes
- [ ] Implement data structures
    - [ ] Voxel grid
    - [ ] Octree
    - [ ] k d tree
- [ ] Implement fragment identification / coloring
- [ ] Implement marching cubes for fragments
