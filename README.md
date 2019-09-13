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

Now create a DockerFile that uses these packages.
```
FROM ubuntu:18.04

MAINTAINER John <insertyour@email.address>

RUN apt-get update && apt-get install -y apache2 && apt-get clean && rm -rf /var/lib/apt/lists/*ENV APACHE_RUN_USER  www-data

ENV APACHE_RUN_GROUP www-data
ENV APACHE_LOG_DIR   /var/log/apache2
ENV APACHE_PID_FILE  /var/run/apache2/apache2.pid
ENV APACHE_RUN_DIR   /var/run/apache2
ENV APACHE_LOCK_DIR  /var/lock/apache2
ENV APACHE_LOG_DIR   /var/log/apache2RUN mkdir -p $APACHE_RUN_DIR
RUN mkdir -p $APACHE_LOCK_DIR
RUN mkdir -p $APACHE_LOG_DIRCOPY index.html /var/www/htmlEXPOSE 80CMD ["/usr/sbin/apache2", "-D", "FOREGROUND"]
```