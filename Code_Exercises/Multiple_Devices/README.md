# SYCL Academy

## Load Balancing

---

In this exercise you will learn how to create two separate queues and then split
a task across two devices.

---

### 1.) Get two devices

Get two devices. If only host device is available then both devices may be identical, that is the host device.

### 2.) Create queues

Then create a `queue` for each of the two devices. 

### 3. ) Split a task across the two queues

Using either the application from the "Data Parallelism" exercise with the
buffer/accessor model or the application from the "Using USM" exercise with the
USM model, create an application where the work is distributed across two
devices using the two `queue`s you created.

Remember to create separate `buffer`s for the separate parts of the data being
computed.

Remember to wait on the work enqueued to both`queue`s to complete and remember
to handle errors.

Also note that you will need to have different types defined to name each of the
two kernel kernel functions.

### 4. ) Tweak the load balancing

Try playing around with the distribution of the work between the two devices by
changing the `range` and `offset` of the two `buffer`s.

## Build and execution hints

For DevCloud via JupiterLab follow these [instructions](../devcloudJupyter.md).

For DPC++: [instructions](../dpcpp.md).

For AdaptiveCpp: [instructions](../adaptivecpp.md).
