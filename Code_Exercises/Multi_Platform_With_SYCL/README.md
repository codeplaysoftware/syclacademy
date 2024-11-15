# SYCL Academy

## Exercise 3: Multi-Platforms

---

In this exercise you will learn how use various devices under the platforms


Your task is to add code to the source.cpp file and implement code using the features of
sycl queue, nd_range.

There are comments and hints in the file to help you, and you can use the slides 
from the presentation too. These are in the "Lesson Materials" folder.

TIP: verify the output under `sycl-ls --verbose`

Ref: https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html#sec:platformmodel

---

### 1.) Query Platforms

- Creates a "default" platform
- Query for the info on devices listed under the platform
- Create a queue based on those devices
- Submit a "Hello World" kernel using this queue

### 2. ) Switching Platforms

- Create a platform for "CPU" type
- Query for the info on devices listed under the platform
- Create a queue based on those devices
- Submit a vector-addition kernel using this queue
- TODO: Repeat the above steps for "GPU"

#### Build And Execution Hints

For DevCloud follow these [instructions](../devcloud.md).
