# SYCL Academy

## Exercise 05: Image Convolution
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

#### Build And Execution Hints Using the DevCloud

For For DPC++:
```sh
icpx -fsycl -o sycl-ex-5 -I../../External/Catch2/single_include -I../../Utilities/include -I../../External/stb/ reference.cpp
```
In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only abvailable through the job queue.

We have provided a ready made script in the same directory as the source.cpp file, so you can call:

```sh
./q run.sh
```

[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
