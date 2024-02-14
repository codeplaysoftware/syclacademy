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

#### When using AdaptiveCpp

With AdaptiveCpp, you can skip this step. If you suspect later that your environment might not be set up correctly, you can run `acpp-info -l` in the `bin`  directory of your AdaptiveCpp installation. It will then print the backends and devices that it sees, for example:
```
$ acpp-info -l
=================Backend information===================
Loaded backend 0: OpenCL
  Found device: Intel(R) UHD Graphics 620 [0x5917]
  Found device: ComputeAorta x86_64
  Found device: Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz
Loaded backend 1: OpenMP
  Found device: hipSYCL OpenMP host device
Loaded backend 2: CUDA
  Found device: NVIDIA GeForce MX150
Loaded backend 3: Level Zero
  Found device: Intel(R) UHD Graphics 620 [0x5917]
```

### If you're using DevCloud via SSH

If you have not already installed SYCLAcademy, follow this [guide](../../README.md#connecting-to-devcloud-via-ssh) to perform the installation.

Go to the exercise 01 directory:
From the syclacademy directory
```
cd build/Code_Exercises/Exercise_01_compiling_with_sycl
```
and continue to [4](#4-include-the-sycl-header-file)

### 3.) Configuring the exercise project

Once you have confirmed your environment is setup and available you are ready to
compile your first SYCL application from source code.

First fetch the tutorial samples from GitHub.

Clone this repository ensuring that you include sub-modules.

```sh
git clone --recursive https://github.com/codeplaysoftware/syclacademy.git
mkdir build
cd build
```

### 4.) Include the SYCL header file

Then open the source file for this exercise and include the SYCL header file
`"sycl/sycl.hpp"`.

Make sure before you do this you define `SYCL_LANGUAGE_VERSION` to `2020`, to
enable support for the SYCL 2020 interface.

Once that is done build your source file with your chosen build system.

### 5.) Compile and run

Once you've done that simply build the exercise with your chosen build system
and invoke the executable.

#### Build And Execution Hints

If you are using DevCloud via SSH:

From the syclacademy directory
```
cd build/Code_Exercises/Exercise_01_compiling_with_sycl
```
and execute:
* ```make exercise_1_source``` - to build source.cpp
* ```make exercise_1_solution``` - to build the solution provided
* ```make``` - to build both

In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only available through the job queue.
Please refer to the [guide][devcloud-job-submission].

So wrap the binary into a script `job_submission`
```
#!/bin/bash
./exercise_1_source
```
and run:
```sh
qsub -l nodes=1:gpu:ppn=2 -d . job_submission
```

The stdout will be stored in ```job_submission.o<job id>``` and stderr in ```job_submission.e<job id>```.

Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make exercise_1
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-1 -I../External/Catch2/single_include ../Code_Exercises/Exercise_01_compiling_with_sycl/source.cpp
./sycl-ex-1
```

For AdaptiveCpp:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;generic" compiles for CPUs with the OpenMP backend and GPUs using the generic single-pass compiler.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_ADAPTIVECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/AdaptiveCpp -DACPP_TARGETS="<target specification>" ..
make exercise_1
```
alternatively, without CMake:
```sh
cd Code_Exercises/Exercise_01_compiling_with_SYCL
/path/to/AdaptiveCpp/bin/acpp -o sycl-ex-1 -I../../External/Catch2/single_include --acpp-targets="<target specification>" source.cpp
./sycl-ex-1
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
