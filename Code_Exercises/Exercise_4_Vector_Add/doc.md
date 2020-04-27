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
dpcpp -o sycl-ex-4 -I../External/catch2/ ../Code_Exercises/Exercise_4_Vector_Add/source.cpp
./sycl-ex-4
```

For ComputeCpp:
```
cmake -DSYCL_ACADEMY_USE_COMPUTECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/computecpp ..
make Exercise_4_source
./Code_Exercises/EExercise_4_Vector_Add/Exercise_4_source
```

For hipSYCL:
```
cmake -SYCL_ACADEMY_USE_HIPSYCL=ON ..
make Exercise_4_source
./Code_Exercises/Exercise_4_Vector_Add/Exercise_4_source