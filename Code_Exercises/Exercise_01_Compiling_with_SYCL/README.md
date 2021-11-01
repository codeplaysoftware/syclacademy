# SYCL Academy

## Exercise 1: Compiling with SYCL

---

For this first exercise you simply need to install a SYCL implementation and the SYCL
Academy dependencies and then verify your installation by comping a source file
for SYCL.

### 1.) Installing a SYCL implementation

To install a SYCL implementation, follow the instructions in the README.md of the SYCL
Academy repository.

### 2.) Verifying your environment

Depending on the SYCL implementation used, the steps to verify your environment might vary.

#### When using ComputeCpp

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

#### When using hipSYCL

With hipSYCL, you can skip this step. If you suspect later that your environment might not be set up correctly, you can set the environment variable `HIPSYCL_DEBUG_LEVEL=3` and execute your program. hipSYCL will then print (among many other things) all devices that it can find, for example:
```sh
[hipSYCL Info] Discovered devices from backend 'OpenMP': 
[hipSYCL Info]   device 0: 
[hipSYCL Info]     vendor: the hipSYCL project
[hipSYCL Info]     name: hipSYCL OpenMP host device
```
*Note: You may not see this output in this exercise because we do not yet actually use any SYCL functionality. Consequently, there is no need for the hipSYCL runtime to launch and print diagnostic information.*

### 3.) Configuring the exercise project

Once you have confirmed your environment is setup and available you are ready to
compile your first SYCL application from source code.

First fetch the tutorial samples from GitHub.

Clone this repository ensuring that you include sub-modules.

```
git clone --recursive https://github.com/codeplaysoftware/syclacademy.git
mkdir build
cd build
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
clang++ -fsycl -o sycl-ex-1 -I../External/Catch2/single_include ../Code_Exercises/Exercise_01_compiling_with_SYCL/source.cpp
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
make exercise_01_compiling_with_sycl_source
./Code_Exercises/Exercise_01_Compiling_with_SYCL/exercise_01_compiling_with_sycl_source
```


For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_01_compiling_with_sycl_source
./Code_Exercises/Exercise_01_Compiling_with_SYCL/exercise_01_compiling_with_sycl_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_01_compiling_with_SYCL
/path/to/hipsycl/bin/syclcc -o sycl-ex-1 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-1
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
