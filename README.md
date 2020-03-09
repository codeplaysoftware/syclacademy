# SYCL Academy

![SYCL Academy](sycl_academy.png "SYCL Academy")

This repository provides materials that can be used for teaching SYCL. The materials are provided using the "Creative Commons Attribution Share Alike 4.0 International" license.

Don't know what SYCL is?

*  Read a description of SYCL on the [Khronos website SYCL page](https://www.khronos.org/sycl/)
*  Go to the Khronos website to find [a list of SYCL resources](https://www.khronos.org/sycl/resources)
*  Browse SYCL news, videos, projects and more on the [sycl.tech community website](https://sycl.tech/)
*  Get a list of the [available SYCL implementations](https://sycl.tech/#get-sycl)

## Contributing to SYCL Academy

Contributions to the materials are very gratefully received and this can be done by submitting a Pull Request with any changes. Please limit the scope of each Pull Request so that they can be reviewed and merged in a timely manner.

## Supporting Organizations

Abertay University, Heriot Watt University, University of Edinburgh, TU Dresden, University of the West of Scotland, Universitat Innsbruck, Universidad de Concepcion and University of Salerno.

## Lesson Curriculum

The SYCL Academy curriculum is divided up into a number of short lessons consisting of slides for presenting the material and a more detailed write-up,
each accompanied by a tutorial for getting hands on experience with the subject matter.

Each of the lessons are designed to be self contained modules in order to support both academic and training style teaching environments.

| Lesson | Description | Slides | Write-up | Tutorial | Source | Solution |
|--------|-------------|--------|----------|----------|--------|----------|
| Introduction to SYCL | Introduction to SYCL and how it can be used for parallel programming. | [slides][lesson-1-slides] (30min) | TODO | [tutorial][lesson-1-tutorial] | NA | NA |
| Creating a SYCL Queue | How to query the SYCL device topology and create a queue. | TODO | TODO | [tutorial][lesson-2-tutorial] | [source][lesson-2-source] | [solution][lesson-2-solution] |
| Launching SYCL Kernels | How to enqueue kernels using SYCL. | [slides][lesson-3-slides] (45min) | TODO | [tutorial][lesson-3-tutorial] | [source][lesson-3-source] | [solution][lesson-3-solution] |
| Managing Data in SYCL | The memory model in SYCL and how buffers and accessors are used to manage this memory. | [slides][lesson-4-slides] (60min) | TODO | [tutorial][lesson-4-tutorial] | [source][lesson-4-source] | [solution][lesson-4-solution] |
| Handling SYCL Errors | How to catch and understand errors that might be emitted by a SYCL application. | [slides][lesson-5-slides] (20min) | TODO | NA | NA | NA |

#### How to use the Materials

Simply clone this repository, then open the "index.html" file for the presentation you want to view. Your browser will have a "Full Screen" mode that can be used to run the presentation, use the right and left cursors to move forward and backward in the presentation.

## Online Interactive Tutorial

Hosted by tech.io, this [SYCL Introduction](https://tech.io/playgrounds/48226/introduction-to-sycl/introduction-to-sycl-2) tutorial introduces the concepts of SYCL. The website also provides the ability to compile and execute SYCL code from your web browser.

## Setting up Computers for SYCL

#### Machine Setup Instructions

ComputeCpp, a SYCL v1.2.1 conformant implementation by Codeplay Software provides setup instructions on [developer.codeplay.com](https://developer.codeplay.com). There is more detailed information about what hardware is supported by ComputeCpp on the [Platform Support](https://developer.codeplay.com/products/computecpp/ce/guides/platform-support) page.

Other SYCL implementations can be found on the SYCL community website [sycl.tech](https://sycl.tech).

#### Setting up a Docker Container for Lab Machines

In order to more easily deploy a SYCL implementation onto a bank of machines in a university lab for example, a Docker container can be used to deploy on these machines. This ensures all the dependencies that are needed are installed on each machine.

An example of how to set up a Docker container:

For Intel CPU or GPU
* Download the OpenCL Drivers for Intel from the [Intel website](https://software.intel.com/en-us/articles/opencl-drivers)
* Download the latest ComputeCpp release package from [developer.codeplay.com](https://developer.codeplay.com)

Now create a DockerFile that uses these packages, an example of how this might be done is below. Please note this file is not tested or maintained regularly but shows the elements that need to be installed.

```
FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install -y git
RUN apt-get install -y ninja-build
RUN apt-get install -y g++
RUN apt-get install -y python3
RUN apt-get install -y python3-pip
RUN apt-get install -y software-properties-common

RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get update

RUN python3 -m pip install cmake

# install Intel OpenCL drivers from downloaded package
RUN tar -xvf l_opencl_p_18.1.0.015.tgz
RUN cd l_opencl_p_18.1.0.015
RUN chmod +x install.sh
RUN ./install.sh

# Download the Khronos OpenCL headers
RUN git clone https://github.com/KhronosGroup/OpenCL-Headers.git
RUN mv OpenCL-Headers/CL/ /opt/khronos/opencl/include

# Set up the ICD Loader
RUN mkdir -p /etc/OpenCL/vendors/ \
    && echo "$OCL_LIB/libintelocl.so" > /etc/OpenCL/vendors/intel.icd

# Create a directory for ComputeCpp
RUN mkdir /usr/local/computecpp
RUN cd /usr/local/computecpp

# Copy the ComputeCpp release package and extract it to /usr/local/computecpp
RUN cp Ubuntu-16.04-64bit.tar.gz . 
RUN tar -xvf Ubuntu-16.04-64bit.tar.gz

# Add the ComputeCpp location to the path on the machine
ENV PATH=OCL_INC:OCL_LIB:/usr/local/computecpp/bin:/usr/local/computecpp/include:/usr/local/computecpp/lib:${PATH}

ENV CC=gcc-8
ENV CXX=g++-8
```

SYCL and the SYCL logo are trademarks of the Khronos Group Inc.

[lesson-1-slides]: ./Lesson_Materials/Lesson-1-Introduction-to-SYCL/index.html
[lesson-1-tutorial]: ./Code_Exercises/cppcon/docs/sycl_00_setting_up_computecpp.md

[lesson-2-slides]: ./Lesson_Materials/Lesson-2-Creating-a-SYCL-Queue/index.html
[lesson-2-tutorial]: ./Code_Exercises/cppcon/docs/sycl_01_configuring_a_queue.md
[lesson-2-source]: ./Code_Exercises/cppcon/source/sycl_01_configuring_a_queue.cpp
[lesson-2-solution]: ./Code_Exercises/cppcon/solutions/sycl_01_configuring_a_queue.cpp

[lesson-3-slides]: ./Lesson_Materials/Lesson-2-Launching-SYCL-Kernels/index.html
[lesson-3-tutorial]: ./Code_Exercises/cppcon/docs/sycl_02_hello_world.md
[lesson-3-source]: ./Code_Exercises/cppcon/source/sycl_02_hello_world.cpp
[lesson-3-solution]: ./Code_Exercises/cppcon/solutions/sycl_02_hello_world.cpp

[lesson-4-slides]: ./Lesson_Materials/Lesson-4-Managing-Data-in-SYCL-Applications/index.html
[lesson-4-tutorial]: ./Code_Exercises/cppcon/docs/sycl_03_vector_add.md
[lesson-4-source]: ./Code_Exercises/cppcon/source/sycl_03_vector_add.cpp
[lesson-4-solution]: ./Code_Exercises/cppcon/solutions/sycl_03_vector_add.cpp

[lesson-5-slides]: ./Lesson_Materials/Lesson-3-Handling-SYCL-Errors/index.html

