# SYCL Academy

## Exercise 11: Using the oneMath library for matrix multiplication
---

In this exercise you will learn how to use the API of the oneMath library and
perform a matrix multiplication using the GEMM routines.

The source code provides a template to perform GEMM using oneMath's USM/buffer
API. Please refer to the API here:
https://oneapi-spec.uxlfoundation.org/specifications/oneapi/latest/elements/onemath/source/domains/blas/gemm

---
## Exercise `oneMath_usm_gemm/source.cpp`

The `source_*.cpp` already include all the code to create input matrices and
compute a reference result serially on host. The exercise is to fill in the
sections marked with "TODO" comments to perform GEMM on a device using oneMath.

## Build and execution hints

To run the example: ./oneMath_usm_gemm_solution (or) ./oneMath_usm_gemm_source
To verify with CUBLAS debug info, `export CUBLAS_LOGINFO_DB=1` and `export CUBLAS_LOGDEST_DBG=stdout`

For DevCloud via JupiterLab follow these [instructions](../devcloudJupyter.md).

For DPC++: [instructions](../dpcpp.md).

For AdaptiveCpp: [instructions](../adaptivecpp.md).
