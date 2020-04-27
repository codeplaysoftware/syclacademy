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
./sycl-test
```

For ComputeCpp:
```
cmake -DSYCL_ACADEMY_USE_COMPUTECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/computecpp ..
make Sample_hello_world
./Code_Exercises/Exercise_1_Getting_Started/Sample_hello_world
```

For hipSYCL:
```
cmake -SYCL_ACADEMY_USE_HIPSYCL=ON ..
make Sample_hello_world
./Code_Exercises/Exercise_1_Getting_Started/Sample_hello_world
```

If you saw the following message:

```
Hello, World!
```

Then you have completed this first exercise.
