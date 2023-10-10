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
`"sycl/sycl.hpp"`.

Make sure before you do this you define `SYCL_LANGUAGE_VERSION` to `2020`, to
enable support for the SYCL 2020 interface.

Once that is done build your source file with your chosen build system.

### 5.) Compile and run

Once you've done that simply build the exercise with your chosen build system
and invoke the executable.

#### Build And Execution Hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_BUILD_EXERCISES=1 
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make
./Code_Exercises/Exercise_01_compiling_with_sycl/exercise_01_compiling_with_sycl_source
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-1 -I../External/Catch2/single_include ../Code_Exercises/Exercise_01_compiling_with_sycl/source.cpp
./sycl-ex-1
```
In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only available through the job queue.
Please refer to the [guide][devcloud-job-submission].

So wrap the binary into a script `job_submission` and run:
```sh
qsub job_submission
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
