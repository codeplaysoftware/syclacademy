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

For DevCloud via SSH follow these [instructions](../devcloud.md).

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make exercise_4_source
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-4 -I../External/Catch2/single_include ../Code_Exercises/Exercise_04_Handling_Errors/source.cpp
./sycl-ex-4
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
# "omp;generic" compiles for CPUs with the OpenMP backend and GPUs using the generic single-pass compiler.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_ADAPTIVECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/AdaptiveCpp -DACPP_TARGETS="<target specification>" ..
make exercise_4
```
alternatively, without CMake:
```sh
cd Code_Exercises/Exercise_04_Handling_Errors
/path/to/AdaptiveCpp/bin/acpp -o sycl-ex-4 -I../../External/Catch2/single_include --acpp-targets="<target specification>" source.cpp
./sycl-ex-4
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
