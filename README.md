# SYCL Academy - IWOCL & SYCLcon 2023

![SYCL Academy](sycl_academy.png "SYCL Academy")

This repository provides materials that can be used for teaching SYCL. The
materials are provided using the "Creative Commons Attribution Share Alike 4.0
International" license.

These materials have been adapted for the SYCL tutorial at IWOCL and SYCLcon.
See the main branch of this repository for all the materials available.

## How to use the Materials

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

## Setting up the Intel DevCloud

There are multiple SYCL implementations but for simplicity due to the limited 
time during the SYCLcon training we will use the Intel DevCloud which is 
pre-configured with the DPC++ compiler.

Go to the [Intel DevCloud for oneAPI](https://devcloud.intel.com/oneapi/get_started/) 
and click on 'Get Free Access' to create a new account if you don't have it.
For more details please refer to the document [Getting Started with Intel DevCloud][DevCloud-getting-started]

There are two options to connect to the DevCloud: via SSH or using JupyterLab.
It is recommended to use the JupyterLab terminal for simplicity.

Go to [this page](https://devcloud.intel.com/oneapi/get_started/) and scroll to the 
bottom of the page. Then click on the 'Launch JupyterLab*' link on the bottom of the 
page to connect with the Jupyter* Lab.

You will then see a "Welcome to Jupyter Notebooks on the Intel DevCloud for oneAPI 
Projects!" document which covers the basics of the JupyterLab access to the Intel 
DevCloud for oneAPI Projects.

**To do the exercises for this tutorial select File -> New -> Terminal and open a 
terminal window. This gives you command line access to the cloud machine.**

## Lesson Curriculum for IWOCL & SYCLcon 23

The SYCL Academy curriculum is divided up into a number of short lessons
consisting of slides for presenting the material and a more detailed write-up,
each accompanied by a tutorial for getting hands on experience with the subject
matter.

Each of the lessons are designed to be self contained modules in order to
support both academic and training style teaching environments. 

| Lesson | Title | Slides | Exercise | Source | Solution |
|--------|-------|--------|----------|--------|----------|
| 01 | GPU programming and SYCL recap | [slides][lesson-1-slides] | NA | NA |
| 02 | In Order Queue | [slides][lesson-2-slides] | [exercise][lesson-2-exercise] | [source][lesson-2-source] | [solution][lesson-2-solution] |
| 03 | Multiple Devices | [slides][lesson-3-slides] | [exercise][lesson-3-exercise] | [source][lesson-3-source] | [solution][lesson-3-solution] |
| 04 | More SYCL Features | [slides][lesson-4-slides] | [exercise][lesson-4-exercise] | [source][lesson-4-source] | [solution][lesson-4-solution] |
| 05 | Image Convolution | [slides][lesson-5-slides] | [exercise][lesson-5-exercise] | [source][lesson-5-source] | [solution][lesson-5-solution] |
| 06 | Coalesced Global Memory | [slides][lesson-6-slides] | [exercise][lesson-6-exercise] | [source][lesson-6-source] | [solution][lesson-6-solution] |
| 07 | Vectorization | [slides][lesson-7-slides] | [exercise][lesson-7-exercise] | [source][lesson-7-source] | [solution][lesson-7-solution] |
| 08 | Local Memory Tiling | [slides][lesson-8-slides] | [exercise][lesson-8-exercise] | [source][lesson-8-source] | [solution][lesson-8-solution] |

## Building the Exercises

The exercises can be built using the command listed in the individual exercise README.

## What is SYCL?

If you're not familiar with SYCL or would like some further resources for
learning about SYCL below are a list of useful resources:

*  Read a description of SYCL on the [Khronos website SYCL page](https://www.khronos.org/sycl/).
*  Go to the Khronos website to find [a list of SYCL resources](https://www.khronos.org/sycl/resources).
*  Check out the [SYCL 2020 reference guide](https://www.khronos.org/registry/SYCL/).
*  Browse SYCL news, blog posts, videos, projects and more on the [sycl.tech community website](https://sycl.tech/)
*  Get a list of the [available SYCL implementations](https://sycl.tech/#get-sycl)

## Contributing to SYCL Academy

Contributions to the materials are very gratefully received and this can be done
by submitting a Pull Request with any changes. Please limit the scope of each
Pull Request so that they can be reviewed and merged in a timely manner.

### List of Contributors

Codeplay Software Ltd., Heidelberg University, Intel, Xilinx and University of Bristol.

## Supporting Organizations
Abertay University, Universidad de Concepcion, TU Dresden, University of
Edinburgh, Federal University of Sao Carlos, University of Glasgow, Heriot Watt
University, Universitat Innsbruck, Universidad de Málaga, University of Salerno
and University of the West of Scotland.

## Install SYCL implementations

The alternative to using DevCloud is to install the specific SYCL implementation.

### Installing DPC++

To set up DPC++ follow the [getting started instructions][dpcpp-getting-started]. The recommended version is 2023.1.

You can also use a [Docker* image][docker-container-oneapi].

If you are using the [Intel DevCloud][intel-devcloud] then the latest version of DPC++ will
already be installed and available in the path.

### Installing hipSYCL

Refer to the [hipSYCL installation instructions][hipsycl-installing] for details on how to install hipSYCL.

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

### Additional cmake arguments for hipSYCL

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

## Working on the Exercises
Once you have a working SYCL compiler, you are ready to start writing some SYCL code. To find the first exercise:
```
cd Code_Exercises/Exercise_02_In_Order_Queue/
```
And read the README.md for further instructions. 

Each exercise directory contains:
* ```README.md```, which contains instructions of how to complete a given exercise, as well as directions for compilation.
* ```source.cpp```, a placeholder file where your code implementation should be written. 
* ```solution.cpp```, where a solution has been implemented in advance. 

Once you have completed any given exercise make sure to compare your implementation against the corresponding ```solution.cpp```. 

SYCL and the SYCL logo are trademarks of the Khronos Group Inc.

[dpcpp-getting-started]: https://software.intel.com/content/www/us/en/develop/articles/installation-guide-for-intel-oneapi-toolkits.html
[intel-devcloud]: https://devcloud.intel.com/oneapi/get_started/
[docker-container-oneapi]: https://www.intel.com/content/www/us/en/docs/oneapi-base-toolkit/get-started-guide-linux/2023-1/using-containers.html

[hipsycl-installing]: https://github.com/illuhad/hipSYCL/blob/develop/doc/installing.md


[lesson-1-slides]: ./Lesson_Materials/Lecture_01_GPU_programming_and_SYCL_recap/Lecture_00_GPU_programming_and_SYCL_recap.pdf

[lesson-2-slides]: ./Lesson_Materials/Lecture_02_In_Order_Queue/Lecture_02_In_Order_Queue.pdf
[lesson-2-exercise]: ./Code_Exercises/Exercise_02_In_Order_Queue/README.md
[lesson-2-source]: ./Code_Exercises/Exercise_02_In_Order_Queue/source.cpp
[lesson-2-solution]: ./Code_Exercises/Exercise_02_In_Order_Queue/solution.cpp

[lesson-3-slides]: ./Lesson_Materials/Lecture_03_Multiple_Devices/Lecture_03_Multiple_Devices.pdf
[lesson-3-exercise]: ./Code_Exercises/Exercise_03_Load_Balancing/README.md
[lesson-3-source]: ./Code_Exercises/Exercise_03_Load_Balancing/source.cpp
[lesson-3-solution]: ./Code_Exercises/Exercise_03_Load_Balancing/solution.cpp

[lesson-4-slides]: ./Lesson_Materials/Lecture_04_More_SYCL_Features/Lecture_04_More_SYCL_Features.pdf
[lesson-4-exercise]: ./Code_Exercises/Exercise_04_SYCL_Reduction/README.md
[lesson-4-source]: ./Code_Exercises/Exercise_04_SYCL_Reduction/
[lesson-4-solution]: ./Code_Exercises/Exercise_04_SYCL_Reduction/

[lesson-5-slides]: ./Lesson_Materials/Lecture_05_Image_Convolution/Lecture_05_Image_Convolution.pdf
[lesson-5-exercise]: ./Code_Exercises/Exercise_05_Image_Convolution/README.md
[lesson-5-source]: ./Code_Exercises/Exercise_05_Image_Convolution/source.cpp
[lesson-5-solution]: ./Code_Exercises/Exercise_05_Image_Convolution/solution.cpp

[lesson-6-slides]: ./Lesson_Materials/Lecture_06_Coalesced_Global_Memory/Lecture_06_Coalesced_Global_Memory.pdf
[lesson-6-exercise]: ./Code_Exercises/Exercise_06_Coalesced_Global_Memory/README.md
[lesson-6-source]: ./Code_Exercises/Exercise_06_Coalesced_Global_Memory/source.cpp
[lesson-6-solution]: ./Code_Exercises/Exercise_06_Coalesced_Global_Memory/solution.cpp

[lesson-7-slides]: ./Lesson_Materials/Lecture_07_Vectors/Lecture_07_Vectors.pdf
[lesson-7-exercise]: ./Code_Exercises/Exercise_07_Vectors/README.md
[lesson-7-source]: ./Code_Exercises/Exercise_07_Vectors/source.cpp
[lesson-7-solution]: ./Code_Exercises/Exercise_07_Vectors/solution.cpp

[lesson-8-slides]: ./Lesson_Materials/Lecture_08_Local_Memory_Tiling/Lecture_08_Local_Memory_Tiling.pdf
[lesson-8-exercise]: ./Code_Exercises/Exercise_08_Local_Memory_Tiling/README.md
[lesson-8-source]: ./Code_Exercises/Exercise_08_Local_Memory_Tiling/source.cpp
[lesson-8-solution]: ./Code_Exercises/Exercise_08_Local_Memory_Tiling/solution.cpp

[DevCloud-getting-started]: ./Code_Exercises/Getting_started_with_Intel_DevCloud.pdf