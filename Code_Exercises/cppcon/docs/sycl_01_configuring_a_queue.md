# Parallelism in Modern C++; from CPU to GPU
### Exercise 1: Configuring a Queue

---

In this first exercise you will learn:
* How to construct a queue using a device selector.
* How to define and use your own device selector.
* How to query information about a device.

---

The first thing you must do in a SYCL application is to construct a queue that will enqueue work, and a queue is associated with a single device to which it enqueues work. The simplest way to construct a queue in SYCL is to pass it a device selector, that is then used to choose a device from all the devices available in your system.

1.) Create a queue using the default selector

Construct a SYCL queue using the default constructor and try printing the name of the device.

Remember the device associated with a queue can be retrieved using the `get_device` member function and information about a device can be queried using the `get_info` member function template.

2.) Try other device selectors

Replace the default selector with one of the other standard device selectors that are provided by SYCL (see [SYCL 1.2.1 specification][sycl-specification], sec. 4.6.1.2) and see which device those choose.

3.) Create your own device selector

Create a device selector using the template below, implementing the function call operator, using various device and platform info queries like the one we used earlier to query the device name (see SYCL 1.2.1 specification, sec. 4.6.4.2) and then use that device selector in the queue constructor:

```
class my_device_selector : public device_selector {
 public:
  my_device_selector() {}

  virtual int operator()(const device &device) const { }
};
```

Remember the platform associated with a device can be retrieved using the `get_platform` member function.

Remember that the value returned from the device selector's function call operator will represent the score for each device, and a device with a negative score will never be chosen. 


[sycl-specification]: https://www.khronos.org/registry/SYCL/specs/sycl-1.2.1.pdf