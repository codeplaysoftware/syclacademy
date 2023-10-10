# SYCL Academy

## Exercise 15: Image Convolution
---

In this exercise there is no task, simply familiarize yourself with the image
convolution reference code, as this will be used in later exercises.

---

### 1.) Reference image

For the purposes of this exercise we have provided an image in the exercise
directory called "dogs.png", however feel free to replace this with any other
32bit PNG image, though note that this exercise will work best with images
where the dimensions are multiples of 2, such as 512x512.

Note you will have to update the path to an image. There is the image in the
repository but feel free to use any image you choose. Though it's recommend that
you use a png image whose dimensions are multiple of 2 (for example 512x512)
and has four channels (RGBA).

### 2.) Stb library

The source for this example provides a stub which loads and write an image using
the STB image library.

### 3.) Benchmarking

The source also contains a call to a benchmarking utility that will print the
time taken to execute the SYCL code, the SYCL code should go inside the lambda
that is passed to the `benchmark` function.

Though note that the benchmark facility provided measures whole application time
which is less accurate than measuring the kernel execution times alone.

Try running the application and recording the benchmark result timing you see so
you can compare this with results in later exercises.

Note if you are running on the host device the default iterations for the
benchmark of 100 will take a while to execute so try reducing this number.

### 4.) Dimensionality

The reference code uses a 2-dimensional `range` in `parallel_for` as this often
simplifies the code when working with images.

### 5.) Convolution filters

The image convolution support code provides a `filter_type` enum which allows
you to choose between `identity` and `blur`. The utility for generating the
filter data; `generate_filter` takes a `filter_type` and a width.

## Build and execution hints

For DPC++:
Using CMake to configure then build the exercise:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_BUILD_EXERCISES=15 
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
make
./Code_Exercises/Exercise_15_Image_Convolution/exercise_15_image_convolution_reference
```
Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o sycl-ex-15 -I../../Utilities/include/ -I../../External/stb reference.cpp
```

For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_15_image_convolution_reference
./Code_Exercises/Exercise_15_Image_Convolution/exercise_15_image_convolution_reference
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_15_Image_Convolution
/path/to/hipsycl/bin/syclcc -o sycl-ex-15 -I../../Utilities/include/ -I../../External/stb --hipsycl-targets="<target specification>" reference.cpp
```