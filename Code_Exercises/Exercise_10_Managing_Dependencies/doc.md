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

# SYCL Academy

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
`"SYCL/sycl.hpp"`.

Make sure before you do this you define `SYCL_LANGUAGE_VERSION` to `2020`, to
enable support for the SYCL 2020 interface.

Once that is done build your source file with your chosen build system.

### 5.) Compile and run

Once you've done that simply build the exercise with your chosen build system
and invoke the executable.


#### Build And Execution Hints

For For DPC++ (using the Intel DevCloud):
```sh
dpcpp -o sycl-ex-10 -I../External/Catch2/single_include ../Code_Exercises/Exercise_10_Managing_Dependencies/source.cpp
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
# Add -DHIPSYCL_GPU_ARCH=<arch> to the cmake arguments when compiling for GPUs.
# <arch> is e.g. sm_60 for NVIDIA Pascal GPUs, gfx900 for AMD Vega 56/64, and gfx906 for Radeon VII.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_PLATFORM=<cpu|cuda|rocm> ..
make exercise_10_managing_dependencies_source
./Code_Exercises/Exercise_10_Managing_Dependencies/exercise_10_managing_dependencies_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_10_Managing_Dependencies
HIPSYCL_PLATFORM=<cpu|cuda|rocm> HIPSYCL_GPU_ARCH=<arch-when-compiling-for-gpu> /path/to/hipsycl/bin/syclcc -o sycl-ex-10 -I../../External/Catch2/single_include source.cpp
./sycl-ex-10
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/