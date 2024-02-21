# SYCL Academy

This section shows the use of some SYCL features in order to perform a vector
reduce operation.

## Naive SYCL reduction

`reduce_naive.cpp` shows a reduction performed without using atomics or
any other SYCL feature. It uses two separate kernels to achieve device
synchronization between reductions step 1 and 2.

## SYCL Atomics

`reduce_atomic.cpp` shows a reduction operation using local memory and
global memory atomics. Workgroups perform a local reduction using local atomics
and the result is added together using a single global memory 
`sycl::atomic_ref`.

## SYCL Group Algorithms

`reduce_group_algorithm.cpp` replaces the local memory atomic add with a call
to `sycl::reduce_over_group`, which can be expected to perform a similar operation
to the device function `workgroup_reduce_local_mem` as seen in
`reduce_naive.cpp`.

## SYCL Reductions

`reduce_sycl_reduction.cpp` replaces the entire logic of the reduction with a
SYCL reducer object. The reduction is a parameter of the `parallel_for`
invocation, and there is another reducer object used as a parameter to the
kernel lambda.
