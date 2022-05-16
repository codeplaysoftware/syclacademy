/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#if defined(SYCL_LANGUAGE_VERSION) && defined(__INTEL_LLVM_COMPILER)
#include <CL/sycl.hpp>
#else
#include <SYCL/sycl.hpp>
#endif

class vector_add;

TEST_CASE("vector_add", "vector_add_solution") {
  constexpr size_t dataSize = 1024;
<<<<<<< HEAD

  float a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i);
    r[i] = 0.0f;
  }

  // Task: Compute r[i] = a[i] + b[i] in parallel on the SYCL device
  for (int i = 0; i < dataSize; ++i) {
    r[i] = a[i] + b[i];
=======

  float a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i);
    r[i] = 0.0f;
  }

  try {
    auto asyncHandler = [&](sycl::exception_list exceptionList) {
      for (auto& e : exceptionList) {
        std::rethrow_exception(e);
      }
    };

    auto defaultQueue = sycl::queue{sycl::default_selector_v, asyncHandler};

    auto bufA = sycl::buffer{a, sycl::range{dataSize}};
    auto bufB = sycl::buffer{b, sycl::range{dataSize}};
    auto bufR = sycl::buffer{r, sycl::range{dataSize}};

    defaultQueue
        .submit([&](sycl::handler& cgh) {
          auto accA = bufA.get_access<sycl::access::mode::read>(cgh);
          auto accB = bufB.get_access<sycl::access::mode::read>(cgh);
          auto accR = bufR.get_access<sycl::access::mode::write>(cgh);

          // Write your kernel code here using range and id, executing
		  // accR[idx] = accA[idx] + accB[idx]; 
		  // see slide 16 of Lesson 6 for examples
        })
        .wait();

    defaultQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
>>>>>>> origin/isc21
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == static_cast<float>(i) * 2.0f);
  }
}

