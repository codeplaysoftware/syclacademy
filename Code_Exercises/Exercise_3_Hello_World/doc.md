# SYCL Academy

### Exercise 3: Hello World

---

In this first exercise you will learn:
* How to create and submit a command group.
* How to define a SYCL kernel function.
* How to stream output from a SYCL kernel function.

---

Once you have a queue you can now submit work to be executed on your chosen
device and this is done via command groups, which are made up of commands and
data dependencies.

1.) Define a command group

Define a lambda to represent your command group and pass it to the submit member
function of the queue.

Note that submitting a command group without any commands will result in an
error.

2.) Define a SYCL kernel function

Define a SYCL kernel function via the `single_task` command within the command
group, which takes only a function object which itself doesn't take any
parameters.

Remember to declare a class for your kernel name in the global namespace.

3.) Stream “Hello World!” to stdout from the SYCL kernel function

Create a `stream` object within the command group scope as follows. The two
parameters to the constructor of the `stream` class are the total buffer size
and the statement size respectively.

Then use the stream you constructed within the SYCL kernel function to print
“Hello world!” using the `<<` operator.

4.) Try another command

Instead of `single_task` try another command for defining a SYCL kernel function
(see [SYCL 1.2.1 specification][sycl-specification], sec 4.8.5).

Remember the function object for the `parallel_for` which takes a `range` can be
an `id` or an `item` and the function object for the `parallel_for` which takes
an `nd_range` must be an `nd_item`.

5.) Try a different dimensionality

Instead of a 1-dimensional range for your SYCL kernel function, try a 2 or
3-dimensional range.

[sycl-specification]: https://www.khronos.org/registry/SYCL/specs/sycl-1.2.1.pdf