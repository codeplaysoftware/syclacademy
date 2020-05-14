# SYCL Academy

### Exercise 1: Getting Started

---

For this exercise we will make some assumptions that either:

* You have followed the pre-tutorial instructions to set up a SYCL compiler of
your choice on your own machine
or
* You will use the Intel DevCloud environment for compiling and executing the
SYCL applications used in the tutorial

In this exercise you will learn:
* How to validate your SYCL environment
* How to create and compile a SYCL application using your chosen SYCL compiler.

---

#### Setting Up Intel DevCloud

If you have set up a SYCL compiler on your own machine you can skip this section

**Access Intel DevCloud**

If you have not already done so, go to the 
[Intel DevCloud oneAPI DevCloud Form](https://intelsoftwaresites.secure.force.com/devcloud/oneapi)

Complete your details and submit the form to gain access to the Intel DevCloud.

Select the "Connnect" option in the top navigation.
You can now use JupyterLab for one-click login, and selecting a "terminal" gives
you command line access to the machine.
There are other ways to connect if you prefer them, for example SSH.

#### Validating your environment

##### For DPC++ (using the Intel DevCloud)

The easiest way to check everything is set up as expected is to compile and run
some code.

Run the following command and follow the instructions and terminal output:

```
/data/oneapi/welcome_dpcpp.sh
```

Assuming there are no errors we can assume that your environment is set up correctly.

##### For ComputeCpp

ComputeCpp includes a utility called "computecpp_info" which lists all the
devices on your machine and outputs which are setup with the correct drivers. 
Open a console and run the executable located in the 'bin' folder of the
ComputeCpp release package:

```
./computecpp_info
```

Look for the lines that say:
```
  Device is supported                     : YES - Tested internally by Codeplay
  Software Ltd.
```

You can also add the option --verbose to display further information about the
devices.

From this output you can confirm your environment is setup correctly.

##### For hipSYCL

You will need to have followed the compilation instructions from the hipSYCL
README file to confirm your setup is working.


#### Compile a SYCL application

Once you have confirmed your environment is setup and available you are ready to
compile your first SYCL application from source code.

First fetch the tutorial samples from GitHub.

Clone this repository ensuring that you include sub-modules.

```
git clone --recursive https://github.com/codeplaysoftware/syclacademy.git
```

```
cd syclacademy
mkdir build
cd build
```

For For DPC++ (using the Intel DevCloud):
```
dpcpp -o sycl-test ../Code_Exercises/Exercise_1_Getting_Started/hello_world.cpp
```

On the Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only available through the job queue.
Please refer to the [example][devcloud-job-submission].

Wrap the binary into a script `job_submission` and run:

`qsub job_submission`

For ComputeCpp:
```
cmake -DSYCL_ACADEMY_USE_COMPUTECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/computecpp ..
make Sample_hello_world
./Code_Exercises/Exercise_1_Getting_Started/Sample_hello_world
```

For hipSYCL:
```
# Add -DHIPSYCL_GPU_ARCH=<arch> to the cmake arguments when compiling for GPUs.
# <arch> is e.g. sm_60 for NVIDIA Pascal GPUs, gfx900 for AMD Vega 56/64, and gfx906 for Radeon VII.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_PLATFORM=<cpu|cuda|rocm> ..
make Sample_hello_world
./Code_Exercises/Exercise_1_Getting_Started/Sample_hello_world
```
alternatively, without cmake:
```
cd Code_Exercises/Exercise_1_Getting_Started
HIPSYCL_PLATFORM=<cpu|cuda|rocm> HIPSYCL_GPU_ARCH=<arch-when-compiling-for-gpu> /path/to/hipsycl/bin/syclcc -o sycl-ex-1 -I../../External/Catch2/single_include source.cpp
./sycl-ex-1
```

If you saw the following message:

```
Hello, World!
```

Then you have completed this first exercise.

*When using hipSYCL:* Note that printing from kernels in ROCm requires a very new software stack and is still experimental, so on hipSYCL you might get an empty output when compiling for AMD GPUs. In this case, try using the CPU backend.
