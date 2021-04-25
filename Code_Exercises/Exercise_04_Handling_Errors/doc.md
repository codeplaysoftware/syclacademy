# SYCL Academy

## Exercise 4: Handling Errors

---

In this exercise you will learn how to handle synchronous and asynchronous
exceptions.

---

### 1.) Catch synchronous exception handling

Synchronous errors, such as failure to construct an object, are reported
immediately  by  the  runtime  throwing  an  exception.

To catch synchronous exceptions simply wrap your application in a try catch
block and catch a SYCL `exception` and print out the error message provided by
the `what` member function.

### 2. ) Catch and asynchronous exceptions

Asynchronous  errors, such  as  an  error  occurring  during execution of a
kernel on a device, are reported via user-supplied asynchronous error-handlers.

To catch asynchronous exceptions create an async handler using a lambda
expression which takes an `exception_list`, iterates over it and rethrows the
exceptions to be caught by the surrounding try-catch block.

#### Build And Execution Hints

For For DPC++ (using the Intel DevCloud):
```sh
dpcpp -o sycl-ex-4 -I../External/Catch2/single_include ../Code_Exercises/Exercise_04_Handling_Errors/source.cpp
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
make exercise_04_handling_errors_source
./Code_Exercises/Exercise_04_Handling_Errors/exercise_04_handling_errors source
```


For hipSYCL:
```sh
# Add -DHIPSYCL_GPU_ARCH=<arch> to the cmake arguments when compiling for GPUs.
# <arch> is e.g. sm_60 for NVIDIA Pascal GPUs, gfx900 for AMD Vega 56/64, and gfx906 for Radeon VII.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_PLATFORM=<cpu|cuda|rocm> ..
make exercise_04_handling_errors source
./Code_Exercises/Exercise_04_Handling_Errors/exercise_04_handling_errors source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_04_Handling_Errors
HIPSYCL_PLATFORM=<cpu|cuda|rocm> HIPSYCL_GPU_ARCH=<arch-when-compiling-for-gpu> /path/to/hipsycl/bin/syclcc -o sycl-ex-4 -I../../External/Catch2/single_include source.cpp
./sycl-ex-4
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/