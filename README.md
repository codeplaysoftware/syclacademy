# Teaching SYCL

This repository provides materials that can be used for teaching SYCL.

## Lesson Materials

#### An Introduction to SYCL

A presentation deck introducing SYCL, and how it can be used for parallel programming.

Recommended duration of talk: 30 minutes

#### Launching SYCL Kernels

A presentation deck explaining how to develop kernels using SYCL

Recommended duration of talk: 45 minutes

#### Handling SYCL Errors

A presentation deck explaining how to catch and understand errors that might be emitted by a SYCL application

Recommended duration of talk: 20 minutes

#### Managing Data in SYCL

A presentation deck explaining the memory model in SYCL and how buffers and accessors are used to maange this memory.

Recommended duration of talk: 60 minutes

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
* Download the OpenCL SDK for Intel from the [Intel website](https://software.intel.com/en-us/opencl-sdk)

* Download the latest ComputeCpp release package from [developer.codeplay.com](https://developer.codeplay.com)
* Get the OpenCL header files from the [Khronos GitHub repo](https://github.com/KhronosGroup/OpenCL-Headers)

Now create a DockerFile that uses these packages, an example of how this might be done is below:

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

RUN apt-get install -y g++-8

RUN python3 -m pip install cmake

# install Intel OpenCL drivers from downloaded package
RUN tar -xvf intelopenclsdk.tar.gz
RUN ./setup.sh

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
