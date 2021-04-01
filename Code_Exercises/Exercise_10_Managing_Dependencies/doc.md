# SYCL Academy

## Exercise 10: Managing Dependencies
---

In this exercise you will learn how to create a data dependency data flow graph
in both the buffer/accessor and USM models.

---

### 1.) Define a data flow graph with the buffer/accessor model

Using everything you have learned in previous exercises create an application
using the buffer/accessor model which has four kernel functions. These kernel
functions can do any computation you like, but they should follow the following
dependencies.

          (kernel A)
         /          \
    (kernel B)  (kernel C)
         \          /
          (kernel D)

The important thing here is that kernels B and C must depend on kernel A, kernel
D must depend on kernels B and C and kernels B and C can be executed in any
order and even concurrently if the device permits. Note that in the
buffer/accessor these dependencies are created implicitly using the creation of
`accessor`s.

Feel free to use any method of synchronization and copy back you like, but
remember to handle errors.

### 2.) Define a data flow graph with the buffer/accessor model

Now do the same again but using the USM model. Note that in the USM model
dependencies are defined explicitly by chaining commands via `event`s.

Again feel free to use any method of synchronization and copy back you like,
but remember to handle errors.

## Build and execution hints

```
cmake -DSYCL_ACADEMY_USE_COMPUTECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/computecpp ..
make managing_dependencies_source
./Code_Exercises/Exercise_10_Managing_Dependencies/managing_dependencies_source
```
