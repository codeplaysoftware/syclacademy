# SYCL Academy

## Exercise 11: Use of oneMKL library
---

In this exercise you will learn how to make use of APIs from oneMKL Interfaces library.
More specifically to perform a matrix multiplication using GEMM

The source code provides template to perform GEMM using oneMKL's BUFFER API:
Please refer to the API here: https://spec.oneapi.io/versions/latest/elements/oneMKL/source/domains/blas/gemm.html#gemm-buffer-version

---
## Exercise `OneMKL_buffer_gemm/source.cpp`

The source code invloves matrix array initialization on host and generate reference results on the host.
`source.cpp` has templates with TODOs to complete the exercise

## Build and execution hints

To run the example: ./OneMKL_buffer_gemm_solution (or) ./OneMKL_buffer_gemm_source
To verify with CUBLAS debug info, `export CUBLAS_LOGINFO_DB=1` and `export CUBLAS_LOGDEST_DBG=stdout`

For DevCloud via SSH follow these [instructions](../devcloud.md).

For DPC++: [instructions](../dpcpp.md).

For AdaptiveCpp: [instructions](../adaptivecpp.md).
