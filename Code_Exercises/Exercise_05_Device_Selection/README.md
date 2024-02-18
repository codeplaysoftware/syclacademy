# SYCL Academy

## Exercise 5: Device Selection

---

In this exercise you will learn how to create a device selector that will choose
a device for you to enqueue work to.

---

### 1.) Query the device of your queue

When you default construct a `queue` the runtime will use the `default_selector_v`
to choose a device. 

Try querying the `device` associated with the `queue` and information about it.

Remember the device associated with a queue can be retrieved using the
`get_device` member function and information about a device can be queried
using the `get_info` member function template.

### 2.) Try other device selectors

Replace the default selector with one of the other standard device selectors
that are provided by SYCL such as the `cpu_selector_v`, `gpu_selector_v` 
and see which device those choose.

### 3.) Create your own device selector

Create a device selector using the template below. Implement the function
call operator, using various device and platform info queries like the one we
used earlier to query the device name and then use that device selector in the
queue constructor. 

To construct device selector, use the following rule:

The interface for a `device selector` is any object that meets the C++ named requirement `Callable`, 
taking a parameter of type `const device &` and returning a value that is implicitly convertible to `int`.

```
  int device_selector()(const device &device) { /* scoring logic */ }
```

Remember the platform associated with a device can be retrieved using the
`get_platform` member function.

Remember that the value returned from the device selector's function call
operator will represent the score for each device, and a device with a negative
score will never be chosen. 


#### Build And Execution Hints

For DevCloud via SSH follow these [instructions](../devcloud.md).

For DPC++: [instructions](../dpc.md).

For AdaptiveCpp: [instructions](../adaptivecp.md).