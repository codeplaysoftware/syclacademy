# SYCL Academy

## Exercise 5: Vector Add

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


#### Build And Execution Hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make exercise_5
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-5 -I../External/Catch2/single_include ../Code_Exercises/Exercise_05_Vector_Add/source.cpp
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
# "omp;generic" compiles for CPUs with the OpenMP backend and GPUs using the generic single-pass compiler.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_ADAPTIVECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/adaptivecpp -DACPP_TARGETS="<target specification>" ..
make exercise_5
```
alternatively, without CMake:
```sh
cd Code_Exercises/Exercise_05_Vector_Add
/path/to/adaptivecpp/bin/acpp -o sycl-ex-5 -I../../External/Catch2/single_include --acpp-targets="<target specification>" source.cpp
./sycl-ex-5
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
