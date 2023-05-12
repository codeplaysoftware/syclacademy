# SYCL Academy

![SYCL Academy](sycl_academy.png "SYCL Academy")

This repository provides materials that can be used for teaching SYCL. The
materials are provided using the "Creative Commons Attribution Share Alike 4.0
International" license.

### How to use the Materials

This branch of SYCL Academy has been made for the SYCL Tutorial at ISC22.
Please ensure you are using the correct branch if you are working on the 
tutorial.

```
git clone --branch isc23 --recursive https://github.com/codeplaysoftware/syclacademy.git
```

The lectures are written in reveal.js, and can be found in `Lesson_Materials`,
in the sub-directory for each topic. To view them simply open the `index.html`
file in your browser. 

The exercises can be found in `Code_Exercises` in the sub-directory for each
topic. Each exercise has a markdown document instructing what to do in the
exercise, a source file to start with and a solution file to provide an
example implementation to compare against.

## Lesson Curriculum

| Lesson | Title | Slides | Exercise | Source | Solution |
|--------|-------|--------|----------|--------|----------|
| 01 | What is SYCL | [slides][lesson-1-slides] | [exercise][lesson-1-exercise] | [source][lesson-1-source] | [solution][lesson-1-solution] |
| 02 | Enqueueing a Kernel | [slides][lesson-2-slides] | [exercise][lesson-2-exercise] | [source][lesson-2-source] | [solution][lesson-2-solution] |
| 03 | Managing Data | [slides][lesson-3-slides] | [exercise][lesson-3-exercise] | [source][lesson-3-source] | [solution][lesson-3-solution] |
| 04 | ND Range Kernels | [slides][lesson-4-slides] | [exercise][lesson-4-exercise] | [source][lesson-4-source] | [solution][lesson-4-solution] |
| 05 | Image Convolution | [slides][lesson-5-slides] | [exercise][lesson-5-exercise] | [source][lesson-5-source] | [solution][lesson-5-solution] |

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

## Working on the Exercises
Once you have a working SYCL compiler, you are ready to start writing some SYCL code. To find the first exercise:
```
cd Code_Exercises/Exercise_01_Compiling_with_SYCL/
```
And read the README.md for further instructions. 

Each exercise directory contains:
* ```README.md```, which contains instructions of how to complete a given exercise, as well as directions for compilation.
* ```source.cpp```, a placeholder file where your code implementation should be written. 
* ```solution.cpp```, where a solution has been implemented in advance. 

Once you have completed any given exercise make sure to compare your implementation against the corresponding ```solution.cpp```. 

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

## Online Interactive Tutorial

Hosted by tech.io, this [SYCL Introduction](https://tech.io/playgrounds/48226/introduction-to-sycl/introduction-to-sycl-2) tutorial introduces the concepts of SYCL. The website also provides the ability to compile and execute SYCL code from your web browser.



SYCL and the SYCL logo are trademarks of the Khronos Group Inc.

[video-playlist]: https://youtube.com/playlist?list=PLCssnq0MpRdM-IUAYtNSPYck6u3oz7OZQ

[lesson-1-slides]: ./Lesson_Materials/Lecture_01_What_is_SYCL/
[lesson-1-exercise]: ./Code_Exercises/Exercise_01_Compiling_with_SYCL/README.md
[lesson-1-source]: ./Code_Exercises/Exercise_01_Compiling_with_SYCL/source.cpp
[lesson-1-solution]: ./Code_Exercises/Exercise_01_Compiling_with_SYCL/solution.cpp

[lesson-2-slides]: ./Lesson_Materials/Lecture_02_Enqueuing_a_Kernel/
[lesson-2-exercise]: ./Code_Exercises/Exercise_02_Hello_World/README.md
[lesson-2-source]: ./Code_Exercises/Exercise_02_Hello_World/source.cpp
[lesson-2-solution]: ./Code_Exercises/Exercise_02_Hello_World/solution.cpp

[lesson-3-slides]: ./Lesson_Materials/Lecture_03_Managing_Data/
[lesson-3-exercise]: ./Code_Exercises/Exercise_03_Scalar_Add/README.md
[lesson-3-source]: ./Code_Exercises/Exercise_03_Scalar_Add/source.cpp
[lesson-3-solution]: ./Code_Exercises/Exercise_03_Scalar_Add/solution.cpp

[lesson-4-slides]: ./Lesson_Materials/Lecture_04_ND_Range_Kernel/
[lesson-4-exercise]: ./Code_Exercises/Exercise_04_ND_Range_Kernel/README.md
[lesson-4-source]: ./Code_Exercises/Exercise_04_ND_Range_Kernel/source.cpp
[lesson-4-solution]: ./Code_Exercises/Exercise_04_ND_Range_Kernel/solution.cpp

[lesson-5-slides]: ./Lesson_Materials/Lecture_05_Image_Convolution/
[lesson-5-exercise]: ./Code_Exercises/Exercise_05_Image_Convolution/README.md
[lesson-5-source]: ./Code_Exercises/Exercise_05_Image_Convolution/source.cpp
[lesson-5-solution]: ./Code_Exercises/Exercise_05_Image_Convolution/reference.cpp

[DevCloud-getting-started]: ./Code_Exercises/Getting_started_with_Intel_DevCloud.pdf