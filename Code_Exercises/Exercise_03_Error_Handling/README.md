# SYCL Academy

## Exercise 3: Handling Errors

---

In this exercise, you will learn how to handle synchronous and
asynchronous exceptions.  Specifically, you will introduce a few
errors and catch them using standard C++ try catch.  Of course,
asynchornous errors are caught by the SYCL runtime and made available
to us to handle with standard C++ mechanisms which only support a
synchronous model directly.

We assume you have your environment set up to compile, since we did
that in Exercise 01.  Ask for help if you have not completed Exercise 01 -
we are here to help!

This exercise uses the solution from Exercise 02 as it's basis, which
was based on Exercise 01.  Therefore, the code should look familiar.
If you have extra time, we hope you'll explore making more additions
or changes.

---

### 1.) Create a synchronous error that terminates the program.

Let's introduce code at the very start of the main() body since there
is no need to use any of the preexisting code.  Either of the
following two code choices will do the trick if add at the start of
main().

```
    // CHOICE 1
    // borrowed from Figure 5-2 in book
    // always bad buffer code
    sycl::buffer<int> b{sycl::range{16}};
    sycl::buffer<int> b2{b, sycl::id{8}, sycl::range{16}};

    // CHOICE 2
    // borrowed from a Codeplay example from computecpp documentation
    // Don't worry (for now) why this creates an error. It's a poorly constructed work size that will not work in general.
    sycl::queue quick_queue;
    sycl::event e2c =
      quick_queue.submit([&](sycl::handler& cgh2c) {
	auto err_range = sycl::nd_range<1>(sycl::range<1>(1), sycl::range<1>(10));
        cgh2c.parallel_for(err_range, [=](sycl::nd_item<1>) {});
      });
```

The key things are this: once we put either code in our application,
it will be forcibly terminated due to violation of SYCL rules
resulting in a SYCL runtime exception.

Compile and run the application, and it should terminate with a message about this error.

Feel free to add both code choices, and you'll note only the first one
causes an error since temination is the resulting action.  We can fix
that (next).

### 2.) Create a bit more control using a try/catch.

Let's surround our error producing code (from the first step) with a try { CODE HERE } catch { PRINT MESSAGE }.

Wrap our code with a standard C++ try/catch construct.  We'll start by only catching SYCL exceptions.

```
  try {
    // code from step 1
  } catch (sycl::exception e) {
    std::cout << "Caught SYCL exception: " << e.what()
              << std::endl;
  }
```

This gives us enough control that we do not terminate our application.
That's good because our goal for this exercise it to produce mulitple
exceptions. We can't produce multiple exceptions if the first one
terminates our program!

Compile and run the application. With our try/catch wrapping our error
from step 1, the program should work just like it did for exercise two
with the addition of a message from our catch.

If you did add both code choices, we can get two error messages
without terminating assuming we wrapped each code choice with its own
try/catch.

### 3.) Let's tidy things up a little so we can feel better about our C++ coding style.

In order to be a little more complete, we can add a few lines
(completely unnecesssary for this exercise) to catch more than just
SYCL exceptions. We do that extending the catches something like this:

```
  } catch (sycl::exception e) {
    std::cout << "Caught SYCL exception: " << e.what()
              << std::endl;
  } catch (std::exception &e) {
    std::cout << "Caught std exception: " << e.what() << "\n";
  } catch (...) {
    std::cout << "Caught unknown exception\n";
  }
```

With these in place, there will not be any exception within the try
block that defaults to terminating the application. This allows us to
have our application under our control. Without these catches, there
is a default that will print the exception information and then
terminate the application.

Compile and run the application, and it should behave the same as
after step 2. Yet, we can be comfortable that we wrote a catch for
every possible throw. If you are a little uncomfortable that we just
let the program continue, that is understandable but this is just an
exercise to have fun today - so you can relax.  :)

### 4.) Let's add an asynchronous error.

An asynchronous error occurs inside code submitted to run on a
device. It is asynchronous because the our host code does not block
waiting for device code to finish. This is important since it allows
our host code to do more work including queueing more work for
accelerators (maybe the same one, maybe others). It does complicate
the propogation of errors, a topic that is well covered in Chapter 5
of the book if you want to learn more.  For now, we'll solve catching
the asychronous error for our example.

We'll just steal an example from figure 5-3 in the book:

declare this before main:

`class something_when_wrong {} ;`

and add this to the start of main():

```
    sycl::queue quick_queue;
    sycl::event e2d =
        quick_queue.submit([&](sycl::handler& cgh2d) {
	  cgh2d.host_task([]() {
	    throw( something_when_wrong{} );
	  });
	});
```

We are using "host_task" in which we are allowed to do a throw. Device
code is not allowed to do a throw. We'll comment a bit more on this in
step 6.

Compile and run the application, and it should terminate with a message about this error.

### 5.) Let's get control so the program does not terminate.

When an asynchronous error occurs, only the SYCL runtime knows about
it. That is because C++ is really only tracking what happens on the
host and with host code. Therefore, a C++ throw/catch will not see an
asynchronous error without a little help. By default, the SYCL runtime
helps by trapping asynchonous errors and terminating our application
with an explanation. That's what happened in the prior step.

Now, we will change our code to introduce a handler that puts us back
in control with our own code instead of the default.

```
auto we_handle_async_error = [](sycl::exception_list elist) {
  for (auto &e : elist) {
    try {
      std::rethrow_exception(e);
    } catch (sycl::exception e) {
      std::cout << "2nd Handler Caught SYCL ASYNC exception!!\n";
    } catch (...) {
      std::cout << "2nd Handler Caught the Something Went Wrong\n";
    }
  }
};
```

Finally, change the queue constructor to use our error handler instead of the default:

```
    sycl::queue quick_queue( we_handle_async_error );
```

Compile and run the application. We should see this asynchronous error
noted without terminating the program now. This is in addition to the
error messages we produced with our prior work to introduce
synchronous errors.

### 6.) We are done with the exercise, but we promised a little more explanation.

We made up an error to throw from a host_task since we did not have a
consistent (portable) way to demonstrate an error from device
code. That is because devices are not required to detect and alert us
to any particular set of issues. For instance, most devices will not
halt based on a divide by zero. It is more likely that a divide by
zero is recorded as a NaN result and the program continues.

Do not be confused - devices can signal issues. But, what they might
signal is very device (and probably implementation) specific.

We do think that adding "assert" capability to device code would be a
useful extension in the future. Possibly worthy to consider for a
future SYCL standard.  The solution.cpp has code to try to use this
experimental extension from the DPC++ open source SYCL project, but
the device driver side support is not yet there so it is not yet
functional (as of November 10, 2023). It tries to cause an issue, but
when it is not caught it falls into code that checks (and should find)
that it is not supported by the device. That shows a nice example of
checking for a feature - even if we did it after it didn't work.  Here
is the code you'd see if you peaked in solution.cpp:

```
    sycl::event e2b =
        myQueue2.submit([&](sycl::handler& cgh2b) {
          cgh2b.single_task([=]() {
	    assert(0 && "Die now");
	  });
	});
    if (! myQueue2.get_device().has(sycl::aspect::ext_oneapi_native_assert)) {
      std::cout << "The assert extension to support in a kernel is not available for this device - so no async was thrown.\n";
    }
```

#### Build And Execution Hints

For DPC++ (using the Intel DevCloud):
```sh
cd ~/syclacademy/Code_Exercises/Exercise_03_Error_Handling
icpx -fsycl -o sycl-ex-3 source.cpp
cp ../Images/goldfish.png  .
./sycl-ex-3 goldfish.png
```
