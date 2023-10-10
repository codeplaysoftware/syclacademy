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
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_BUILD_EXERCISES=17 
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make
./Code_Exercises/Exercise_17_Vectors/exercise_17_vectors_source
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-17 -I../External/Catch2/single_include ../Code_Exercises/Exercise_17_Vectors/source.cpp
./sycl-ex-17
```

For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_17_vectors_source
./Code_Exercises/Exercise_17_Vectors/exercise_17_vectors_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_17_Vectors
/path/to/hipsycl/bin/syclcc -o sycl-ex-17 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-17
```
