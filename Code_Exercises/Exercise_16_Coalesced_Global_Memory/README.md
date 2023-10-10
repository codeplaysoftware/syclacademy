# SYCL Academy

## Exercise 16: Coalesced Global Memory
---

In this exercise you will learn how to apply row-major and column-major when
linearizing the global id in order to compare the performance difference due to
coalesced global memory access.

---

### 1.) Evaluate global memory access

Now that you have a working image convolution kernel you should evaluate whether the
global memory access patterns in your kernel are coalesced.

Consider two alternative ways to linearize the global id:

```
auto rowMajorLinearId    = (idx[1] * width) + idx[0];  // row-major
auto columnMajorLinearId = (idx[0] * height) + idx[1];  // column-major
```

Try using both of these and compare the execution time of each.

## Build and execution hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_BUILD_EXERCISES=16 
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make
./Code_Exercises/Exercise_16_Coalesced_Global_Memory/exercise_16_coalesced_global_memory_source
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-16 -I../External/Catch2/single_include ../Code_Exercises/Exercise_16_Coalesced_Global_Memory/source.cpp
./sycl-ex-16
```

For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_16_coalesced_global_memory_source
./Code_Exercises/Exercise_16_Coalesced_Global_Memory/exercise_16_coalesced_global_memory_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_16_Coalesced_Global_Memory
/path/to/hipsycl/bin/syclcc -o sycl-ex-16 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-16
```
