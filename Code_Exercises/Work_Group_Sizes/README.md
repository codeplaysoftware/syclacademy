# SYCL Academy

## Work-Group Sizes
---

In this exercise you will learn how to use different work-group sizes in order
to compare the performance difference.

---

### 1.) Try different work-group sizes

In order to optimize for occupancy try different work-group sizes, by specifying
a different local range for the `nd_range`.

Note that if the work-group size exceeds the maximum work-group size the target
device supports then it will fail to execute.

Compare the performance of the various work-group sizes you try.

## Build and execution hints

For DevCloud via JupiterLab follow these [instructions](../devcloudJupyter.md).

For DPC++: [instructions](../dpcpp.md).

For AdaptiveCpp: [instructions](../adaptivecpp.md).
