# SYCL Academy

## Exercise 11: In Order Queue
---

In this exercise you will learn how to create a fixed data flow using an
in-order `queue`.

---
## Exercise `queue_benchmarking`

Your old coworker is lazy, and has enqueued all the kernels in the same in-order queue.
Performance is poor as kernels cannot execute concurrently. Your goal is to improve it:

- Using one out-of-order queue
- Using multiple in-order queues


## Exercise `vector_add`

### 1.) In order queue with buffer/accessor model

Using the application from exercise 10 which uses the buffer/accessor model
convert the `queue` to in-order using the `property::queue::in_order` property,
converting the data flow graph to a fixed execution order.

Feel free to have the kernel functions execute in any order you like providing
the necessary dependencies described in exercise 10 are still met.

### 2.) In order queue with USM model

Now do the same using the application from exercise 10 which uses the USM model,
again converting the `queue` to in-order, converting the data flow graph to a
fixed execution order.

Again feel free to have the kernel functions execute in any order you like
providing the necessary dependencies described in exercise 10 are still met.

Note that in the USM model when using an in-order `queue` it is no longer
necessary to chain commands using `event`s.

## Build and execution hints

For DevCloud via SSH follow these [instructions](../devcloud.md).

For DPC++: [instructions](../dpcpp.md).

For AdaptiveCpp: [instructions](../adaptivecpp.md).
