# SYCL Academy

## Exercise 10: Managing Dependencies
---

In this exercise you will learn how to create a data dependency data flow graph
in both the buffer/accessor and USM models.

---

### 1.) Define a data flow graph with the buffer/accessor model

Using everything you have learned in previous exercises create an application
using the buffer/accessor model which has four kernel functions. These kernel
functions can do any computation you like, but they should follow the following
dependencies.

          (kernel A)
         /          \
    (kernel B)  (kernel C)
         \          /
          (kernel D)

The important thing here is that kernels B and C must depend on kernel A, kernel
D must depend on kernels B and C and kernels B and C can be executed in any
order and even concurrently if the device permits. Note that in the
buffer/accessor these dependencies are created implicitly using the creation of
`accessor`s.

Feel free to use any method of synchronization and copy back you like, but
remember to handle errors.

### 2.) Define a data flow graph with the buffer/accessor model

Now do the same again but using the USM model. Note that in the USM model
dependencies are defined explicitly by chaining commands via `event`s.

Again feel free to use any method of synchronization and copy back you like,
but remember to handle errors.

#### Build And Execution Hints

For For DPC++ (using the Intel DevCloud):
```sh
clang++ -fsycl -o sycl-ex-10 -I../External/Catch2/single_include ../Code_Exercises/Exercise_10_Managing_Dependencies/source.cpp
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
make exercise_10_managing_dependencies_source
./Code_Exercises/Exercise_10_Managing_Dependencies/exercise_10_managing_dependencies_source
```


For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_10_managing_dependencies_source
./Code_Exercises/Exercise_10_Managing_Dependencies/exercise_10_managing_dependencies_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_10_Managing_Dependencies
/path/to/hipsycl/bin/syclcc -o sycl-ex-10 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-10
```

[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
