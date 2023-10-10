# SYCL Academy

## Exercise 19: Work-Group Sizes
---

In this exercise you will learn how to use different work-group sizes in order
to compare the performance difference.

---

### 1.) Try different work-group sizes

In order to optimize for occupancy try different work-group sizes, by specifying
a different local range for the `nd_range`.

Note that if the work-group size exceeds the maximum work-group size the target
device supports then it will fail to execute.

Compare the performance of the various work-group sizes you try.

## Build and execution hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_BUILD_EXERCISES=19 
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make
./Code_Exercises/Exercise_19_Work_Group_Sizes/exercise_19_work_group_sizes_source
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-19 -I../External/Catch2/single_include ../Code_Exercises/Exercise_19_Work_Group_Sizes/source.cpp
./sycl-ex-19
```

For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_19_work_group_sizes_source
./Code_Exercises/Exercise_19_Work_Group_Sizes/exercise_19_work_group_sizes_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_19_Work_Group_Sizes
/path/to/hipsycl/bin/syclcc -o sycl-ex-19 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-19
```