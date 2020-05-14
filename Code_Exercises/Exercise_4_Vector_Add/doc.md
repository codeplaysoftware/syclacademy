# SYCL Academy

### Exercise 4: Vector add

---

In this first exercise you will learn:
* How to manage data using buffers.
* How to access data using accessors.
* How to define an nd range SYCL kernel function.

---

In SYCL buffers are used to manage data across the host and device(s), and
accessors are used to declare data dependencies to a SYCL kernel function as
well as to access the data within a SYCL kernel function.

1.) Allocate your input and output vectors

Allocate memory on the host for your input and output data using `std::vector`s
and initialize the input with values.

2.) Construct buffers

Construct a buffer to manage your input and output data. The template parameters
for the the `buffer` class are the type and then the dimensionality. The
parameters to construct a buffer are a pointer to the host data and a `range`.

Remember the dimensionality of the `range` must match the dimensionality of the
`buffer`.

3.) Construct accessors

Construct an accessor for your input and output buffers. The template parameter
to `get_access` is the access mode that specifies how you wish to use the data
managed by the buffer.

Remember to pass the `handler` to `get_access`, if you don't this will construct
a host accessor, which behaves differently to a regular accessor.

4.) Declare your kernel

Declare a SYCL kernel function using the `parallel_for` command with a range
matching the size of the `std::vector`s. The kernel function should use the
`operator[]` of the `accessor` objects to read from the inputs and write the sum
to the output.

Remember the `accessor`'s `operator[]` can take either a `size_t` (when the
dimensionality is 1) and an `id`.

5.) Try a temporary buffer

You can construct a temporary `buffer` that doesn't copy back on destruction by
initializing it with just a `range` and no host pointer.

#### Build And Execution Hints

For For DPC++ (using the Intel DevCloud):
```
dpcpp -o sycl-ex-4 -I../External/Catch2/single_include ../Code_Exercises/Exercise_4_Vector_Add/source.cpp
./sycl-ex-4
```
Then follow the instructions in the [main README][devcloud-execution] to submit your job to the queue.

For ComputeCpp:
```
cmake -DSYCL_ACADEMY_USE_COMPUTECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/computecpp ..
make Exercise_4_source
./Code_Exercises/Exercise_4_Vector_Add/Exercise_4_source
```

For hipSYCL:
```
# Add -DHIPSYCL_GPU_ARCH=<arch> to the cmake arguments when compiling for GPUs.
# <arch> is e.g. sm_60 for NVIDIA Pascal GPUs, gfx900 for AMD Vega 56/64, and gfx906 for Radeon VII.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_PLATFORM=<cpu|cuda|rocm> ..
make Exercise_4_source
./Code_Exercises/Exercise_4_Vector_Add/Exercise_4_source
<<<<<<< HEAD

[devcloud-execution]: https://github.com/codeplaysoftware/syclacademy#compiling-directly-dpc-only
=======
```
alternatively, without cmake:
```
cd Code_Exercises/Exercise_4_Vector_Add
HIPSYCL_PLATFORM=<cpu|cuda|rocm> HIPSYCL_GPU_ARCH=<arch-when-compiling-for-gpu> /path/to/hipsycl/bin/syclcc -o sycl-ex-4 -I../../External/Catch2/single_include source.cpp
./sycl-ex-4
```
>>>>>>> master
