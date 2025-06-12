# SYCL Academy @ ISC25

![SYCL Academy](sycl_academy_black.png#gh-light-mode-only "SYCL Academy")
![SYCL Academy](sycl_academy_white.png#gh-dark-mode-only "SYCL Academy")

This repository provides materials that can be used for teaching SYCL. The
materials are provided using the "Creative Commons Attribution Share Alike 4.0
International" license.

This specific branch of SYCL Academy is being used for ISC25 and contains a subset
of the materials available in the main branch.

To clone this repository locally, use the following command:

`git clone --branch isc25 https://github.com/codeplaysoftware/syclacademy.git`

You can open the presentations by opening the index.html file in each folder under the "Lesson_Materials" folder.

## Lesson Curriculum

The SYCL Academy curriculum is divided up into a number of short lessons
consisting of slides for presenting the material and a more detailed write-up,
each accompanied by a tutorial for getting hands on experience with the subject
matter. The code is available in both the repository and as a Compiler Explorer link.

| Lesson | Title | Slides | Exercise | Repository | Compiler Explorer Source |
|--------|-------|--------|----------|------------|------------------|
| 01 | A Fast Introduction to SYCL | [slides][lesson-1-slides] | [exercise][lesson-1-exercise] | [source][lesson-1-CEsource]  |
| 02 | ND Range Kernels and Concepts | [slides][lesson-2-slides] | [exercise][lesson-2-exercise] | [source][lesson-2-CEsource] |
| 03 | Data Flow with SYCL | [slides][lesson-3-slides] | [exercise][lesson-3-exercise] | [source][lesson-3-CEsource] |
| 04 | Recap and Further Learning | [slides][lesson-4-slides] | NA | NA |

If you really need to look at the solutions for the exercises go to [this page][isc25-solutions].

[lesson-1-slides]: ./Lesson_Materials/Fast_Track/
[lesson-1-exercise]: ./Code_Exercises/Asynchronous_Execution/README.md
[lesson-1-source]:   ./Code_Exercises/Asynchronous_Execution/source.cpp
[lesson-1-CEsource]: https://godbolt.org/z/Mxb5zj6zW

[lesson-2-slides]: ./Lesson_Materials/Data_Parallelism/
[lesson-2-exercise]: ./Code_Exercises/Data_Parallelism/README.md
[lesson-2-source]:   ./Code_Exercises/Data_Parallelism/source.cpp
[lesson-2-CEsource]: https://godbolt.org/z/rWEee49rP

[lesson-3-slides]: ./Lesson_Materials/Data_and_Dependencies/
[lesson-3-exercise]: ./Code_Exercises/Data_and_Dependencies/README.md
[lesson-3-source]:   ./Code_Exercises/Data_and_Dependencies/source.cpp
[lesson-3-CEsource]: https://godbolt.org/z/ajErrMccv

[lesson-4-slides]: ./Lesson_Materials/Recap_and_Further_Learning/
[isc25-solutions]: ./Solutions/solutions.md