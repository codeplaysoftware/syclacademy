# SYCL Academy

## Exercise 17: Vectors
---

In this exercise you will learn how to use `vec` to explicitly vectorized your
kernel function.

---

### 1.) Use vectors

Now that global memory access is coalesced another optimization you can do is to
use the `vec` class to present the pixels in the image.

To do this first you want to reinterpret the `buffer` objects as `buffer`s with
the element type `float4`. You can do this by calling `reinterpret` on the
`buffer`s and specifying the type `float4`.

Note you will have to provide a new `range`s which will be the original `range`s
divided by 4 to account for the channels which are now represented by the four
elements of the vector type.

### 2.) Refactor the kernel function

Now that you are using vector types, you want to replace the representation of
pixels in the kernel function with a `float4` and remove any multiplication or
offsets to account for the number of channels.

## Build and execution hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make exercise_17
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-17 -I../External/Catch2/single_include ../Code_Exercises/Exercise_17_Vectors/source.cpp
./sycl-ex-17
```

For AdaptiveCpp:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;generic" compiles for CPUs with the OpenMP backend and GPUs using the generic single-pass compiler.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_ADAPTIVECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/adaptivecpp -DACPP_TARGETS="<target specification>" ..
make exercise_17
```
alternatively, without CMake:
```sh
cd Code_Exercises/Exercise_17_Vectors
/path/to/adaptivecpp/bin/acpp -o sycl-ex-17 -I../../External/Catch2/single_include --acpp-targets="<target specification>" source.cpp
./sycl-ex-17
```
