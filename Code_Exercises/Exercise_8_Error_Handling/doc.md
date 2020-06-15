# SYCL Academy

### Exercise 8: Error Handling

---

In this first exercise you will learn:
* How to catch a synchronous exception
* How to catch an asynchronous exception

---

Almost certainly, at some point, you will come across an error scenario in your 
SYCL code. This exercise helps you to understand how to use exceptions and 
console prints to capture initial error information that might be useful for 
you to figure out why the error is occuring.

1.) Add synchronous exception handling

Synchronous errors, such as failure to construct an object, are reported 
immediately  by  the  runtime  throwing  an  exception.

Add a synchronous exception handler to the SYCL code.

2. ) Catch and asynchronous exceptions

Asynchronous  errors,  such  as  an  error  occurring  during execution of a 
kernel on a device, are reported via user-supplied asynchronous error-handlers.

This time add an asynchronous exception handler to the SYCL code. Then 
compile and run the code to see the details of the asynchronous exception that is 
thrown.

3. ) Fix the code

See if you can figure out why the exception is being thrown from the error 
message and fix it.

#### Build And Execution Hints

For For DPC++ (using the Intel DevCloud):

```
dpcpp -o sycl-ex-8 -I../External/Catch2/single_include ../Code_Exercises/Exercise_8_Error_Handling/source.cpp
```

In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only abvailable through the job queue.
Please refer to the [example][devcloud-job-submission].

So wrap the binary into a script `job_submission` and run:
```
qsub job_submission
```

For ComputeCpp:
```
cmake -DSYCL_ACADEMY_USE_COMPUTECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/computecpp ..
make Exercise_8_source
./Code_Exercises/Exercise_8_Error_Handling/Exercise_8_source
```

For hipSYCL:
```
# Add -DHIPSYCL_GPU_ARCH=<arch> to the cmake arguments when compiling for GPUs.
# <arch> is e.g. sm_60 for NVIDIA Pascal GPUs, gfx900 for AMD Vega 56/64, and gfx906 for Radeon VII.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_PLATFORM=<cpu|cuda|rocm> ..
make Exercise_8_source
./Code_Exercises/Exercise_8_Hello_World/Exercise_8_source
```
alternatively, without cmake:
```
cd Code_Exercises/Exercise_8_Hello_World
HIPSYCL_PLATFORM=<cpu|cuda|rocm> HIPSYCL_GPU_ARCH=<arch-when-compiling-for-gpu> /path/to/hipsycl/bin/syclcc -o sycl-ex-3 -I../../External/Catch2/single_include source.cpp
./sycl-ex-8
```

*Note:* Printing from kernels is still experimental on ROCm, so you might get an empty output when using the hipSYCL ROCm backend. In this case, try using the CPU backend instead.

[sycl-specification]: https://www.khronos.org/registry/SYCL/specs/sycl-1.2.1.pdf
[devcloud-job-submission]: https://devcloud.intel.com/oneapi/learn/advanced-queue/basic-job-submission#command-file-job-script-