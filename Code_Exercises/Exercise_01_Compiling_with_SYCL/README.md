# SYCL Academy

## Exercise 1: Compiling with SYCL

---

For this first exercise you simply need to register and log in to the DevCloud 
environment. We would recommend accessing the DevCloud through the Jupyter terminal.
To access this go to [this page](https://devcloud.intel.com/oneapi/get_started/) 
and scroll right to the bottom where there is a link "Connect with Jupyter* Lab."
Once opened, which may take a little time, use the "File->New->Terminal" option to 
open a console.

### 2.) Verifying your environment

Depending on the SYCL implementation used, the steps to verify your environment might vary.

#### DPC++

```
sycl-ls
```

This will show you the devices that are available to you on the system.

#### ComputeCpp

To use ComputeCpp you will need to load the module.

`module use /data/oneapi_workshop/xpublog/cppcon/Modules/modulefiles`
`module load computeCPP`

```
computecpp_info
```

Unload the module again if you want to use DPC++ using `unload computeCpp`

This will show you the devices that are available to you on the system.

#### hipSYCL

To use hipSYCL you will need to load the module.

`module use /data/oneapi_workshop/xpublog/cppcon/Modules/modulefiles`
`module load hipSYCL`

Unload the module again if you want to use DPC++ using `unload hipSYCL`

### 3.) Configuring the exercise project

Once you have confirmed your environment is setup and available you are ready to
compile your first SYCL application from source code.

First fetch the tutorial samples from GitHub.

Clone this repository ensuring that you include sub-modules and the "isc22" branch.

```
git clone --recursive --branch isc22 https://github.com/codeplaysoftware/syclacademy.git
mkdir build
cd build
```

### 4.) Include the SYCL header file

Then open the source file for this exercise and include the SYCL header file
`"CL/sycl.hpp"`.

Make sure before you do this you define `SYCL_LANGUAGE_VERSION` to `2020`, to
enable support for the SYCL 2020 interface.

Once that is done build your source file with your chosen build system.

### 5.) Compile and run

Once you've done that simply build the exercise with your chosen build system
and invoke the executable.


#### Build And Execution Hints Using the DevCloud

For For DPC++:
```sh
dpcpp -fsycl -o sycl-ex-1 ../Code_Exercises/Exercise_01_Compiling_with_SYCL/source.cpp
```
In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only abvailable through the job queue.

We have provided a ready made script in the same directory as the source.cpp file, so you can call:

```sh
qsub -l nodes=1:gpu:ppn=2 -d . run.sh
```

For ComputeCpp:

```sh
cmake -DSYCL_ACADEMY_USE_COMPUTECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/computecpp ..
make exercise_01_compiling_with_sycl_source
./Code_Exercises/Exercise_01_Compiling_with_SYCL/exercise_01_compiling_with_sycl_source
```


For hipSYCL:

```sh
syclcc -o sycl-ex-1 --hipsycl-targets="spirv" ../Code_Exercises/Exercise_01_Compiling_with_SYCL/source.cpp
qsub -l nodes=1:gpu:ppn=2 -d . run.sh
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
