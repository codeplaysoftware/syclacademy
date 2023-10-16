# SYCL Academy

## Exercise 12: Temporary Data
---

In this exercise you will learn how to use temporary data and avoid unnecessary
copies to and from the device.

---

### 1.) Temporary data with buffer/accessor model

Using what you've learnt so far write a SYCL application that has two kernels,
where the first kernel reads in from an input and writes to an intermediate data
and the second reads that intermediate data and writes to an output.

Feel free to have the kernel functions perform any computation you like, and
feel free to use any method of synchronization and copy back you like.

To ensure the input `buffer` doesn't copy back to the original pointer call
`set_final_data` on it with `nullptr`.

To ensure the intermediate `buffer` doesn't copy to or from the device, create
it as uninitialized.

To ensure the output `buffer` is copied back create is as uninitialized and then
call `set_final_data` on it with the address of the output memory.

### 2.) Temporary data with USM model

Now do the same but using the USM model.

Again, feel free to have the kernel functions perform any computation you like,
and feel free to use any method of synchronization and copy back you like.

Note that when using the USM model since it's an explicit model to avoid
unnecessary copies you can simply not perform those copies.

## Build and execution hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_BUILD_EXERCISES=12 
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make
./Code_Exercises/Exercise_12_Temporary_Data/exercise_12_temporary_data_source
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-12 -I../External/Catch2/single_include ../Code_Exercises/Exercise_12_Temporary_Data/source.cpp
./sycl-ex-12
```

For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_12_temporary_data_source
./Code_Exercises/Exercise_12_Temporary_Data/exercise_12_temporary_data_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_12_Temporary_Data
/path/to/hipsycl/bin/syclcc -o sycl-ex-12 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-12
```
