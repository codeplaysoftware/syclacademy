## Exercise 8: Local Memory Matrix Transpose
---

This exercise uses GPU specific features in order to gain good GPU performance.
While code will run on other hardware, the local memory tiled solution may not
give as good performance as it does on a GPU.

In this exercise you will learn how to cache global memory into local memory in
tiles according to work-groups in order to compare the performance difference. 

In order to get good performance, make sure that global memory accesses are 
coalesced. Local memory accesses do not have as large a penalty for
uncoalesced memeory accesses.


### 1.) Use local memory

Allocate local memory for the kernel function by creating a `local_accessor`.

The `local_accessor` is created by specifying a `range` which is the number of
elements to allocate.

Note that local memory is allocated per work-group and each work-group can only
access its own local memory.

### 2.) Cache global memory access in local memory

Cache the global memory required for each work-group in local memory by reading
from global `accessor` and then writing to the local `accessor`.

Then write from the local accessor to the global memory output accessor in a
coalesced fashion.

Compare the performance with local memory and without local memory.

#### Build And Execution Hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make exercise_8
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-8 -I ../../Utilities/include ../Code_Exercises/Exercise_08_Matrix_Transpose/source.cpp
./sycl-ex-8
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
cmake -DSYCL_ACADEMY_USE_ADAPTIVECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/adaptivecpp -DACPP_TARGETS="<target specification>" ..
make exercise_8
```
alternatively, without CMake:
```sh
cd Code_Exercises/Exercise_08_Matrix_Transpose
/path/to/adaptivecpp/bin/acpp -o sycl-ex-8 -I ../../Utilities/include source.cpp --acpp-targets="<target specification>" source.cpp
./sycl-ex-8
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
