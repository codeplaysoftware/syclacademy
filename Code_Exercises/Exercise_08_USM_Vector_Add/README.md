# SYCL Academy

## Exercise 8: USM Vector Add
---

In this exercise you will learn how to use the USM API to write a SYCL
application which performs a vector add.

---

### 1.) Allocate data on the host

Allocate memory on the host for the input and out data just as you did when
using the buffer/accessor model.

### 2.) Create a queue

Create a `queue` using the USM device selector from exercise 7, remember to
handle errors.

### 3.) Allocate device memory

When using the USM model the first thing you need to do is allocate the USM
device memory.

To do this call `malloc_device` to allocate memory for the two inputs and the
output.

ComputeCpp - wrappers

### 4.) Copy to the device

Before you can perform any computation on the data you must copy it to the
device.

To do this call the `queue` member function `memcpy` for each of the two inputs,
remember to call `wait` on the `event` that is returned.

### 5.) Define the kernel function

Now you can define the kernel function itself, which is largely the same as in
exercise 7.

This can be done differently from the buffer/accessor model, by calling the
shortcut member function `single_task` on the `queue` rather than creating a
command group.

Note that as you are accessing a pointer rather than an `accessor` you must
retrieve an integral index, which can be done by calling the subscript operator
on the `id` passed into the kernel function, with index 0.

Remember to name your kernel function, and to call `wait` on the `event` that is
returned.

### 6.) Copy back the result

Once the kernel function has completed you can copy the result back to the host.

As you did when copying to the device, you can do this by calling the `queue`
member function `memcpy`, again remember to call `wait` on the `event` that is
returned.

### 7.) Free the device memory

Finally once you have copied the data back from the device you can free that
memory.

To do this call `free` on each of the USM device allocations, note this is the
SYCL API `free` and not the standard C `free`.

#### Build And Execution Hints

For For DPC++ (using the Intel DevCloud):
```sh
clang++ -fsycl -o sycl-ex-8 -I../External/Catch2/single_include ../Code_Exercises/Exercise_08_USM_Vector_Add/source.cpp
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
make exercise_08_usm_vector_add_source
./Code_Exercises/Exercise_08_USM_Vector_Add/exercise_08_usm_vector_add_source
```


For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_08_usm_vector_add_source
./Code_Exercises/Exercise_08_USM_Vector_Add/exercise_08_usm_vector_add_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_08_USM_Vector_Add
/path/to/hipsycl/bin/syclcc -o sycl-ex-8 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-8
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
