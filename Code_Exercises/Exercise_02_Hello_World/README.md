# SYCL Academy

## Exercise 2: Hello World

---

In this first exercise you will learn how to enqueue your first kernel function
to run on a device and print `Hello World!` to the console.

---

### 1.) Create a queue

The first thing you must do is create a `queue` to submit work to. The simplest
way to do this is to default construct it, this will choose a device for you.

### 2.) Define a command group

Once you have a `queue` you can now submit work to be executed on the device
that `queue` is targeting and this is done via a command group.

Define a lambda expression which takes a reference to a `handler` to represent
your command group function and pass it to the `submit` member function of the
`queue`.

Note that submitting a command group without any commands will result in an
error.

### 3.) Define a SYCL kernel function

Within the command group function define a SYCL kernel function via the
`single_task` command within the command group, which takes only a function
object which itself doesn't take any parameters.

Remember to declare a class for your kernel name in the global namespace. While
it is possible to leave the class declaration inline in the handler scope, this
can produce long kernel names that show up in profiler and debugger output and
make it harder to use. Defining the kernel names out of local scope avoids
this.

Also remember to call `wait` on the `event` returned from `submit` to await the
completion of the kernel function.

### 4.) Stream "Hello World!" to stdout

Create a `stream` object within the command group scope. The parameters to the
constructor of the `stream` class are the total buffer size, the work-item
buffer size and the `handler`.

Then use the stream you constructed within the SYCL kernel function to print
`"Hello world!"` using the `<<` operator.

#### Build And Execution Hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON 
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make exercise_2
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-2 -I../External/Catch2/single_include ../Code_Exercises/Exercise_02_Hello_World/source.cpp
./sycl-ex-2
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
cmake -DSYCL_ACADEMY_USE_ADAPTIVECPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF
-DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/adaptivecpp -DADAPTIVECPP_TARGETS="<target specification>" ..
make exercise_2
```
alternatively, without CMake:
```sh
cd Code_Exercises/Exercise_02_Hello_World
/path/to/adaptivecpp/bin/syclcc -o sycl-ex-2 -I../../External/Catch2/single_include --adaptivecpp-targets="<target specification>" source.cpp
./sycl-ex-2
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
