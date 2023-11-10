# SYCL Academy

## Exercise 02: Data Management

---

In this exercise, you'll see how to use USM as an alternative to buffers.
Both have their place, and we'll explore this by having you change the simple
Pi calculation kernel use USM memory to store it's result.


We assume you have your environment set up to compile, since we did that in Exercise 01.
Ask for help if you have not completed Exercise 01 - we are here to help!

This exercise uses the solution from Exercise 01 as it's basis.
It should look familiar.
If you have extra time, we hope you'll explore making more additions or changes.

---

### 1.) Change the declaration of d4.

In the buffer version, we decalre d4 as a std::array and then connect a buffer to it
and use accessors to give the kernel and host access to the data during the buffer
lifetime.

Since a kernel or host can "just" access data in a USM shared memory, we want to simply
create shared memory and then use it.

The first step is to create d4 as share memory.

Do something like this:

auto d4 = (int *)sycl::malloc_shared( sizeof(int)*200, myQueue2 );

### 2.) Change the accesses to use the share memory.

We don't need the buffer declaration (outD4).

We don't need the accessor declaration (OutAccessor).

We can just use d4 directly instead of OutAccessor.

Therefore, you just need to delete a couple declarations and change the access (in the output statement in the kernel).

#### Build And Execution Hints

For DPC++ (using the Intel DevCloud):
```sh
cd ~/syclacademy/Code_Exercises/Exercise_02_Data_Management
icpx -fsycl -o sycl-ex-2 source.cpp
cp ../Images/goldfish.png  .
./sycl-ex-2 goldfish.png
```

