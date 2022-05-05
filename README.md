# SYCL Academy - IWOCL & SYCLcon 2022

![SYCL Academy](sycl_academy.png "SYCL Academy")

This repository provides materials that can be used for teaching SYCL. The
materials are provided using the "Creative Commons Attribution Share Alike 4.0
International" license.

These materials have been adapted for the SYCL tutorial at IWOCL and SYCLcon.
See the main branch of this repository for all the materials available.

## What is SYCL?

If you're not familiar with SYCL or would like some further resources for
learning about SYCL below are a list of useful resources:

*  Read a description of SYCL on the [Khronos website SYCL page](https://www.khronos.org/sycl/).
*  Go to the Khronos website to find [a list of SYCL resources](https://www.khronos.org/sycl/resources).
*  Check out the [SYCL 2020 reference guide](https://www.khronos.org/registry/SYCL/).
*  Browse SYCL news, blog posts, videos, projects and more on the [sycl.tech community website](https://sycl.tech/)
*  Get a list of the [available SYCL implementations](https://sycl.tech/#get-sycl)

### How to use the Materials

To use these materials simply clone this repository including the required submodules.

```
git clone --branch iwocl22 --recursive https://github.com/codeplaysoftware/syclacademy.git
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

## Lesson Curriculum for IWOCL & SYCLcon 22

The SYCL Academy curriculum is divided up into a number of short lessons
consisting of slides for presenting the material and a more detailed write-up,
each accompanied by a tutorial for getting hands on experience with the subject
matter.

Each of the lessons are designed to be self contained modules in order to
support both academic and training style teaching environments. 

| Lesson | Title | Slides | Exercise | Source | Solution | ComputeCpp | DPC++ | hipSYCL |
|--------|-------|--------|----------|--------|----------|------------|-------|---------|
| 01 | What is SYCL | [slides][lesson-1-slides] | [exercise][lesson-1-exercise] | [source][lesson-1-source] | [solution][lesson-1-solution] | Yes | Yes | Yes |
| 02 | Enqueueing a Kernel | [slides][lesson-2-slides] | [exercise][lesson-2-exercise] | [source][lesson-2-source] | [solution][lesson-2-solution] | Yes | Yes | Yes |
| 03 | Managing Data | [slides][lesson-3-slides] | [exercise][lesson-3-exercise] | [source][lesson-3-source] | [solution][lesson-3-solution] | Yes | Yes | Yes |
| 04 | ND Range Kernels | [slides][lesson-14-slides] | [exercise][lesson-14-exercise] | [source][lesson-14-source] | [solution][lesson-14-solution] | Yes | Yes | Yes |
| 05 | Image Convolution | [slides][lesson-15-slides] | [exercise][lesson-15-exercise] | [source][lesson-15-source] | [solution][lesson-15-solution] | Yes | Yes | Yes |


## Building the Exercises

The exercises can be built using the command listed in the individual exercise README.

### Supported Platforms

For simplicity, attendees of the tutorial will use the [Intel DevCloud](https://tinyurl.com/getdevcloud) 
for the exercises. Go to this url to set up your environment.

SYCL and the SYCL logo are trademarks of the Khronos Group Inc.

[computecpp-download]: https://developer.codeplay.com
[computecpp-getting-started]: https://developer.codeplay.com/products/computecpp/ce/guides/getting-started?
[dpcpp-getting-started]: https://software.intel.com/content/www/us/en/develop/articles/installation-guide-for-intel-oneapi-toolkits.html
[intel-devcloud]: https://intelsoftwaresites.secure.force.com/devcloud/oneapi
[docker-container-oneapi]: https://software.intel.com/content/www/us/en/develop/documentation/get-started-with-intel-oneapi-base-linux/top/using-containers.html
[oneAPI-system-requirements]: https://software.intel.com/content/www/us/en/develop/articles/intel-oneapi-base-toolkit-system-requirements.html

[hipsycl-installing]: https://github.com/illuhad/hipSYCL/blob/develop/doc/installing.md
[rocm-gpus]: https://github.com/RadeonOpenCompute/ROCm#supported-gpus
[spack]: https://github.com/spack/spack

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

[lesson-14-slides]: ./Lesson_Materials/Lecture_04_ND_Range_Kernel/
[lesson-14-exercise]: ./Code_Exercises/Exercise_04_ND_Range_Kernel/README.md
[lesson-14-source]: ./Code_Exercises/Exercise_04_ND_Range_Kernel/source.cpp
[lesson-14-solution]: ./Code_Exercises/Exercise_04_ND_Range_Kernel/solution.cpp

[lesson-15-slides]: ./Lesson_Materials/Lecture_05_Image_Convolution/
[lesson-15-exercise]: ./Code_Exercises/Exercise_05_Image_Convolution/README.md
[lesson-15-source]: ./Code_Exercises/Exercise_05_Image_Convolution/source.cpp
[lesson-15-solution]: ./Code_Exercises/Exercise_05_Image_Convolution/reference.cpp