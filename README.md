# SYCL Academy

![SYCL Academy](sycl_academy.png "SYCL Academy")

This repository provides materials that can be used for teaching SYCL. The
materials are provided using the "Creative Commons Attribution Share Alike 4.0
International" license.

## What is SYCL?

If you're not familiar with SYCL or would like some further resources for
learning about SYCL below are a list of useful resources:

*  Read a description of SYCL on the [Khronos website SYCL page](https://www.khronos.org/sycl/).
*  Go to the Khronos website to find [a list of SYCL resources](https://www.khronos.org/sycl/resources).
*  Check out the [SYCL 2020 reference guide](https://www.khronos.org/registry/SYCL/).
*  Browse SYCL news, blog posts, videos, projects and more on the [sycl.tech community website](https://sycl.tech/)
*  Get a list of the [available SYCL implementations](https://sycl.tech/#get-sycl)

### How to use the Materials

To use these materials simply clone this repository including the required submodules.

```
git clone --recursive https://github.com/codeplaysoftware/syclacademy.git
```

The lectures are written in reveal.js, and can be found in `Lesson_Materials`,
in the sub-directory for each topic. To view them simply open the `index.html`
file in your browser. Your browser will have a "Full Screen" mode that can be
used to run the presentation, use the right and left cursors to move forward and
backward in the presentation.

The exercises can be found in `Code_Exercises` in the sub-directory for each
topic. Each exercise has a markdown document instructing what to do in the
exercise, a source file to start with and a solution file to provide an
example implementation to compare against.

## Contributing to SYCL Academy

Contributions to the materials are very gratefully received and this can be done
by submitting a Pull Request with any changes. Please limit the scope of each
Pull Request so that they can be reviewed and merged in a timely manner.

### List of Contributors

Codeplay Software Ltd., Heidelberg University, Intel, and Xilinx.

## Supporting Organizations
Abertay University, Universidad de Concepcion, TU Dresden, University of
Edinburgh, Federal University of Sao Carlos, University of Glasgow, Heriot Watt
University, Universitat Innsbruck, Universidad de Málaga, University of Salerno
and University of the West of Scotland.

## Lesson Curriculum

The SYCL Academy curriculum is divided up into a number of short lessons
consisting of slides for presenting the material and a more detailed write-up,
each accompanied by a tutorial for getting hands on experience with the subject
matter.

Each of the lessons are designed to be self contained modules in order to
support both academic and training style teaching environments. 

A playlist of video content is [also available][video-playlist]. Though note that these
slides and exercises may have changed since these videos were created so they
may not match completely.

| Lesson | Title | Slides | Exercise | Source | Solution | ComputeCpp | DPC++ | hipSYCL |
|--------|-------|--------|----------|--------|----------|------------|-------|---------|
| 01 | What is SYCL | [slides][lesson-1-slides] | [exercise][lesson-1-exercise] | [source][lesson-1-source] | [solution][lesson-1-solution] | Yes | Yes | TBC |
| 02 | Enqueueing a Kernel | [slides][lesson-2-slides] | [exercise][lesson-2-exercise] | [source][lesson-2-source] | [solution][lesson-2-solution] | Yes | Yes | TBC |
| 03 | Managing Data | [slides][lesson-3-slides] | [exercise][lesson-3-exercise] | [source][lesson-3-source] | [solution][lesson-3-solution] | Yes | Yes | TBC |
| 04 | Handling Errors | [slides][lesson-4-slides] | [exercise][lesson-4-exercise] | [source][lesson-4-source] | [solution][lesson-4-solution] | Yes | Yes | TBC |
| 05 | Device Discovery | [slides][lesson-5-slides] | [exercise][lesson-5-exercise] | [source][lesson-5-source] | [solution][lesson-5-solution] | Yes | Yes | TBC |
| 06 | Data Parallelism | [slides][lesson-6-slides] | [exercise][lesson-6-exercise] | [source][lesson-6-source] | [solution][lesson-6-solution] | Yes | Yes | TBC |
| 07 | Introduction to USM | [slides][lesson-7-slides] | [exercise][lesson-7-exercise] | [source][lesson-7-source] | [solution][lesson-7-solution] | Yes | Yes | TBC |
| 08 | Using USM | [slides][lesson-8-slides] | [exercise][lesson-8-exercise] | [source][lesson-8-source] | [solution][lesson-8-solution] | Yes | Yes | TBC |
| 09 | Asynchronous Execution | [slides][lesson-9-slides] | [exercise][lesson-9-exercise] | [source][lesson-9-source] | [solution][lesson-9-solution] | Yes | Yes | TBC |
| 10 | Data and Dependencies | [slides][lesson-10-slides] | [exercise][lesson-10-exercise] | [source][lesson-10-source] | [solution][lesson-10-solution] | Yes | Yes | TBC |
| 11 | In Order Queue | [slides][lesson-11-slides] | [exercise][lesson-11-exercise] | [source][lesson-11-source] | [solution][lesson-11-solution] | Yes | Yes | TBC |
| 12 | Advanced Data Flow | [slides][lesson-12-slides] | [exercise][lesson-12-exercise] | [source][lesson-12-source] | [solution][lesson-12-solution] | Yes | Yes | TBC |
| 13 | Multiple Devices | [slides][lesson-13-slides] | [exercise][lesson-13-exercise] | [source][lesson-13-source] | [solution][lesson-13-solution] | Yes | Yes | TBC |
| 14 | ND Range Kernels | [slides][lesson-14-slides] | [exercise][lesson-14-exercise] | [source][lesson-14-source] | [solution][lesson-14-solution] | Yes | Yes | TBC |
| 15 | Image Convolution | [slides][lesson-15-slides] | [exercise][lesson-15-exercise] | [source][lesson-15-source] | [solution][lesson-15-solution] | Yes | Yes | TBC |
| 16 | Coalesced Global Memory | [slides][lesson-16-slides] | [exercise][lesson-16-exercise] | [source][lesson-16-source] | [solution][lesson-16-solution] | Yes | Yes | TBC |
| 17 | Vectorization | [slides][lesson-17-slides] | [exercise][lesson-17-exercise] | [source][lesson-17-source] | [solution][lesson-17-solution] | Yes | Yes | TBC |
| 18 | Local Memory Tiling | [slides][lesson-18-slides] | [exercise][lesson-18-exercise] | [source][lesson-18-source] | [solution][lesson-18-solution] | Yes | Yes | TBC |
| 19 | Further Optimisations | [slides][lesson-19-slides] | [exercise][lesson-19-exercise] | [source][lesson-19-source] | [solution][lesson-19-solution] | Yes | Yes | TBC |


## Building the Exercises

The exercises can be built for ComputeCpp CE 2.7.0 ASP (not the standard 2.7.0 branch; see below), DPC++ and hipSYCL.

### Supported Platforms

Below is a list of the supported platforms and devices for each SYCL implementations, 
please check this before deciding which SYCL implementation to use.
Make sure to also install the specified version to ensure that you can build
all of the exercises.

| Implementation | Supported Platforms | Supported Devices | Required Version |
|----------------|---------------------|-------------------|------------------|
| ComputeCpp | Windows 10 Visual Studio 2019 (64bit)* <br> Ubtuntu 18.04 (64bit) | Intel CPU (OpenCL) <br> Intel GPU (OpenCL) | CE 2.7.0 ASP |
| DPC++ | [Intel DevCloud](https://tinyurl.com/getdevcloud) <br> Windows 10 Visual Studio 2019 (64bit) <br> Red Hat Enterprise Linux 8, CentOS 8<br> Ubtuntu 18.04 LTS, 20.04 LTS (64bit)<br> Refer to [System Requirements][oneAPI-system-requirements] for more details | Intel CPU (OpenCL) <br> Intel GPU (OpenCL) <br> Intel FPGA (OpenCL) <br> Nvidia GPU (CUDA)** | 2021.4	|
| hipSYCL | Any Linux | CPU (OpenMP) <br> AMD GPU (ROCm)*** <br> Nvidia GPU (CUDA) | Latest develop branch |

\* See [here](troubleshooting-for-computecpp) for troubleshooting when using
ComputeCpp with Visual Studio post toolset version 14.26.

\*\* Supported in open source project only

\*\*\* See [here][rocm-gpus] for the official list of GPUs supported by AMD for
ROCm. We do not recommend using GPUs earlier than gfx9 (Vega 10 and Vega 20
chips).

### Install SYCL implementations

First you'll need to install your chosen SYCL implementation and any
dependencies they require.

#### Installing ComputeCpp

To set up ComputeCpp download the [ComputeCpp CE package][computecpp-download]
and follow the [getting started instructions][computecpp-getting-started].

#### Installing DPC++

To set up DPC++ follow the [getting started instructions][dpcpp-getting-started].

You can also use a [Docker* image][docker-container-oneapi].

If you are using the [Intel DevCloud][intel-devcloud] then the latest version of DPC++ will
already be installed and available in the path.

#### Installing hipSYCL

You will need a hipSYCL build from April 21st 2021 or newer. Refer to the [hipSYCL installation instructions][hipsycl-installing] for details on how to install hipSYCL.

### Pre-requisites

Before building the exercises you'll need:

* One of the platforms in the support matrix above, depending on which SYCL
implementation you are wishing to build for.
* A C++17 or above tool-chain.
* An appropriate build system for the platform you are targeting (CMake, Ninja,
Make, Visual Studio).

### Configuring using CMake (ComputeCpp CE and hipSYCL only)

Clone this repository, there are some additional dependencies configured as git
sub-modules so make sure to clone those as well. Then simply invoke CMake as
follows:

```
mkdir build

cd build

cmake ../ -G<cmake_generator> -A<cmake_arch> -D<sycl_implementation>=ON
```

For `<cmake_generator>` / `<cmake_arch>` we recommend:

* Visual Studio 16 2019 / x64 (Windows)
* Ninja / NA (Windows or Linux)
* Make / NA (Linux)

For `sycl_implementation` this can be one of:

* `SYCL_ACADEMY_USE_COMPUTECPP`
* `SYCL_ACADEMY_USE_HIPSYCL`

You can also specify the additional optional options:

-DSYCL_ACADEMY_INSTALL_ROOT=<path_to_sycl_impl_install_root>

For `<path_to_sycl_impl_install_root>` we recommend you specify the path to the
root directory of your SYCL implementation installation, though this may not
always be required.

-DSYCL_ACADEMY_ENABLE_SOLUTIONS=ON

This will enable building the solutions for each exercise as well as the source
files. This is disabled by default.

#### Additional cmake arguments for hipSYCL

When building with hipSYCL, cmake will additionally require you to specify the
target platform using `-DHIPSYCL_TARGETS=<target specification>`. 
`<target specification>` is a list of backends and devices to target, for example
`-DHIPSYCL_TARGETS="omp;hip:gfx900,gfx906"` compiles for CPUs with the OpenMP backend
and for AMD Vega 10 and Vega 20 GPUs using the HIP backend.
Available backends are:
* `omp` - OpenMP CPU backend
* `cuda` - CUDA backend for NVIDIA GPUs. Requires specification of targets of the form sm_XY, e.g. sm_70 for Volta, sm_60 for Pascal
* `hip`  - HIP backend for AMD GPUs. Requires specification of targets of the form gfxXYZ, e.g. gfx906 for Vega 20, gfx900 for Vega 10
* `spirv` - use clang SYCL driver to generate spirv (experimental)


### Compiling directly (DPC++ only)

If you are using DPC++ there is no CMake integration, but it is very simple to
use the DPC++ compiler directly.

First you have to ensure that your environment is configured to use DPC++ (note
if you are using the Intel DevCloud then you don't need to do this step).

On Linux simply call the `setvars.sh` which is available in `/opt/intel/oneapi` 
for sudo or root users and ~/intel/oneapi/ when installed as a normal user.

For root or sudo installations:
`source /opt/intel/oneapi/setvars.sh`

For normal user installations:
`source ~/intel/oneapi/setvars.sh`

On Windows the script is located in  `<dpc++_install_root>\setvars.bat`

Where `<dpc++_install_root>` is wherever the `oneAPI` directory is installed.

Once that's done you can invoke the DPC++ compiler as follows:

`dpcpp -I<syclacademy_root>/External/Catch2/single_include -o a.out source.cpp`

Where `<syclacademy_root>` is the path to the root directory of where you cloned
this repository. Note that on Windows you need to add the option /EHsc to avoid exception handling error. 

### Troubleshooting for ComputeCpp on Windows

If you are using ComputeCpp with a more recent version of Visual Sutdio 2019
which has a toolset version greater than 14.26 you may encounter compilation
errors in the C++ STL it's likely due to an unsupported version of the Visual
Studio toolset, if you encounter this the solution is to configure the project
to use an earlier troolset version, you can use the following steps to do this.

* As a pre-requisite, open the Visual Studio 2019 Installer, select "Modify" and
then open the "Individual components" tab and check the following components:
  * `MSVC v142 - VS 2019 C++ x64/x86 build tools (v14.26)`
  * `C++/CLI support for v142 build tools (14.26)`
* First we recommend opening the root directory of the SYCL Academy repository
in Visual Studio 2019 and configuring CMake this way rather than running CMake
on the command line as this makes configurating the toolset version easier.
* Ensure that you are building in Release mode.
* Next, add the following option to the CMake configuration:
  * `-DCOMPUTECPP_DEVICE_COMPILER_FLAGS=-D_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH"`
* Open `CMakeSettings.json` in the root directory and add the following:
```
  "environments": [
    {
      "VCToolsVersion" :  "14.26"
    }
  ],
```

## Online Interactive Tutorial

Hosted by tech.io, this [SYCL Introduction](https://tech.io/playgrounds/48226/introduction-to-sycl/introduction-to-sycl-2) tutorial introduces the concepts of SYCL. The website also provides the ability to compile and execute SYCL code from your web browser.



SYCL and the SYCL logo are trademarks of the Khronos Group Inc.

[computecpp-download]: https://developer.codeplay.com/products/computecpp/ce/download/?experimental=true
[computecpp-getting-started]: https://developer.codeplay.com/products/computecpp/ce/guides/getting-started?
[dpcpp-getting-started]: https://software.intel.com/content/www/us/en/develop/articles/installation-guide-for-intel-oneapi-toolkits.html
[intel-devcloud]: https://intelsoftwaresites.secure.force.com/devcloud/oneapi
[docker-container-oneapi]: https://software.intel.com/content/www/us/en/develop/documentation/get-started-with-intel-oneapi-base-linux/top/using-containers.html
[oneAPI-system-requirements]: https://software.intel.com/content/www/us/en/develop/articles/intel-oneapi-base-toolkit-system-requirements.html

[hipsycl-installing]: https://github.com/illuhad/hipSYCL/blob/develop/doc/installing.md
[rocm-gpus]: https://github.com/RadeonOpenCompute/ROCm#supported-gpus
[spack]: https://github.com/spack/spack

[video-playlist]: https://youtube.com/playlist?list=PLCssnq0MpRdM-IUAYtNSPYck6u3oz7OZQ

[lesson-1-slides]: ./Lesson_Materials/Lecture_01_What_is_SYCL/
[lesson-1-exercise]: ./Code_Exercises/Exercise_01_Compiling_with_SYCL/doc.md
[lesson-1-source]: ./Code_Exercises/Exercise_01_Compiling_with_SYCL/source.cpp
[lesson-1-solution]: ./Code_Exercises/Exercise_01_Compiling_with_SYCL/solution.cpp

[lesson-2-slides]: ./Lesson_Materials/Lecture_02_Enqueuing_a_Kernel/
[lesson-2-exercise]: ./Code_Exercises/Exercise_02_Hello_World/doc.md
[lesson-2-source]: ./Code_Exercises/Exercise_02_Hello_World/source.cpp
[lesson-2-solution]: ./Code_Exercises/Exercise_02_Hello_World/solution.cpp

[lesson-3-slides]: ./Lesson_Materials/Lecture_03_Managing_Data/
[lesson-3-exercise]: ./Code_Exercises/Exercise_03_Scalar_Add/doc.md
[lesson-3-source]: ./Code_Exercises/Exercise_03_Scalar_Add/source.cpp
[lesson-3-solution]: ./Code_Exercises/Exercise_03_Scalar_Add/solution.cpp

[lesson-4-slides]: ./Lesson_Materials/Lecture_04_Handling_Errors/
[lesson-4-exercise]: ./Code_Exercises/Exercise_04_Handling_Errors/doc.md
[lesson-4-source]: ./Code_Exercises/Exercise_04_Handling_Errors/source.cpp
[lesson-4-solution]: ./Code_Exercises/Exercise_04_Handling_Errors/solution.cpp

[lesson-5-slides]: ./Lesson_Materials/Lecture_05_Device_Discovery/
[lesson-5-exercise]: ./Code_Exercises/Exercise_05_Device_Selection/doc.md
[lesson-5-source]: ./Code_Exercises/Exercise_05_Device_Selection/source.cpp
[lesson-5-solution]: ./Code_Exercises/Exercise_05_Device_Selection/solution.cpp

[lesson-6-slides]: ./Lesson_Materials/Lecture_06_Data_Parallelism/
[lesson-6-exercise]: ./Code_Exercises/Exercise_06_Vector_Add/doc.md
[lesson-6-source]: ./Code_Exercises/Exercise_06_Vector_Add/source.cpp
[lesson-6-solution]: ./Code_Exercises/Exercise_06_Vector_Add/solution.cpp

[lesson-7-slides]: ./Lesson_Materials/Lecture_07_Introduction_to_USM/
[lesson-7-exercise]: ./Code_Exercises/Exercise_07_USM_Selector/doc.md
[lesson-7-source]: ./Code_Exercises/Exercise_07_USM_Selector/source.cpp
[lesson-7-solution]: ./Code_Exercises/Exercise_07_USM_Selector/solution.cpp

[lesson-8-slides]: ./Lesson_Materials/Lecture_08_Using_USM/
[lesson-8-exercise]: ./Code_Exercises/Exercise_08_USM_Vector_Add/doc.md
[lesson-8-source]: ./Code_Exercises/Exercise_08_USM_Vector_Add/source.cpp
[lesson-8-solution]: ./Code_Exercises/Exercise_08_USM_Vector_Add/solution.cpp

[lesson-9-slides]: ./Lesson_Materials/Lecture_09_Asynchronous_Execution/
[lesson-9-exercise]: ./Code_Exercises/Exercise_09_Synchronization/doc.md
[lesson-9-source]: ./Code_Exercises/Exercise_09_Synchronization/source.cpp
[lesson-9-solution]: ./Code_Exercises/Exercise_09_Synchronization/solution.cpp

[lesson-10-slides]: ./Lesson_Materials/Lecture_10_Data_and_Dependencies/
[lesson-10-exercise]: ./Code_Exercises/Exercise_10_Managing_Dependencies/doc.md
[lesson-10-source]: ./Code_Exercises/Exercise_10_Managing_Dependencies/source.cpp
[lesson-10-solution]: ./Code_Exercises/Exercise_10_Managing_Dependencies/solution.cpp

[lesson-11-slides]: ./Lesson_Materials/Lecture_11_In_Order_Queue/
[lesson-11-exercise]: ./Code_Exercises/Exercise_11_In_Order_Queue/doc.md
[lesson-11-source]: ./Code_Exercises/Exercise_11_In_Order_Queue/source.cpp
[lesson-11-solution]: ./Code_Exercises/Exercise_11_In_Order_Queue/solution.cpp

[lesson-12-slides]: ./Lesson_Materials/Lecture_12_Advanced_Data_Flow/
[lesson-12-exercise]: ./Code_Exercises/Exercise_12_Temporary_Data/doc.md
[lesson-12-source]: ./Code_Exercises/Exercise_12_Temporary_Data/source.cpp
[lesson-12-solution]: ./Code_Exercises/Exercise_12_Temporary_Data/solution.cpp

[lesson-13-slides]: ./Lesson_Materials/Lecture_13_Multiple_Devices/
[lesson-13-exercise]: ./Code_Exercises/Exercise_13_Load_Balancing/doc.md
[lesson-13-source]: ./Code_Exercises/Exercise_13_Load_Balancing/source.cpp
[lesson-13-solution]: ./Code_Exercises/Exercise_13_Load_Balancing/solution.cpp

[lesson-14-slides]: ./Lesson_Materials/Lecture_14_ND_Range_Kernel/
[lesson-14-exercise]: ./Code_Exercises/Exercise_14_ND_Range_Kernel/doc.md
[lesson-14-source]: ./Code_Exercises/Exercise_14_ND_Range_Kernel/source.cpp
[lesson-14-solution]: ./Code_Exercises/Exercise_14_ND_Range_Kernel/solution.cpp

[lesson-15-slides]: ./Lesson_Materials/Lecture_15_Image_Convolution/
[lesson-15-exercise]: ./Code_Exercises/Exercise_15_Image_Convolution/doc.md
[lesson-15-source]: ./Code_Exercises/Exercise_15_Image_Convolution/source.cpp
[lesson-15-solution]: ./Code_Exercises/Exercise_15_Image_Convolution/reference.cpp

[lesson-16-slides]: ./Lesson_Materials/Lecture_16_Coalesced_Global_Memory/
[lesson-16-exercise]: ./Code_Exercises/Exercise_16_Coalesced_Global_Memory/doc.md
[lesson-16-source]: ./Code_Exercises/Exercise_16_Coalesced_Global_Memory/source.cpp
[lesson-16-solution]: ./Code_Exercises/Exercise_16_Coalesced_Global_Memory/solution.cpp

[lesson-17-slides]: ./Lesson_Materials/Lecture_17_Vectors/
[lesson-17-exercise]: ./Code_Exercises/Exercise_17_Vectors/doc.md
[lesson-17-source]: ./Code_Exercises/Exercise_17_Vectors/source.cpp
[lesson-17-solution]: ./Code_Exercises/Exercise_17_Vectors/solution.cpp

[lesson-18-slides]: ./Lesson_Materials/Lecture_18_Local_Memory_Tiling/
[lesson-18-exercise]: ./Code_Exercises/Exercise_18_Local_Memory_Tiling/doc.md
[lesson-18-source]: ./Code_Exercises/Exercise_18_Local_Memory_Tiling/source.cpp
[lesson-18-solution]: ./Code_Exercises/Exercise_18_Local_Memory_Tiling/solution.cpp

[lesson-19-slides]: ./Lesson_Materials/Lecture_19_Work_Group_Sizes/
[lesson-19-exercise]: ./Code_Exercises/Exercise_19_Work_Group_Sizes/doc.md
[lesson-19-source]: ./Code_Exercises/Exercise_19_Work_Group_Sizes/source.cpp
[lesson-19-solution]: ./Code_Exercises/Exercise_19_Work_Group_Sizes/solution.cpp

