# SYCL Academy

## Exercise 4: Handling Errors

---

In this exercise you will learn how to handle synchronous and asynchronous
exceptions.

---

### 1.) Catch synchronous exception handling

Synchronous errors, such as failure to construct an object, are reported
immediately  by  the  runtime  throwing  an  exception.

To catch synchronous exceptions simply wrap your application in a try catch
block and catch a SYCL `exception` and print out the error message provided by
the `what` member function.

### 2. ) Catch and asynchronous exceptions

Asynchronous  errors, such  as  an  error  occurring  during execution of a
kernel on a device, are reported via user-supplied asynchronous error-handlers.

To catch asynchronous exceptions create an async handler using a lambda
expression which takes an `exception_list`, iterates over it and rethrows the
exceptions to be caught by the surrounding try-catch block.

#### Build And Execution Hints

For DevCloud via SSH follow these [instructions](../devcloud.md).

For DPC++: [instructions](../dpcpp.md).

For AdaptiveCpp: [instructions](../adaptivecpp.md).
