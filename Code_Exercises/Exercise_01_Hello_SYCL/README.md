# Exercise 1

The purpose of this exercise is to compile some SYCL code.

Write a simple code using the examples in `source.cpp` and compile with
```
clang++ -fsycl -fsycl-targets=nvptx64-nvidia-cuda source.cpp
```

Try to run the code on different devices using 
```
SYCL_DEVICE_FILTER=cuda ./a.out
```

Use the quick reference guide in `source.cpp` to output the device name
to `stdout`.

Extra fields may also be outputted using `get_info()`.

Try:

`sycl::info::device::version`
`sycl::info::device::driver_version`

