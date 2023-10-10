# SYCL Academy

## Exercise 11: In Order Queue
---

In this exercise you will learn how to create a fixed data flow using an
in-order `queue`.

---

### 1.) In order queue with buffer/accessor model

Using the application from exercise 10 which uses the buffer/accessor model
convert the `queue` to in-order using the `property::queue::in_order` property,
converting the data flow graph to a fixed execution order.

Feel free to have the kernel functions execute in any order you like providing
the necessary dependencies described in exercise 10 are still met.

### 2.) In order queue with USM model

Now do the same using the application from exercise 10 which uses the USM model,
again converting the `queue` to in-order, converting the data flow graph to a
fixed execution order.

Again feel free to have the kernel functions execute in any order you like
providing the necessary dependencies described in exercise 10 are still met.

Note that in the USM model when using an in-order `queue` it is no longer
necessary to chain commands using `event`s.

## Build and execution hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_BUILD_EXERCISES=11 
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make
./Code_Exercises/Exercise_11_In_Order_Queue/exercise_11_in_order_queue_source
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-11 -I../External/Catch2/single_include ../Code_Exercises/Exercise_11_In_Order_Queue/source.cpp
./sycl-ex-11
```

For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_11_in_order_queue_source
./Code_Exercises/Exercise_11_In_Order_Queue/exercise_11_in_order_queue_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_11_In_Order_Queue
/path/to/hipsycl/bin/syclcc -o sycl-ex-11 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-11
```