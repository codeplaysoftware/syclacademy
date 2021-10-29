# SYCL Academy

## Exercise 9: Synchronization
---

In this exercise you will learn how to use different techniques for
synchronizing commands and data.

---

### 1.) Waiting on events

Take a look at the vector add applications using the buffer/accessor model in
exercise 6 and the USM model in exercise 8, and familiarize yourself with how
they call `wait` on returned `event`s to synchronize the completion of the work.

### 2.) Waiting on queues

With those same applications convert them to call `wait` on the `queue` to
synchronize instead.

### 3.) Buffer destruction

Take a look at the vector add application using the buffer/accessor mode in
exercise 6 and how it synchronizes on the destruction of the `buffer`s. 

### 4.) Copy back

Take a look that two applications again and familiarize yourself with how the
result of the computation is copied back to the host.

In the case of the application using the buffer/accessor model note how this
occurs implicitly on the destruction of the `buffer`.

In the case of the application using the USM model note how this occurs
explicitly by calling `memcpy`.

### 4.) Host accessor

Finally with the application which is using the buffer/accessor model introduce
a host `accessor` by calling `get_host_access` on the `buffer`. The host
`accessor` can be used to check the result of the computation on the host while
the `buffer` is still alive.

Remember to do this within a scope to ensure the host `accessor` is destroyed.

Also note that creating a host `accessor` may copy the data back to the original
pointer provided to the `buffer` but this is not guaranteed.

#### Build And Execution Hints

For For DPC++ (using the Intel DevCloud):
```sh
clang++ -fsycl -o sycl-ex-9 -I../External/Catch2/single_include ../Code_Exercises/Exercise_09_Synchronization/source.cpp
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
make exercise_09_synchronization_source
./Code_Exercises/Exercise_09_Synchronization/exercise_09_synchronization_source
```


For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_09_synchronization_source
./Code_Exercises/Exercise_09_Synchronization/exercise_09_synchronization_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_09_Synchronization
/path/to/hipsycl/bin/syclcc -o sycl-ex-9 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-9
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
