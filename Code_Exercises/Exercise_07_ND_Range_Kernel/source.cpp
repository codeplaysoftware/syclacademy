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
 * // Construct an in-order queue
 * auto q = sycl::queue{sycl::default_selector_v, 
 *        {sycl::property::queue::in_order{}}};
 *
 * // Declare a buffer pointing to ptr
 * auto buf = sycl::buffer{ptr, sycl::range{n}};
 *
 * // Do a USM memcpy
 * auto event = q.memcpy(dst_ptr, src_ptr, sizeof(T)*n);
 * // Do a USM memcpy with dependent events
 * auto event = q.memcpy(dst_ptr, src_ptr, sizeof(T)*n, {event1, event2});
 *
 * // Wait on an event
 * event.wait();
 *
 * // Wait on a queue
 * q.wait();
 *
 * // Submit work to the queue
 * auto event = q.submit([&](sycl::handler &cgh) {
 *   // COMMAND GROUP
 * });
 *
 *
 * // Within the command group you can
 * //    1. Declare an accessor to a buffer
 *          auto read_write_acc = sycl::accessor{buf, cgh};
 *          auto read_acc = sycl::accessor{buf, cgh, sycl::read_only};
 *          auto write_acc = sycl::accessor{buf, cgh, sycl::write_only};
 *          auto no_init_acc = sycl::accessor{buf, cgh, sycl::no_init};
 * //    2. Enqueue a parallel for:
 * //             i: With range:
 *                    cgh.parallel_for<class mykernel>(sycl::range{n}, 
 *                    [=](sycl::id<1> i) { // Do something });
 * //             ii: With nd_range:
 *                    cgh.parallel_for<class mykernel>(sycl::nd_range{
 *                        globalRange, localRange}, [=](sycl::nd_item<1> i) { 
 *                        // Do something
 *                      });
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <sycl/sycl.hpp>

class vector_add_1;
class vector_add_2;

TEST_CASE("range_kernel_with_item", "nd_range_kernel_source") {
  constexpr size_t dataSize = 1024;

  float a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i);
    r[i] = 0.0f;
  }

  try {
    auto gpuQueue = sycl::queue{sycl::gpu_selector_v};

    auto bufA = sycl::buffer{a, sycl::range{dataSize}};
    auto bufB = sycl::buffer{b, sycl::range{dataSize}};
    auto bufR = sycl::buffer{r, sycl::range{dataSize}};

    gpuQueue.submit([&](sycl::handler& cgh) {
      sycl::accessor accA{bufA, cgh, sycl::read_only};
      sycl::accessor accB{bufB, cgh, sycl::read_only};
      sycl::accessor accR{bufR, cgh, sycl::write_only};

      // TODO 1a: Replace `sycl::id` with `sycl::item`
      cgh.parallel_for<vector_add_1>(
          sycl::range{dataSize}, 
          [=](sycl::id<1> idx) {
          // TODO 1b: Retrieve the `idx` from `item` with `get_id()` member function  
            accR[idx] = accA[idx] + accB[idx];
          });
    });

    gpuQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == static_cast<float>(i) * 2.0f);
  }
}


TEST_CASE("nd_range_kernel", "nd_range_kernel_source") {
  constexpr size_t dataSize = 1024;

  float a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i);
    r[i] = 0.0f;
  }

  try {
    auto gpuQueue = sycl::queue{sycl::gpu_selector_v};

    auto bufA = sycl::buffer{a, sycl::range{dataSize}};
    auto bufB = sycl::buffer{b, sycl::range{dataSize}};
    auto bufR = sycl::buffer{r, sycl::range{dataSize}};

    gpuQueue.submit([&](sycl::handler& cgh) {
      sycl::accessor accA{bufA, cgh, sycl::read_only};
      sycl::accessor accB{bufB, cgh, sycl::read_only};
      sycl::accessor accR{bufR, cgh, sycl::write_only};

      // TODO 2a: Replace `sycl::range` with `sycl::nd_range{globalRange, localRange}`.
      // `dataSize` can be chosen as `GlobalRange` for now. 
      // `localRange` is the size of the "thread block" of your choice.
      //
      // TODO 2b: Replace `sycl::id` with `sycl::nd_item`
      cgh.parallel_for<vector_add_2>(
          sycl::range{dataSize}, 
          [=](sycl::id<1> idx) {
          // TODO 2c: Retrieve the `idx` from `nd_item`.
          // One option is with the `get_global_linear_id()` member function  
            accR[idx] = accA[idx] + accB[idx];
          });
    });

    gpuQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == static_cast<float>(i) * 2.0f);
  }
}
