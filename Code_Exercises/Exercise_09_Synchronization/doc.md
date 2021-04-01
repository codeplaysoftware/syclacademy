# SYCL Academy

## Exercise 9: Synchronization
---

In this exercise you will learn how to use different techniques for
synchronizing commands and data.

---

### 1.) Waiting on events

Take a look at the vector add applications using the buffer/accessor model in
exercise 6 and the USM model in exercise 8, and familiarize yourself with how
they call `wait` on returned `event`s to synchronize the completion of the work.

### 2.) Waiting on queues

With those same applications convert them to call `wait` on the `queue` to
synchronize instead.

### 3.) Buffer destruction

Take a look at the vector add application using the buffer/accessor mode in
exercise 6 and how it synchronizes on the destruction of the `buffer`s. 

### 4.) Copy back

Take a look that two applications again and familiarize yourself with how the
result of the computation is copied back to the host.

In the case of the application using the buffer/accessor model note how this
occurs implicitly on the destruction of the `buffer`.

In the case of the application using the USM model note how this occurs
explicitly by calling `memcpy`.

### 4.) Host accessor

Finally with the application which is using the buffer/accessor model introduce
a host `accessor` by calling `get_host_access` on the `buffer`. The host
`accessor` can be used to check the result of the computation on the host while
the `buffer` is still alive.

Remember to do this within a scope to ensure the host `accessor` is destroyed.

Also note that creating a host `accessor` may copy the data back to the original
pointer provided to the `buffer` but this is not guaranteed.

## Build and execution hints

```
cmake -DSYCL_ACADEMY_USE_COMPUTECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/computecpp ..
make synchronization_source
./Code_Exercises/Exercise_9_Synchronization/synchronization_source
```
