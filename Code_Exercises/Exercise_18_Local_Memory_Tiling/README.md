# SYCL Academy

## Exercise 18: Local Memory Tiling
---

In this exercise you will learn how to cache global memory into local memory in
tiles according to work-groups in order to compare the performance difference. 

---

### 1.) Use local memory

Allocate local memory for the kernel function by creating a local `accessor`.

The local `accessor` is created by specifying a `range` which is the number of
elements to allocate.

Note that local memory is allocated per work-group and each work-group can only
access it's own local memory.

### 2.) Cache global memory access in local memory

Cache the global memory required for each work-group in local memory by reading
from global `accessor` and then writing to the local `accessor`.

Remember to use the local id to know where in local memory to store the data,
this can be queried by calling the `nd_item` member function `get_local_id`.

Compare the performance with local memory and without local memory.

## Build and execution hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_BUILD_EXERCISES=18 
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make
./Code_Exercises/Exercise_18_Local_Memory_Tiling/exercise_18_local_memory_tiling_source
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-18 -I../External/Catch2/single_include ../Code_Exercises/Exercise_18_Local_Memory_Tiling/source.cpp
./sycl-ex-18
```

For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_14_nd_range_kernel_source
./Code_Exercises/Exercise_18_Local_Memory_Tiling/exercise_18_local_memory_tiling_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_18_Local_Memory_Tiling
/path/to/hipsycl/bin/syclcc -o sycl-ex-18 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-18
```
