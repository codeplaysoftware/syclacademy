# SYCL Academy for SC23

![SYCL Academy](sycl_academy_black.png#gh-light-mode-only "SYCL Academy")
![SYCL Academy](sycl_academy_white.png#gh-dark-mode-only "SYCL Academy")

This repository provides materials that can be used for teaching SYCL. The
materials are provided using the "Creative Commons Attribution Share Alike 4.0
International" license.

### How to use the Materials

To use these materials simply clone this repository including the required submodules.
Don't forget to use the correct branch for SC23!

```
git clone --recursive --branch sc23 https://github.com/codeplaysoftware/syclacademy.git
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

## Lesson Curriculum for SC23

| Lesson | Title | Slides | Exercise | Source | Solution | DPC++ | AdaptiveCpp |
|--------|-------|--------|----------|--------|----------|-------|---------|
| 01 | What is SYCL | [slides][lesson-1-slides] | [exercise][lesson-1-exercise] | [source][lesson-1-source] | [solution][lesson-1-solution] | Yes | Yes |
| 02 | Data Management | [slides][lesson-2-slides] | [exercise][lesson-2-exercise] | [source][lesson-2-source] | [solution][lesson-2-solution] | Yes | Yes |
| 03 | Error Handling | [slides][lesson-3-slides] | [exercise][lesson-3-exercise] | [source][lesson-3-source] | [solution][lesson-3-solution] | Yes | Yes |
| 04 | Device Selections | [slides][lesson-4-slides] | [exercise][lesson-4-exercise] | [source][lesson-4-source] | [solution][lesson-4-solution] | Yes | Yes |
| 05 | Data Parallelism | [slides][lesson-5-slides] | [exercise][lesson-5-exercise] | [source][lesson-5-source] | [solution][lesson-5-solution] | Yes | Yes |
| 06 | Asynchronous Execution | [slides][lesson-6-slides] | [exercise][lesson-6-exercise] | [source][lesson-6-source] | [solution][lesson-6-solution] | Yes | Yes |
| 07 | ND Range Kernels | [slides][lesson-7-slides] | [exercise][lesson-7-exercise] | [source][lesson-7-source] | [solution][lesson-7-solution] | Yes | Yes |
| 08 | Using USM | [slides][lesson-8-slides] | [exercise][lesson-8-exercise] | [source][lesson-8-source] | [solution][lesson-8-solution] | Yes | Yes |

## Building the Exercises

During the tutorial at SC23 we will use the DevCloud environment to run through the hands on exercises.
You can set up the DevCloud by following the instructions [here](https://tinyurl.com/getdevcloud).

### Supported Platforms

Below is a list of the supported platforms and devices for each SYCL implementations, 
please check this before deciding which SYCL implementation to use.
Make sure to also install the specified version to ensure that you can build
all of the exercises.

| Implementation | Supported Platforms | Supported Devices | Required Version |
|----------------|---------------------|-------------------|------------------|
| DPC++ | [Intel DevCloud](https://tinyurl.com/getdevcloud) <br> Windows 10 Visual Studio 2019 (64bit) <br> Red Hat Enterprise Linux 8, CentOS 8<br> Ubtuntu 18.04 LTS, 20.04 LTS (64bit)<br> Refer to [System Requirements][oneAPI-system-requirements] for more details | Intel CPU (OpenCL) <br> Intel GPU (OpenCL) <br> Intel FPGA (OpenCL) <br> Nvidia GPU (CUDA)* | 2021.4	|
| AdaptiveCpp | Any Linux | CPU (OpenMP) <br> AMD GPU (ROCm)*** <br> NVIDIA GPU (CUDA)<br> Intel GPU (Level Zero)<br> Intel CPU, GPU (OpenCL) | 23.10.0 from Nov 1, 2023 or newer |

\* Supported in open source project only

\*\* See [here][rocm-gpus] for the official list of GPUs supported by AMD for
ROCm. We do not recommend using GPUs earlier than gfx9 (Vega 10 and Vega 20
chips).

### Install SYCL implementations

First you'll need to install your chosen SYCL implementation and any
dependencies they require.

#### Installing DPC++

To set up DPC++ follow the [getting started instructions][dpcpp-getting-started].

You can also use a [Docker* image][docker-container-oneapi].

If you are using the [Intel DevCloud][intel-devcloud] then the latest version of DPC++ will
already be installed and available in the path.

#### Installing AdaptiveCpp

You will need a AdaptiveCpp (formerly hipSYCL) build from September 2021 or newer. Refer to the [AdaptiveCpp installation instructions][adaptivecpp-installing] for details on how to install AdaptiveCpp.

### Pre-requisites

Before building the exercises you'll need:

* One of the platforms in the support matrix above, depending on which SYCL
implementation you are wishing to build for.
* A C++17 or above tool-chain.
* An appropriate build system for the platform you are targeting (CMake, Ninja,
Make, Visual Studio).

### Configuring using CMake 

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
* Make / NA (Linux) i.e. "-GUnix Makefiles"

For `sycl_implementation` this can be one of:

* `SYCL_ACADEMY_USE_ADAPTIVECPP`
* `SYCL_ACADEMY_USE_DPCPP`

You can also specify the additional optional options:

-DSYCL_ACADEMY_INSTALL_ROOT=<path_to_sycl_impl_install_root>

For `<path_to_sycl_impl_install_root>` we recommend you specify the path to the
root directory of your SYCL implementation installation, though this may not
always be required.

-DSYCL_ACADEMY_ENABLE_SOLUTIONS=ON

This will enable building the solutions for each exercise as well as the source
files. This is disabled by default.

-DCMAKE_BUILD_TYPE=Release

The build configuration for all exercises defaults to a debug build if this option is not specified.

#### Additional cmake arguments for DPC++

-DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx

This SYCL Academy CMake configuration uses the Intel oneAPI IntelSYCL CMake module package to assist it in its configuration. These command line arguments must be used to initiate this configuration correctly.

#### Additional cmake arguments for AdaptiveCpp

When building with AdaptiveCpp, cmake will additionally require you to specify the
target platform using `-DACPP_TARGETS=<target specification>`. 
`<target specification>` is a list of compilation flows to enable and devices to target, for example
`-DACPP_TARGETS="omp;generic"` compiles for CPUs using OpenMP and GPUs using the generic single-pass compiler.

Available compilation flows are:
* `omp` - OpenMP CPU backend
* `generic` - Generic single-pass compiler. Generates a binary that runs on AMD, NVIDIA and Intel GPUs using runtime compilation
* `cuda` - CUDA backend for NVIDIA GPUs. Requires specification of targets of the form sm_XY, e.g. sm_70 for Volta, sm_60 for Pascal
* `hip`  - HIP backend for AMD GPUs. Requires specification of targets of the form gfxXYZ, e.g. gfx906 for Vega 20, gfx900 for Vega 10

When in doubt, use `-DACPP_TARGETS=omp;generic`.

#### CMake usage example

Invoking CMake from the command line example usage:
```
  cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=ON -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
```

### Getting started with compiling DPC++

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

`icpx -fsycl -I<syclacademy_root>/External/Catch2/single_include -o a.out source.cpp`

Where `<syclacademy_root>` is the path to the root directory of where you cloned
this repository. Note that on Windows you need to add the option /EHsc to avoid exception handling error. 

The CMake configuration can also be used to build the exercises, see the section **Configuring using CMake** above.

## Working on the Exercises
Once you have a working SYCL compiler, you are ready to start writing some SYCL code. To find the first exercise:
```
cd Code_Exercises/Exercise_01_Compiling_with_SYCL/
```
And read the README.md for further instructions. 

Each exercise directory contains:
* ```README.md```, which contains instructions of how to complete a given exercise, as well as directions for compilation.
* ```source.cpp```, a placeholder file where your code implementation should be written. 
* ```solution.cpp```, where a solution has been implemented in advance. 

Once you have completed any given exercise make sure to compare your implementation against the corresponding ```solution.cpp```. 

## Contributing to SYCL Academy

Contributions to the materials are very gratefully received and this can be done
by submitting a Pull Request with any changes. If you can, follow the
instructions [here](https://revealjs.com/pdf-export/) to generate a pdf file for
any lecture slides you change. Please limit the scope of each
Pull Request so that they can be reviewed and merged in a timely manner.

### List of Contributors

Codeplay Software Ltd., Heidelberg University, Intel, Xilinx and University of Bristol.

## Supporting Organizations

Abertay University, Universidad de Concepcion, TU Dresden, University of
Edinburgh, Federal University of Sao Carlos, University of Glasgow, Heriot Watt
University, Universitat Innsbruck, Universidad de Málaga, University of Salerno
and University of the West of Scotland.

SYCL and the SYCL logo are trademarks of the Khronos Group Inc.

[dpcpp-getting-started]: https://software.intel.com/content/www/us/en/develop/articles/installation-guide-for-intel-oneapi-toolkits.html
[intel-devcloud]: https://intelsoftwaresites.secure.force.com/devcloud/oneapi
[docker-container-oneapi]: https://software.intel.com/content/www/us/en/develop/documentation/get-started-with-intel-oneapi-base-linux/top/using-containers.html
[oneAPI-system-requirements]: https://software.intel.com/content/www/us/en/develop/articles/intel-oneapi-base-toolkit-system-requirements.html

[adaptivecpp-installing]: https://github.com/AdaptiveCpp/AdaptiveCpp/blob/develop/doc/installing.md
[rocm-gpus]: https://github.com/RadeonOpenCompute/ROCm#supported-gpus
[spack]: https://github.com/spack/spack

[video-playlist]: https://youtube.com/playlist?list=PLCssnq0MpRdM-IUAYtNSPYck6u3oz7OZQ

[lesson-1-slides]: ./Lesson_Materials/Lecture_01_Big_Hello_SYCL/
[lesson-1-exercise]: ./Code_Exercises/Exercise_01_Big_Hello_SYCL/README.md
[lesson-1-source]: ./Code_Exercises/Exercise_01_Big_Hello_SYCL/source.cpp
[lesson-1-solution]: ./Code_Exercises/Exercise_01_Big_Hello_SYCL/solution.cpp

[lesson-2-slides]: ./Lesson_Materials/Lecture_02_Data_Management/
[lesson-2-exercise]: ./Code_Exercises/Exercise_02_Data_Management/README.md
[lesson-2-source]: ./Code_Exercises/Exercise_02_Data_Management/source.cpp
[lesson-2-solution]: ./Code_Exercises/Exercise_02_Data_Management/solution.cpp

[lesson-3-slides]: ./Lesson_Materials/Lecture_03_Error_Handling/
[lesson-3-exercise]: ./Code_Exercises/Exercise_03_Error_Handling/README.md
[lesson-3-source]: ./Code_Exercises/Exercise_03_Error_Handling/source.cpp
[lesson-3-solution]: ./Code_Exercises/Exercise_03_Error_Handling/solution.cpp

[lesson-4-slides]: ./Lesson_Materials/Lecture_04_Device_Selections/
[lesson-4-exercise]: ./Code_Exercises/Exercise_04_Device_Selections/README.md
[lesson-4-source]: ./Code_Exercises/Exercise_04_Device_Selections/source.cpp
[lesson-4-solution]: ./Code_Exercises/Exercise_04_Device_Selections/solution.cpp

[lesson-5-slides]: ./Lesson_Materials/Lecture_05_Data_Parallelism/
[lesson-5-exercise]: ./Code_Exercises/Exercise_05_Vector_Add/README.md
[lesson-5-source]: ./Code_Exercises/Exercise_05_Vector_Add/source.cpp
[lesson-5-solution]: ./Code_Exercises/Exercise_05_Vector_Add/solution.cpp

[lesson-6-slides]: ./Lesson_Materials/Lecture_06_Asynchronous_Execution/
[lesson-6-exercise]: ./Code_Exercises/Exercise_06_Synchronization/README.md
[lesson-6-source]: ./Code_Exercises/Exercise_06_Synchronization/source.cpp
[lesson-6-solution]: ./Code_Exercises/Exercise_06_Synchronization/solution.cpp

[lesson-7-slides]: ./Lesson_Materials/Lecture_07_ND_Range_Kernel/
[lesson-7-exercise]: ./Code_Exercises/Exercise_07_ND_Range_Kernel/README.md
[lesson-7-source]: ./Code_Exercises/Exercise_07_ND_Range_Kernel/source.cpp
[lesson-7-solution]: ./Code_Exercises/Exercise_07_ND_Range_Kernel/solution.cpp

[lesson-8-slides]: ./Lesson_Materials/Lecture_08_GPU_Programming_Principles/
[lesson-8-exercise]: ./Code_Exercises/Exercise_08_Matrix_Transpose/README.md
[lesson-8-source]: ./Code_Exercises/Exercise_08_Matrix_Transpose/source.cpp
[lesson-8-solution]: ./Code_Exercises/Exercise_08_Matrix_Transpose/solution.cpp
