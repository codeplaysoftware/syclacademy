# SYCL Academy

## Exercise 7: USM Selector
---

In this exercise you will learn how to find a suitable device for using the USM data management model.

---

### 1.) Create a device selector

Create a custom device selector as you did in exercise 5.

### 2.) Check for USM support

Within this device selector check for whether the device being inspected has
support for the USM device allocations.

This can be querying for the `aspect::usm_device_allocations` aspect.

### 3.) Create a queue

Once you have a device selector which will choose a device which supports USM
create a `queue` using it to select its device, remember to handle errors.


#### Build And Execution Hints

For For DPC++ (using the Intel DevCloud):
```sh
clang++ -fsycl -o sycl-ex-7 -I../External/Catch2/single_include ../Code_Exercises/Exercise_07_USM_Selector/source.cpp
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
make exercise_07_usm_selector_source
./Code_Exercises/Exercise_07_USM_Selector/exercise_07_usm_selector_source
```


For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_07_usm_selector_source
./Code_Exercises/Exercise_07_USM_Selector/exercise_07_usm_selector_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_07_USM_Selector
/path/to/hipsycl/bin/syclcc -o sycl-ex-7 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-7
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
