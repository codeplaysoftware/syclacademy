# SYCL Academy

## Exercise 1: Compiling with SYCL (Big Helloooooo SYCL!)

---

The goal for this first exercise, is to make sure everyone is set up to compile and run C++ with SYCL programs.
If you have extra time, before the next lecture starts, please experiment a little (see two suggestions at the end of this file).

### 1.) Installing a SYCL implementation

Before you start the exercise please set yourself up with an account and access to the [DevCloud.](https://tinyurl.com/getdevcloud)

This will be used to run through the hands-on exercises and includes the DPC++ compiler that will be used 
to build your SYCL code.

### 2.) Verifying your environment

Depending on the SYCL implementation used, the steps to verify your environment might vary.

#### When using DPC++ (including on Intel Developer Cloud)

ON the Intel Developer Cloud, be sure you you are not on "head-node".  If you are using a terminal you created in a browser within a Jupyter notebook you are good.  If you accessed using ssh, you should have run "srun --pty bash" on the head node so that are no longer on a head-node.

Test with the 'sycl-ls' command.

If it fails, you may be on a head node. Please double check.
Otherwise, if it fails, you should use this command and then try sycl-ls again:
```sh
source /opt/intel/oneapi/setvars.sh
```
If it still fails, talk with an instructor please!

The sycl-ls should display something like:
```sh
[opencl:acc:0] Intel(R) FPGA Emulation Platform for OpenCL(TM), Intel(R) FPGA Emulation Device 1.2 [2023.16.7.0.21_160000]
[opencl:cpu:1] Intel(R) OpenCL, Intel(R) Xeon(R) Platinum 8480+ 3.0 [2023.16.7.0.21_160000]
[opencl:gpu:2] Intel(R) OpenCL Graphics, Intel(R) Data Center GPU Max 1100 3.0 [23.22.26516.29]
[opencl:gpu:3] Intel(R) OpenCL Graphics, Intel(R) Data Center GPU Max 1100 3.0 [23.22.26516.29]
[opencl:gpu:4] Intel(R) OpenCL Graphics, Intel(R) Data Center GPU Max 1100 3.0 [23.22.26516.29]
[opencl:gpu:5] Intel(R) OpenCL Graphics, Intel(R) Data Center GPU Max 1100 3.0 [23.22.26516.29]
[ext_oneapi_level_zero:gpu:0] Intel(R) Level-Zero, Intel(R) Data Center GPU Max 1100 1.3 [1.3.26516]
[ext_oneapi_level_zero:gpu:1] Intel(R) Level-Zero, Intel(R) Data Center GPU Max 1100 1.3 [1.3.26516]
[ext_oneapi_level_zero:gpu:2] Intel(R) Level-Zero, Intel(R) Data Center GPU Max 1100 1.3 [1.3.26516]
[ext_oneapi_level_zero:gpu:3] Intel(R) Level-Zero, Intel(R) Data Center GPU Max 1100 1.3 [1.3.26516]
```

If it is shorter, try issuing this command and trying again:
```sh
unset ONEAPI_DEVICE_SELECTOR
```

If it is still a shorter list, talk with an instructor please!

#### When using AdaptiveCpp (formerly hipSYCL)

With AdaptiveCpp (formerly hipSYCL), you can skip this step. If you suspect later that your environment might not be set up correctly, you can set the environment variable `HIPSYCL_DEBUG_LEVEL=3` and execute your program. AdaptiveCpp (formerly hipSYCL) will then print (among many other things) all devices that it can find, for example:
```sh
[hipSYCL Info] Discovered devices from backend 'OpenMP': 
[hipSYCL Info]   device 0: 
[hipSYCL Info]     vendor: the hipSYCL project
[hipSYCL Info]     name: hipSYCL OpenMP host device
```
*Note: You may not see this output in this exercise because we do not yet actually use any SYCL functionality. Consequently, there is no need for the hipSYCL runtime to launch and print diagnostic information.*

### 3.) Configuring the exercise project

Once you have confirmed your environment is setup and available you are ready to
compile your first SYCL application from source code.

First fetch the tutorial samples from GitHub.

Clone this repository ensuring that you include sub-modules.

```
git clone --recursive --branch sc23 --single-branch https://github.com/codeplaysoftware/syclacademy.git
mkdir build
cd build
```

If the clone HANGS when on Intel Developer Cloud - do the following steps:
1. exit the worker nodes: type 'exit'
2. now try the git command again (from above, remove the directory if rerunning git complains it exists - and then run git)
3. go back to a worker node: type 'srun --pty bash'
4. continue with the mkdir and cd from above, and so on

### 4.) Compile and run

Simply build the exercise with your chosen build system and invoke the executable.
If you are on Developer Cloud, you can view the image easily using the browser with JupyterLab to visit the photo (blurred_goldfish.png).

#### Build And Execution Hints

For DPC++ (using the Intel DevCloud):
```sh
cd ~/syclacademy/Code_Exercises/Exercise_01_Big_Hello_SYCL
icpx -fsycl -o sycl-ex-1 source.cpp
cp ../Images/goldfish.png  .
./sycl-ex-1 goldfish.png
```

If you get an error "Command 'icpx' not found" that means you need to first type: source /opt/intel/oneapi/setvars.sh

For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_01_big_hello_sycl
./Code_Exercises/Exercise_01_Big_Hello_SYCL/exercise_01_big_hello_sycl

```
alternatively, without cmake:
```sh
cd ~/syclacademy/Code_Exercises/Exercise_01_Big_Hello_SYCL
/path/to/hipsycl/bin/syclcc -o sycl-ex-1 --hipsycl-targets="<target specification>" source.cpp
cp ../Images/goldfish.png  .
./sycl-ex-1 goldfish.png
```


### 6.) Bonus round - two things to try if you have extra time (over achiever you!)

Two experiments to consider:

1. Change one of the program kernels to print "Hello, World". You will want to add these two lines of code (can you figure out where and make it work?):
```
auto os = sycl::stream{128, 128, cghX}; // X in chgX will depend on which kernel you add it to
cghX.single_task([=]() { os << "Hello World!\n"; });
```

2. Bonus points if you can put the Hello World print routine onto a third accelerator instead of using one of the two already being used (the code finds 4 devices (possibly not unique - but we'll discuss that later) and the code only uses 2 of them)


