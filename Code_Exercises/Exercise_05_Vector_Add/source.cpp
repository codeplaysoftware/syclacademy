/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

 * SYCL Quick Reference
 * ~~~~~~~~~~~~~~~~~~~~
 *
 * // Default construct a queue
 * auto q = sycl::queue{};
 *
 * // Declare a buffer pointing to ptr
 * auto buf = sycl::buffer{ptr, sycl::range{n}};
 *
 * // Submit work to the queue
 * q.submit([&](sycl::handler &cgh) {
 *   // COMMAND GROUP
 * });
 *
 * // Within the command group you can
 * //    1. Declare an accessor to a buffer
 *          auto read_write_acc = sycl::accessor{buf, cgh};
 *          auto read_acc = sycl::accessor{buf, cgh, sycl::read_only};
 *          auto write_acc = sycl::accessor{buf, cgh, sycl::write_only};
 *          auto no_init_acc = sycl::accessor{buf, cgh, sycl::no_init};
 * //    2. Enqueue a single task:
 *          cgh.single_task<class mykernel>([=]() {
 *              // Do something
 *          });
 * //    3. Enqueue a parallel for:
 *          cgh.parallel_for<class mykernel>(sycl::range{n}, [=](sycl::id<1> i) {
 *              // Do something
 *          });
 *
*/

#define CATCH_CONFIG_MAIN
//#include <catch2/catch.hpp>

TEST_CASE("vector_add", "vector_add_solution") {
  constexpr size_t dataSize = 1024;

  float a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i);
    r[i] = 0.0f;
  }

  // Task: Compute r[i] = a[i] + b[i] in parallel on the SYCL device
  
  // TODO: Comment out the computation in line 56 - 58 
  for (int i = 0; i < dataSize; ++i) {
    r[i] = a[i] + b[i];
  }

  try {
    // TODO 1a: Create a `queue` with your choice of `selector` 

    // TODO 2: Create `buffers` for input a, b and output r which all have a size of `dataSize`

    // TODO 3a: Submit a command group functor for execution on a queue. This functor
    // encapsulates the kernel and the data needed for its execution.
    
    // TODO 3b: Inside the command group functor, create `accessor`s for each `buffer`s

    // TODO 4: Implement a vector-add kernel with `parallel_for` and lambda function
    
    // TODO 3c (Optional): Throw asynchronous exceptions if any
    
  } catch (const sycl::exception& e) {
    // TODO 1b: Print out error messages of synchronous exceptions if any
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == static_cast<float>(i) * 2.0f);
  }
}
