# SYCL Academy

## Exercise 13: Load Balancing

---

In this exercise you will learn how to create two separate queues and then split
a task across two devices.

---

### 1.) Get two devices

Get two devices. If only host device is available then both devices may be identical, that is the host device.

### 2.) Create queues

Then create a `queue` for each of the two devices. 

### 3. ) Split a task across the two queues

Using either the application from exercise 6 using the buffer/accessor model or
the application from exercise 8 with the USM model create an application where
the work is distributed across two devices using the two `queue`s you created.

Remember to create separate `buffer`s for the separate parts of the data being
computed.

Remember to wait on the work enqueued to both`queue`s to complete and remember
to handle errors.

Also note that you will need to have different types defined to name each of the
two kernel kernel functions.

### 4. ) Tweak the load balancing

Try playing around with the distribution of the work between the two devices by
changing the `range` and `offset` of the two `buffer`s.

## Build and execution hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_BUILD_EXERCISES=13
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make
./Code_Exercises/Exercise_13_Load_Balancing/exercise_13_load_balancing_source
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-13 -I../External/Catch2/single_include ../Code_Exercises/Exercise_13_Load_Balancing/source.cpp
./sycl-ex-13
```

For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_13_load_balancing_source
./Code_Exercises/Exercise_13_Load_Balancing/exercise_13_load_balancing_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_13_Load_Balancing
/path/to/hipsycl/bin/syclcc -o sycl-ex-13 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-13
```