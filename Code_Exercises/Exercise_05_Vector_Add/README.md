# SYCL Academy

## Exercise 6: Vector Add

---

In this exercise you will learn how add the values in two arrays and write the
results to another array in parallel using `parallel_for`.

---

### 1.) Create your queue

Create a `queue` to enqueue your kernel function to, remember to handle errors.

### 2. ) Create buffers

Create `buffer`s to manage the data of the two input arrays and output array.

Remember to ensure the `range` provided to the buffer is the size of the arrays.

### 3. ) Create accessors

Create `accessor`s to each of the `buffer`s within the command group function.

### 4. ) Write the kernel function

Now enqueue parallel kernel function by calling `parallel_for` on the `handler`.

This function takes a `range` specifying the number of iterations of the kernel
function to invoke and the kernel function itself must take an `id` which
represents the current iteration.

The `id` can be used in the `accessor` subscript operator to access or assign to
the corresponding element of data that the accessor represents.

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
clang++ -fsycl -o sycl-ex-6 -I../External/Catch2/single_include ../Code_Exercises/Exercise_06_Vector_Add/source.cpp
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
make exercise_06_vector_add source
./Code_Exercises/Exercise_06_Vector_Add/exercise_06_vector_add source
```


For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_06_vector_add
./Code_Exercises/Exercise_06_Vector_Add/exercise_06_vector_add_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_06_Vector_Add
/path/to/hipsycl/bin/syclcc -o sycl-ex-6 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-6
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
