# SYCL Academy

## Exercise 3: Scalar Add

---

In this exercise you will learn how to create `buffer`s to manage data and
`accessor`s to access teh data within a kernel function.

---

### 1.) Allocate your input and output vectors

Allocate memory on the host for your input and output data using `std::vector`s
and initialize the input with values.

### 2.) Construct buffers

In SYCL buffers are used to manage data across the host and device(s).

Construct a buffer to manage your input and output data. The template parameters
for the the `buffer` class are the type and then the dimensionality. The
parameters to construct a buffer are a pointer to the host data and a `range`.

Remember the dimensionality of the `range` must match the dimensionality of the
`buffer`.

### 3.) Construct accessors

In SYCL accessors are used to declare data dependencies to a SYCL kernel
function as well as to access the data within a SYCL kernel function.

Construct an accessor for your input and output buffers. The template parameter
to `get_access` is the access mode that specifies how you wish to use the data
managed by the buffer.

Remember to pass the `handler` to `get_access`, if you don't this will construct
a host accessor, which behaves differently to a regular accessor.

### 4.) Declare your kernel

Declare a SYCL kernel function using the `single_task` command with a range
matching the size of the `std::vector`s. The kernel function should use the
`operator[]` of the `accessor` objects to read from the inputs and write the sum
to the output.

Remember the `accessor`'s `operator[]` can take either a `size_t` (when the
dimensionality is 1) and an `id`.

### 5.) Try a temporary buffer

You can construct a temporary `buffer` that doesn't copy back on destruction by
initializing it with just a `range` and no host pointer.

#### Build And Execution Hints

For For DPC++ (using the Intel DevCloud):
```sh
dpcpp -o sycl-ex-3 -I../External/Catch2/single_include ../Code_Exercises/Exercise_03_Scalar_Add/source.cpp
./sycl-ex-3
```
In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only abvailable through the job queue.
Please refer to the [guide][devcloud-job-submission].

So wrap the binary into a script `job_submission` and run:
```sh
qsub job_submission
```

For ComputeCpp:
```sh
cmake -DSYCL_ACADEMY_USE_COMPUTECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/computecpp ..
make exercise_03_scalar_add_source
./Code_Exercises/Exercise_03_Scalar_Add/exercise_03_scalar_add_source
```


For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_03_scalar_add_source
./Code_Exercises/Exercise_03_Scalar_Add/exercise_03_scalar_add_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_03_Scalar_Add
/path/to/hipsycl/bin/syclcc -o sycl-ex-3 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-3
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
