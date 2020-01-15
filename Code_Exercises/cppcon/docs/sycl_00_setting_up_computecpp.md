# Parallelism in Modern C++; from CPU to GPU
### Exercise 0: Setting up ComputeCpp

---

In this exercise you will learn:
* How to install ComputeCpp and its dependencies.
* How to create and compile a SYCL application using ComputeCpp.

---

1.) Install ComputeCpp

ComputeCpp is an implementation of SYCL 1.2.1 developed by Codeplay. It is the first complete and conformant implementation of the standard and a free community edition is available to download.

You can download the ComputeCpp CE package from the [developer portal][computecpp-developer-portal] (you will need to create an account). ComputeCpp CE is available on Windows 7/10, Ubuntu 14.04/16.04 and CentOS.

If you do not have a supported operating system you can download and run the Ubuntu 16.04 docker image. To do this you'll need to first install [Docker][docker-installer] and then once you have your Docker environment configured pull and run the ComputeCpp Ubutnu 16.04 docker image:

```
docker pull aerialmantis/computecpp_ubuntu1604
docker run --rm -it aerialmantis/computecpp_ubuntu1604
```

2.) Install dependencies

ComputeCpp supports a wide range of OpenCL devices, however, in addition to installing ComputeCpp you must also install the relevant OpenCL drivers for the device you wish to run on.

If you are using the docker image, the Intel OpenCL drivers will already be installed so you can skip this step.

Please follow the links before to find the appropriate OpenCL drivers for the device you wishing to use:
* [Intel OpenCL drivers][intel-drivers]
* [AMD OpenCL drivers][amd-drivers]
* [Nvidia OpenCL drivers][nvidia-drivers]

Please note that:
* Not all AMD devices will be supported by ComputeCpp as some more recent AMD drivers do not support SPIR.
* Nvidia GPU support is still experimental and is not yet available on Windows.

For the purposes of this class, we recommend that you use a GPU, however, all exercises can be done using a CPU device or event the host device (an emulated OpenCL device available with ComputeCpp that can be used when OpenCL is not available). However, note that performance will vary between the CPU and the GPU.

3.) Check your installation

The ComputeCpp CE package comes with a tool called computecpp_info, which can be used to list all of the devices available on your machine that can be used by ComputeCpp. This can be used to check that you have the appropriate drivers installed to allow you to use your chosen device. It will also inform you whether that particular device is tested for ComputeCpp CE.

When you run computecpp_info you will get something like:

```
********************************************************************************

ComputeCpp Info (CE 1.1.4)

SYCL 1.2.1 revision 3

********************************************************************************


Device Info:

Discovered 2 devices matching:
  platform    : <any>
  device type : <any>

--------------------------------------------------------------------------------
Device 0:

  Device is supported                     : NO - Device does not support SPIR
  CL_DEVICE_NAME                        : GeForce GTX 1060 6GB
  CL_DEVICE_VENDOR                    : NVIDIA Corporation
  CL_DRIVER_VERSION                   : 417.35
  CL_DEVICE_TYPE                          : CL_DEVICE_TYPE_GPU
--------------------------------------------------------------------------------
Device 1:

  Device is supported                     : YES - Tested internally by Codeplay Software Ltd.
  CL_DEVICE_NAME                        : Intel(R) Core(TM) i7-7700K CPU @ 4.20GHz
  CL_DEVICE_VENDOR                    : Intel(R) Corporation
  CL_DRIVER_VERSION                   : 6.4.0.37
  CL_DEVICE_TYPE                          : CL_DEVICE_TYPE_CPU

If you encounter problems when using any of these OpenCL devices, please consult
this website for known issues:
https://computecpp.codeplay.com/releases/v1.1.4/platform-support-notes

********************************************************************************
```

You can also add the option --verbose to display further information about the devices.

From this you should confirm that you have a supported platform and that the CE version is 1.1.4.

4.) Compile a SYCL application

Once you have ComputeCpp and the OpenCL devices for your chosen device installed you are ready to compile your first SYCL application.

The best way to do this is to download this repository and build the first example.

Clone this repository.

```
git clone https://github.com/AerialMantis/cppcon-parallelism-class.git
```

Create a build directory.

```
cd cppcon-parallelism-class
mkdir build
cd build
```

Run CMake to configure the solutions (local setup)

```
cmake ../ -G[Generator] -DCMAKE_BUILD_TYPE=Debug
```

Run CMake to configure the solutions (Docker setup)
```
cmake ../ -GNinja -DCMAKE_BUILD_TYPE=Debug -DOpenCL_LIBRARY=${OCL_LIB}/libOpenCL.so -DOpenCL_INCLUDE_DIR=${OCL_INC}
```

Note that if you are using an NVidia GPU, in order to use the experimental ComputeCpp SYCL support you must include the following in the above CMake command:

```
-DCOMPUTECPP_BITCODE=ptx64
```

Note that you can disable the SYCL tests in the case you are not able to use ComputeCpp by adding the following in the above CMake command:

```
-DCPPCON_ENABLE_SYCL=OFF
```

Build your solution:

```
cmake --build .
```

Verify your setup by running the hello world example:


```
./examples/example_verify_sycl
```

[computecpp-developer-portal]: https://developer.codeplay.com/home/
[docker-installer]: https://docs.docker.com/install/
[intel-drivers]: https://software.intel.com/en-us/articles/opencl-drivers
[amd-drivers]: https://www.amd.com/en/support
[nvidia-drivers]: https://developer.nvidia.com/cuda-toolkit-32-downloads
