# SYCL Academy @ ISC25

![SYCL Academy](sycl_academy_black.png#gh-light-mode-only "SYCL Academy")
![SYCL Academy](sycl_academy_white.png#gh-dark-mode-only "SYCL Academy")

This repository provides materials that can be used for teaching SYCL. The
materials are provided using the "Creative Commons Attribution Share Alike 4.0
International" license.

This specific branch of SYCL Academy is being used for ISC25 and contains a subset 
of the materials available in the main branch.

## Lesson Curriculum

The SYCL Academy curriculum is divided up into a number of short lessons
consisting of slides for presenting the material and a more detailed write-up,
each accompanied by a tutorial for getting hands on experience with the subject
matter.

| Lesson | Title | Slides | Exercise | Source | Solution |
|--------|-------|--------|----------|--------|----------|
https://github.com/codeplaysoftware/syclacademy/tree/main/Lesson_Materials/Fast_Track
https://github.com/codeplaysoftware/syclacademy/blob/main/Code_Exercises/Asynchronous_Execution/README.md

https://github.com/codeplaysoftware/syclacademy/tree/main/Lesson_Materials/Data_Parallelism
https://github.com/codeplaysoftware/syclacademy/blob/main/Code_Exercises/Data_Parallelism/README.md

https://github.com/codeplaysoftware/syclacademy/tree/main/Lesson_Materials/Data_and_Dependencies
https://github.com/codeplaysoftware/syclacademy/blob/main/Code_Exercises/Data_and_Dependencies/

Recap

| 01 | A Fast Introduction to SYCL | [slides][lesson-1-slides] | [exercise][lesson-1-exercise] | [source][lesson-1-source] | [solution][lesson-1-solution] |
| 02 | ND Range Kernels and Concepts | [slides][lesson-2-slides] | [exercise][lesson-2-exercise] | [source][lesson-2-source] | [solution][lesson-2-solution] |
| 03 | Data Flow with SYCL | [slides][lesson-3-slides] | [exercise][lesson-3-exercise] | [source][lesson-3-source] | [solution][lesson-3-solution] |
| 04 | Recap and Further Learning | [slides][lesson-4-slides] | NA | NA | NA |

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

```
-DSYCL_ACADEMY_INSTALL_ROOT=<path_to_sycl_impl_install_root>
```

For `<path_to_sycl_impl_install_root>` we recommend you specify the path to the
root directory of your SYCL implementation installation, though this may not
always be required.

```
-DSYCL_ACADEMY_ENABLE_SOLUTIONS=ON
```

This will enable building the solutions for each exercise as well as the source
files. This is disabled by default.

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

`icpx -fsycl -o a.out source.cpp`

Where `<syclacademy_root>` is the path to the root directory of where you cloned
this repository. Note that on Windows you need to add the option /EHsc to avoid exception handling error.

The CMake configuration can also be used to build the exercises, see the section **Configuring using CMake** above.

## Working on the Exercises
Once you have a working SYCL compiler, you are ready to start writing some SYCL code. To find the first exercise:
```
cd Code_Exercises/Compiling_with_SYCL/
```
And read the README.md for further instructions.

Each exercise directory contains:
* ```README.md```, which contains instructions of how to complete a given exercise, as well as directions for compilation.
* ```source.cpp```, a placeholder file where your code implementation should be written.
* ```solution.cpp```, where a solution has been implemented in advance.

Once you have completed any given exercise make sure to compare your implementation against the corresponding ```solution.cpp```.

## Online Interactive Tutorial

Hosted by tech.io, this [SYCL Introduction](https://tech.io/playgrounds/48226/introduction-to-sycl/introduction-to-sycl-2) tutorial introduces the concepts of SYCL. The website also provides the ability to compile and execute SYCL code from your web browser.

## Connecting to DevCloud via SSH

* Start by creating an [Intel DevCloud account][intel-devcloud] account if you do not already have one and login in.
* Initialize the SSH configuration by clicking on [Automated Configuration](https://devcloud.intel.com/oneapi/documentation/connect-with-ssh-linux-macos/) and follow the instructions to setup the SSH configuration file.
* SSH into DevCloud (```ssh devcloud```)

## Connect to DevCloud via Jupyter Notebooks

* Start by creating an [Intel DevCloud account][intel-devcloud] account if you do not already have one and login in.
* Go to [training](https://console.cloud.intel.com/training) and click on ```Launch JupyterLab´´´
* In the ```Jupiter Notebook``` select *File->New->Terminal*

You are now ready to start with the first [lesson][lesson-1-slides]. Enjoy !

## Building the Exercises for DPC++

* Execute the following command to download SYCLAcademy:
```sh
git clone --recursive https://github.com/codeplaysoftware/syclacademy.git

```
* If you are using **DevCloud via ssh**, run:
 ```sh
 module load cmake
 ```

* To create the code_exercises directory structure with the Makefiles:
```sh
cd syclacademy
mkdir build
cd build
cmake ../ "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=ON -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
```


[dpcpp-getting-started]: https://software.intel.com/content/www/us/en/develop/articles/installation-guide-for-intel-oneapi-toolkits.html
[intel-devcloud]: https://consumer.intel.com/intelcorpb2c.onmicrosoft.com/B2C_1A_UnifiedLogin_SISU_CML_SAML/generic/login?entityId=www.intel.com&ui_locales=en
[docker-container-oneapi]: https://software.intel.com/content/www/us/en/develop/documentation/get-started-with-intel-oneapi-base-linux/top/using-containers.html
[oneAPI-system-requirements]: https://software.intel.com/content/www/us/en/develop/articles/intel-oneapi-base-toolkit-system-requirements.html

[adaptivecpp-installing]: https://github.com/AdaptiveCpp/AdaptiveCpp/blob/develop/doc/installing.md
[rocm-gpus]: https://github.com/RadeonOpenCompute/ROCm#supported-gpus
[spack]: https://github.com/spack/spack

[video-playlist]: https://youtube.com/playlist?list=PLCssnq0MpRdM-IUAYtNSPYck6u3oz7OZQ

[lesson-1-slides]: ./Lesson_Materials/Fast_Track/
[lesson-1-exercise]: ./Code_Exercises/Asynchronous_Execution/README.md
[lesson-1-source]:   ./Code_Exercises/Asynchronous_Execution/source.cpp
[lesson-1-solution]: ./Code_Exercises/Asynchronous_Execution/solution.cpp

[lesson-2-slides]: ./Lesson_Materials/Data_Parallelism/
[lesson-2-exercise]: ./Code_Exercises/Data_Parallelism/README.md
[lesson-2-source]:   ./Code_Exercises/Data_Parallelism/source.cpp
[lesson-2-solution]: ./Code_Exercises/Data_Parallelism/solution.cpp

[lesson-3-slides]: ./Lesson_Materials/Data_and_Dependencies/
[lesson-3-exercise]: ./Code_Exercises/Data_and_Dependencies/README.md
[lesson-3-source]:   ./Code_Exercises/Data_and_Dependencies/source.cpp
[lesson-3-solution]: ./Code_Exercises/Data_and_Dependencies/solution.cpp

[lesson-4-slides]: ./Lesson_Materials/Recap_and_Further_Learning/
