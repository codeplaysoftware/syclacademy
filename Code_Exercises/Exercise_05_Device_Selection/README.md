# SYCL Academy

## Exercise 5: Device Selection

---

In this exercise you will learn how to create a device selector that will choose
a device for you to enqueue work to.

---

### 1.) Query the device of your queue

When you default construct a `queue` the runtime will use the `default_selector`
to choose a device. 

Try querying the `device` associated with the `queue` and information about it.

Remember the device associated with a queue can be retrieved using the
`get_device` member function and information about a device can be queried
using the `get_info` member function template.

### 2.) Try other device selectors

Replace the default selector with one of the other standard device selectors
that are provided by SYCL such as the `cpu_selector`, `gpu_selector` or
`host_selector` and see which device those choose.

### 3.) Create your own device selector

Create a device selector using the template below, implementing the function
call operator, using various device and platform info queries like the one we
used earlier to query the device name and then use that device selector in the
queue constructor:

```
class my_device_selector : public device_selector {
 public:
  my_device_selector() {}

  virtual int operator()(const device &device) const { /* scoring logic */ }
};
```

Remember the platform associated with a device can be retrieved using the
`get_platform` member function.

Remember that the value returned from the device selector's function call
operator will represent the score for each device, and a device with a negative
score will never be chosen. 

## SYCL Academy

## Exercise 1: Compiling with SYCL

---

For this first exercise you simply need to install ComputeCpp and the SYCL
Academy dependencies and then verify your installation by comping a source file
for SYCL.

### 1.) Installing ComputeCpp

To install ComputeCpp follow the instructions in the README.md of the SYCL
Academy repository for installing ComputeCpp and the necessary OpenCL drivers.

### 2.) Verifying your environment

ComputeCpp includes a tool called `computecpp_info` which lists all the
devices available on your machine and displays which are setup with the correct
drivers.

Open a console and run the executable located in the 'bin' directory of the
ComputeCpp release package:

```
./computecpp_info
```

Look for the lines that say:
```
  Device is supported                     : YES - Tested internally by Codeplay
  Software Ltd.
```

You can also add the option --verbose to display further information about the
devices.

From this output you can confirm your environment is setup correctly.

### 3.) Configuring the exercise project

Once you have confirmed your environment is setup and available you are ready to
compile your first SYCL application from source code.

First fetch the tutorial samples from GitHub.

Clone this repository ensuring that you include sub-modules.

```
git clone --recursive https://github.com/codeplaysoftware/syclacademy.git
```

### 4.) Include the SYCL header file

Then open the source file for this exercise and include the SYCL header file
`"CL/sycl.hpp"`.

Make sure before you do this you define `SYCL_LANGUAGE_VERSION` to `2020`, to
enable support for the SYCL 2020 interface.

Once that is done build your source file with your chosen build system.

### 5.) Compile and run

Once you've done that simply build the exercise with your chosen build system
and invoke the executable.


#### Build And Execution Hints

For For DPC++ (using the Intel DevCloud):
```sh
clang++ -fsycl -o sycl-ex-5 -I../External/Catch2/single_include ../Code_Exercises/Exercise_05_Device_Selection/source.cpp
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
make exercise_05_device_selection_source
./Code_Exercises/Exercise_05_Device_Selection/exercise_04_handling_errors source
```


For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_05_device_selection_source
./Code_Exercises/Exercise_05_Device_Selection/exercise_05_device_selection_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_05_Device_Selection
/path/to/hipsycl/bin/syclcc -o sycl-ex-5 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-5
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
