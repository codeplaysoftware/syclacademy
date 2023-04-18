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


#### Build And Execution Hints

For DPC++ (using the Intel DevCloud):
```sh
icpx -fsycl -o sycl-ex-6 -I../External/Catch2/single_include ../Code_Exercises/Exercise_06_Vector_Add/source.cpp
```
In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only available through the job queue.
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
