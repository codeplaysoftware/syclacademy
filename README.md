# SYCL Academy

![SYCL Academy](sycl_academy.png "SYCL Academy")

This repository provides materials that can be used for teaching SYCL. The
materials are provided using the "Creative Commons Attribution Share Alike 4.0
International" license.

## What is SYCL?

If you're not familiar with SYCL or would like some further resources for
learning about SYCL below are a list of useful resources:

*  Read a description of SYCL on the [Khronos website SYCL page](https://www.khronos.org/sycl/).
*  Go to the Khronos website to find [a list of SYCL resources](https://www.khronos.org/sycl/resources).
*  Check out the [SYCL 2020 reference guide](https://www.khronos.org/registry/SYCL/).
*  Browse SYCL news, blog posts, videos, projects and more on the [sycl.tech community website](https://sycl.tech/)
*  Get a list of the [available SYCL implementations](https://sycl.tech/#get-sycl)

### How to use the Materials

This branch contains specific materials for the NERSC Perlmutter workshop.
To use these materials simply clone this repository with the correct branch.

```
git clone --recursive --branch perlmutter-workshop https://github.com/codeplaysoftware/syclacademy.git
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

## Lesson Curriculum

The SYCL Academy curriculum is divided up into a number of short lessons
consisting of slides for presenting the material and a more detailed write-up,
each accompanied by a tutorial for getting hands on experience with the subject
matter.

Each of the lessons are designed to be self contained modules in order to
support both academic and training style teaching environments. 


| Lesson | Title | Slides | Exercise | Source | Solution | ComputeCpp | DPC++ | hipSYCL |
|--------|-------|--------|----------|--------|----------|------------|-------|---------|
| 01 | Hello SYCL | [slides][lesson-1-slides] | [exercise][lesson-1-exercise] | [source][lesson-1-source] | [solution][lesson-1-solution] | Yes | Yes | Yes |
| 02 | Enqueueing a Kernel | [slides][lesson-2-slides] | [exercise][lesson-2-exercise] | [source][lesson-2-source] | [solution][lesson-2-solution] | Yes | Yes | Yes |
| 03 | Data Parallelism | [slides][lesson-3-slides] | [exercise][lesson-3-exercise] | [source][lesson-3-source] | [solution][lesson-3-solution] | Yes | Yes | Yes |
| 04 | ND Range Kernels | [slides][lesson-4-slides] | [exercise][lesson-4-exercise] | [source][lesson-4-source] | [solution][lesson-4-solution] | Yes | Yes | Yes |
| 05 | Profiling and Debugging | [slides][lesson-5-slides] | [exercise][lesson-5-exercise] | [source][lesson-5-source] | [solution][lesson-5-solution] | Yes | Yes | Yes |

### Compiling directly (DPC++ only)

If you are using DPC++ there is no CMake integration, but it is very simple to
use the DPC++ compiler directly.

`clang++ -fsycl -fsycl-targets=nvptx64-nvidia-cuda source.cpp`

## Working on the Exercises
Once you have a working SYCL compiler, you are ready to start writing some SYCL code. To find the first exercise:
```
cd Code_Exercises/Exercise_01_Compiling_with_SYCL/
```
And read the README.md for further instructions. 

Each exercise directory contains:
* ```README.md```, which contains instructions of how to complete a given exercise, as well as directions for compilation.
* ```source.cpp```, where a you should implement your solution.

Code solutions can be found in `Code_exercises/solutions`

Once you have completed any given exercise make sure to compare your implementation against the corresponding ```ex${i}_solution.cpp```. 

## Online Interactive Tutorial

Hosted by tech.io, this [SYCL Introduction](https://tech.io/playgrounds/48226/introduction-to-sycl/introduction-to-sycl-2) tutorial introduces the concepts of SYCL. The website also provides the ability to compile and execute SYCL code from your web browser.

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

[lesson-1-slides]: ./Lesson_Materials/Lecture_01_What_is_SYCL_and_DPC++/
[lesson-1-exercise]: ./Code_Exercises/Exercise_01_Hello_SYCL/README.md
[lesson-1-source]: ./Code_Exercises/Exercise_01_Hello_SYCL/source.cpp
[lesson-1-solution]: ./Code_Exercises/solutions/ex1_solution.cpp

[lesson-2-slides]: ./Lesson_Materials/Lecture_02_Enqueueing_a_Kernel/
[lesson-2-exercise]: ./Code_Exercises/Exercise_02_First_Kernel/README.md
[lesson-2-source]: ./Code_Exercises/Exercise_02_First_Kernel/source.cpp
[lesson-2-solution]: ./Code_Exercises/solutions/ex2_solution.cpp

[lesson-3-slides]: ./Lesson_Materials/Lecture_03_Data_Parallelism/
[lesson-3-exercise]: ./Code_Exercises/Exercise_03_Vector_Add/README.md
[lesson-3-source]: ./Code_Exercises/Exercise_03_Vector_Add/source.cpp
[lesson-3-solution]: ./Code_Exercises/solutions/ex3_solution.cpp

[lesson-4-slides]: ./Lesson_Materials/Lecture_04_ND_Range_Kernel/
[lesson-4-exercise]: ./Code_Exercises/Exercise_04_ND_Range_Kernel/README.md
[lesson-4-source]: ./Code_Exercises/Exercise_04_ND_Range_Kernel/source.cpp
[lesson-4-solution]: ./Code_Exercises/solutions/ex4_solution.cpp

[lesson-5-slides]: ./Lesson_Materials/Lecture_05_Profiling_and_Debugging/
[lesson-5-exercise]: ./Code_Exercises/Exercise_05_Profiling/README.md
[lesson-5-source]: ./Code_Exercises/Exercise_05_Profiling/source.cpp
[lesson-5-solution]: ./Code_Exercises/solutions/ex5_solution.cpp

