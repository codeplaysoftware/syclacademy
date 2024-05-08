
# SYCL Academy

![SYCL Academy](sycl_academy_black.png#gh-light-mode-only "SYCL Academy")
![SYCL Academy](sycl_academy_white.png#gh-dark-mode-only "SYCL Academy")

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

## How to use the Materials

To use these materials, simply clone this repository, including the required submodules.
**Make sure you clone the correct branch**

```
git clone --recursive --branch isc24 https://github.com/codeplaysoftware/syclacademy.git
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


## Lesson Curriculum

The SYCL Academy curriculum is divided up into a number of short lessons
consisting of slides for presenting the material and a more detailed write-up,
each accompanied by a tutorial for getting hands on experience with the subject
matter.

Each of the lessons are designed to be self contained modules in order to
support both academic and training style teaching environments.

| Lesson | Title | Slides | Exercise | Source | Solution | DPC++ | AdaptiveCpp |
|--------|-------|--------|----------|--------|----------|-------|---------|
| 01 | What is SYCL | [slides][lesson-1-slides] | [exercise][lesson-1-exercise] | [source][lesson-1-source] | [solution][lesson-1-solution] | Yes | Yes |
| 14 | ND Range Kernels | [slides][lesson-14-slides] | [exercise][lesson-14-exercise] | [source][lesson-14-source] | [solution][lesson-14-solution] | Yes | Yes |
| 20 | oneMKL GEMM | [slides][lesson-20-slides] | [exercise][lesson-20-exercise] | [source][lesson-20-source] | [solution][lesson-20-solution] | Yes | Yes |

## Working on the Exercises on Intel Developer Cloud

During the tutorial at ISC24 we will use the Intel Developer Cloud environment to run through the hands on exercises. You can set up the Developer Cloud account by following the instructions in the next section.
Note that exercises can be built for DPC++ and AdaptiveCpp(requires [installation][adaptivecpp-installing]).

### Connect to Intel Developer Cloud via JupyterLab

* Start by creating an [Intel Developer Cloud][intel-devcloud] account if you do not already have one and login in.
* Go to [training](https://console.cloud.intel.com/training) and click on ```Launch JupyterLab´´´
* In the ```Jupiter Notebook``` select *File->New->Terminal*

You are now ready to start with the first [lesson][lesson-1-slides]. Enjoy !

### Building the Exercises with Intel oneAPI DPC++/C++ Compiler

* Execute the following command to download SYCL Academy project (if not already done):
```sh
git clone --recursive --branch isc24 https://github.com/codeplaysoftware/syclacademy.git

```
* To create the code_exercises directory structure with the Makefiles:
```sh
cd syclacademy
mkdir build
cd build
cmake ../ "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=ON -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
```

### Working on the Exercises
Once you have a working SYCL compiler, you are ready to start writing some SYCL code. To find the first exercise:
```
cd Code_Exercises/Compiling_with_SYCL/
```
And read the `README.md` for further instructions.

Each exercise directory contains:
* ```README.md```, which contains instructions of how to complete a given exercise, as well as directions for compilation.
* ```source.cpp```, a placeholder file where your code implementation should be written.
* ```solution.cpp```, where a solution has been implemented in advance.

Once you have completed any given exercise make sure to compare your implementation against the corresponding ```solution.cpp```.

## Working on the Exercises on Your Own HW
### Supported Platforms

Below is a list of the supported platforms and devices for each SYCL implementations,
please check this before deciding which SYCL implementation to use.
Make sure to also install the specified version to ensure that you can build
all of the exercises.

| Implementation | Supported Platforms | Supported Devices | Required Version |
|----------------|---------------------|-------------------|------------------|
| DPC++ | [Intel Developer Cloud](#connect-to-intel-developer-cloud-via-jupyterlab) <br> Ubuntu 22.04<br> Red Hat Enterprise Linux 9.2<br> Microsoft Windows 10, 11 Visual Studio 2019/2022 (64bit)  <br> Refer to [System Requirements][oneAPI-system-requirements] for more details | Intel CPU (OpenCL) <br> Intel GPU (OpenCL, Level Zero) <br> Intel FPGA (OpenCL) <br> Nvidia GPU (CUDA)* <br> AMD GPU (HIP)* | 2024.1	|
| AdaptiveCpp | Any Linux | CPU (OpenMP) <br> AMD GPU (ROCm)*** <br> NVIDIA GPU (CUDA)<br> Intel GPU (Level Zero)<br> Intel CPU, GPU (OpenCL) | 23.10.0 from Nov 1, 2023 or newer |

\* Supported in [open source project][intel-llvm] or requires [Codeplay oneAPI Plugins for NVIDIA & AMD][codeplay-oneapi-plugins]

\*\* See [here][rocm-gpus] for the official list of GPUs supported by AMD for
ROCm. We do not recommend using GPUs earlier than gfx9 (Vega 10 and Vega 20
chips).

### Install SYCL implementations

First you'll need to install your chosen SYCL implementation and any dependencies they require.

#### Installing DPC++

To set up DPC++ follow the [getting started instructions][dpcpp-getting-started].

You can also use a [Docker* image][docker-container-oneapi].

Note that one [Intel Developer Cloud][intel-devcloud] the latest version of DPC++ is already installed and available in the path.

#### Installing AdaptiveCpp

You will need a AdaptiveCpp (formerly hipSYCL) build from September 2021 or newer. Refer to the [AdaptiveCpp installation instructions][adaptivecpp-installing] for details on how to install AdaptiveCpp.

### Pre-requisites

Before building the exercises you'll need:

* One of the platforms in the support matrix above, depending on which SYCL implementation you are wishing to build for.
* A C++17 or above tool-chain.
* An appropriate build system for the platform you are targeting (CMake, Ninja, Make, Visual Studio).

### Configuring using CMake

Clone this repository, there are some additional dependencies configured as git sub-modules so make sure to clone those as well. Then simply invoke CMake as follows:

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

```
-DSYCL_ACADEMY_INSTALL_ROOT=<path_to_sycl_impl_install_root>
```

For `<path_to_sycl_impl_install_root>` we recommend you specify the path to the root directory of your SYCL implementation installation, though this may not always be required.

```
-DSYCL_ACADEMY_ENABLE_SOLUTIONS=ON
```

This will enable building the solutions for each exercise as well as the source files. This is disabled by default.

```
-DCMAKE_BUILD_TYPE=Release
```

The build configuration for all exercises defaults to a debug build if this option is not specified.

#### Additional cmake arguments for DPC++

```
-DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
```

This SYCL Academy CMake configuration uses the Intel oneAPI IntelSYCL CMake module package to assist it in its configuration. These command line arguments must be used to initiate this configuration correctly.

`-DSYCL_TRIPLE` can be used to specify a DPC++ compatible SYCL triple. Possible
values include:

* `amdgcn-amd-amdhsa` - For AMD devices
* `nvptx64-nvidia-cuda` - For CUDA devices
* `spir64_gen` - For Intel GPUs
* `native_cpu` - For native CPU SYCL device (dependent on DPCPP version)

`-DSYCL_ARCH` can also be used to specify a device arch. This CMake opt is
necessary for AMD. Possible values include:

* `gfx90a` - For AMD MI200
* `sm_80` - For NVIDIA A100
* `pvc` - For Intel PVC

It may also be necessary to manually specify the install location of the CUDA or
ROCM SDK, if this is found in a non-standard location. The flags:

`-DROCM_DIR` and `-DCUDA_DIR` can be used to specify the install dir of the ROCM
or CUDA SDKs, respectively.

##### DPC++ for AMD CMake example

```
  cmake .. -GNinja -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=ON -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx _DSYCL_TRIPLE=amdgcn-amd-amdhsa -DSYCL_ARCH=gfx90a -DROCM_DIR=/opt/rocm/5.4.3
```

##### DPC++ for CUDA CMake example

```
  cmake .. -GNinja -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=ON -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx _DSYCL_TRIPLE=nvptx64-nvidia-cuda -DSYCL_ARCH=sm_61 -DCUDA_DIR=/usr/local/cuda/11.2/
```

#### Additional cmake arguments for AdaptiveCpp

Sufficiently new (>= 24.02.0), full installations of AdaptiveCpp do not require specifying compilation targets.
In this case, targets may still be provided optionally. 

For older AdaptiveCpp versions, CMake will require you to specify the compilation targets using `-DACPP_TARGETS=<target specification>`. 

`<target specification>` is a list of compilation flows to enable and devices to target, for example
`-DACPP_TARGETS="omp;generic"` compiles for CPUs using OpenMP and GPUs using the generic single-pass compiler.

If your AdaptiveCpp installation does not force a compilation target to be provided, but it was built with the generic single-pass compiler disabled (it is enabled by default in all AdaptiveCpp installations built against LLVM >= 14), it is compiling for a default set of targets provided at installation time. If you cannot run the binary on the hardware of your choice, this default set may not be the right one for your hardware and you may have to specify the right targets explicitly.

Available compilation flows are:
* `omp` - OpenMP CPU backend
* `generic` - Generic single-pass compiler. Generates a binary that runs on host CPU, AMD, NVIDIA and Intel GPUs using runtime compilation
* `cuda` - CUDA backend for NVIDIA GPUs. Requires specification of targets of the form sm_XY, e.g. sm_70 for Volta, sm_60 for Pascal. E.g: `cuda:sm_70`.
* `hip`  - HIP backend for AMD GPUs. Requires specification of targets of the form gfxXYZ, e.g. gfx906 for Vega 20, gfx900 for Vega 10. E.g.: `hip:gfx906`.

When in doubt, use `-DACPP_TARGETS=generic` as it compiles the fastest, usually generates the fastest binaries, and generates portable binaries.

#### CMake usage example

Invoking CMake from the command line example usage:
```
  cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=ON -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
```

### Getting started with compiling DPC++

First you have to ensure that your environment is configured to use DPC++ (note
if you are using the Intel Developer Cloud then you don't need to do this step).

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


[dpcpp-getting-started]: https://software.intel.com/content/www/us/en/develop/articles/installation-guide-for-intel-oneapi-toolkits.html
[intel-devcloud]: https://console.cloud.intel.com/training
[docker-container-oneapi]: https://github.com/intel/oneapi-containers
[oneAPI-system-requirements]: https://software.intel.com/content/www/us/en/develop/articles/intel-oneapi-base-toolkit-system-requirements.html

[adaptivecpp-installing]: https://github.com/AdaptiveCpp/AdaptiveCpp/blob/develop/doc/installing.md
[rocm-gpus]: https://github.com/RadeonOpenCompute/ROCm#supported-gpus
[codeplay-oneapi-plugins]: https://codeplay.com/solutions/oneapi/plugins/
[intel-llvm]: https://github.com/intel/llvm
[spack]: https://github.com/spack/spack

[video-playlist]: https://youtube.com/playlist?list=PLCssnq0MpRdM-IUAYtNSPYck6u3oz7OZQ

[lesson-1-slides]: ./Lesson_Materials/What_is_SYCL/
[lesson-1-exercise]: ./Code_Exercises/What_is_SYCL/README.md
[lesson-1-source]:   ./Code_Exercises/What_is_SYCL/source.cpp
[lesson-1-solution]: ./Code_Exercises/What_is_SYCL/solution.cpp

[lesson-14-slides]: ./Lesson_Materials/ND_Range_Kernel/
[lesson-14-exercise]: ./Code_Exercises/ND_Range_Kernel/README.md
[lesson-14-source]:   ./Code_Exercises/ND_Range_Kernel/source.cpp
[lesson-14-solution]: ./Code_Exercises/ND_Range_Kernel/solution.cpp

[lesson-20-slides]: ./Lesson_Materials/OneMKL_gemm/
[lesson-20-exercise]: ./Code_Exercises/OneMKL_gemm/README.md
[lesson-20-source]:   ./Code_Exercises/OneMKL_gemm/source.cpp
[lesson-20-solution]: ./Code_Exercises/OneMKL_gemm/solution.cpp