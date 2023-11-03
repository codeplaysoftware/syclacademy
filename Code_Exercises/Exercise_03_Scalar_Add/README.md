# SYCL Academy

## Exercise 3: Scalar Add

---

In this exercise you will learn how to create `buffer`s to manage data and
`accessor`s to access the data within a kernel function.

---

### 1.) Allocate your input and output

Allocate memory on the host for your input and output data variables and assign
values to the inputs.

### 2.) Construct buffers

In SYCL buffers are used to manage data across the host and device(s).

Construct a buffer to manage your input and output data. The parameters to
construct a buffer are a pointer to the host data and a `1` dimensional `range`
of `1` to represent a single value. The element type and dimensionality can be
inferred from the pointer and the `range`.

### 3.) Construct accessors

In SYCL accessors are used to declare data dependencies to a SYCL kernel
function as well as to access the data within a SYCL kernel function.

Construct an accessor for each of the buffers to access the data of each within
the kernel function. The parameters to construct an `accessor` are the `buffer`
and the `handler`.

### 4.) Declare your kernel

Declare a SYCL kernel function using the `single_task` command provide a lambda
as the kernel function. The kernel function should use the `operator[]` of the
`accessor` objects to read from the inputs and write the sum to the output. As
each `accessor` is only accessing a single element you can simply specify `0`.

### 5.) Try a temporary buffer

You can construct a temporary `buffer` that doesn't copy back on destruction by
initializing it with just a `range` and no host pointer.

#### Build And Execution Hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make exercise_3
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-3 -I../External/Catch2/single_include ../Code_Exercises/Exercise_03_Scalar_Add/source.cpp
./sycl-ex-3
```
In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only available through the job queue.
Please refer to the [guide][devcloud-job-submission].

So wrap the binary into a script `job_submission` and run:
```sh
qsub job_submission
```

For AdaptiveCpp:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_ADAPTIVECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/adapivecpp -DADAPTIVECPP_TARGETS="<target specification>" ..
make exercise_3
```
alternatively, without CMake:
```sh
cd Code_Exercises/Exercise_03_Scalar_Add
/path/to/AdaptiveCpp/bin/syclcc -o sycl-ex-3 -I../../External/Catch2/single_include --adaptivecpp-targets="<target specification>" source.cpp
./sycl-ex-3
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
