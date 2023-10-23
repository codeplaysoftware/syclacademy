# SYCL Academy

## Exercise 5: Device Selection

---

In this exercise you will learn how to create a device selector that will choose
a device for you to enqueue work to.

---

### 1.) Query the device of your queue

When you default construct a `queue` the runtime will use the `default_selector_v`
to choose a device. 

Try querying the `device` associated with the `queue` and information about it.

Remember the device associated with a queue can be retrieved using the
`get_device` member function and information about a device can be queried
using the `get_info` member function template.

### 2.) Try other device selectors

Replace the default selector with one of the other standard device selectors
that are provided by SYCL such as the `cpu_selector_v`, `gpu_selector_v` 
and see which device those choose.

### 3.) Create your own device selector

Create a device selector using the template below. Implement the function
call operator, using various device and platform info queries like the one we
used earlier to query the device name and then use that device selector in the
queue constructor. 

To construct device selector, use the following rule:

The interface for a `device selector` is any object that meets the C++ named requirement `Callable`, 
taking a parameter of type `const device &` and returning a value that is implicitly convertible to `int`.

```
  int device_selector()(const device &device) { /* scoring logic */ }
```

Remember the platform associated with a device can be retrieved using the
`get_platform` member function.

Remember that the value returned from the device selector's function call
operator will represent the score for each device, and a device with a negative
score will never be chosen. 


#### Build And Execution Hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make exercise_5
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-5 -I../External/Catch2/single_include ../Code_Exercises/Exercise_05_Device_Selection/source.cpp
./sycl-ex-5
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
cmake -DSYCL_ACADEMY_USE_ADAPTIVECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/adaptivecpp -DADAPTIVECPP_TARGETS="<target specification>" ..
make exercise_5
```
alternatively, without CMake:
```sh
cd Code_Exercises/Exercise_05_Device_Selection
/path/to/adaptivecpp/bin/syclcc -o sycl-ex-5 -I../../External/Catch2/single_include --adaptivecpp-targets="<target specification>" source.cpp
./sycl-ex-5
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
