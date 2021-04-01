# SYCL Academy

## Exercise 13: Load Balancing

---

In this exercise you will learn how to create two separate queues and then split
a task across two devices.

---

### 1.) Create a context

Retrieve two devices (if possible from the same platform), and then create
`context`(s) from those devices.

If both of the devices are from the same platform you can create a single
`context` from both of the devices.

If the devices are from different platforms you will have to create separate
`context`s.

Note if you only have one device available you can use the host device or
use the same device twice

### 2.) Create queues

Then create a `queue` for each of the two devices.

### 3. ) Split a task across the two queues

Using either the application from exercise 6 using the buffer/accessor model or
the application from exercise 8 with the USM model create an application where
the work is distributed across two devices using the two `queue`s you created.

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

```
cmake -DSYCL_ACADEMY_USE_COMPUTECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/computecpp ..
make configuring_queues_source
./Code_Exercises/Exercise_13_Load_Balancing/load_balancing_source
```
