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

For DevCloud via SSH follow these [instructions](../devcloud.md).

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make exercise_19_source
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-19 -I../External/Catch2/single_include ../Code_Exercises/Exercise_19_Work_Group_Sizes/source.cpp
./sycl-ex-19
```

For AdaptiveCpp:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;generic" compiles for CPUs with the OpenMP backend and GPUs using the generic single-pass compiler.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_ADAPTIVECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/AdaptiveCpp -DACPP_TARGETS="<target specification>" ..
make exercise_19
```
alternatively, without CMake:
```sh
cd Code_Exercises/Exercise_19_Work_Group_Sizes
/path/to/adaptivecpp/bin/acpp -o sycl-ex-19 -I../../External/Catch2/single_include --acpp-targets="<target specification>" source.cpp
./sycl-ex-19
```
