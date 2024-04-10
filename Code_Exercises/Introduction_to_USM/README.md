# SYCL Academy

## Exercise 7: USM Selector
---

In this exercise you will learn how to find a suitable device for using the USM data management model.

---

### 1.) Create a device selector

Create a custom device selector as you did in exercise 5.

### 2.) Check for USM support

Within this device selector check for whether the device being inspected has
support for the USM device allocations.

This can be querying for the `aspect::usm_device_allocations` aspect.

### 3.) Create a queue

Once you have a device selector which will choose a device which supports USM
create a `queue` using it to select its device, remember to handle errors.


#### Build And Execution Hints

For DevCloud via SSH follow these [instructions](../devcloud.md).

For DPC++: [instructions](../dpcpp.md).

For AdaptiveCpp: [instructions](../adaptivecpp.md).
