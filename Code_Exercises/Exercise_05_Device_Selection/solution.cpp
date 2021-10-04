/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#if __has_include(<SYCL/sycl.hpp>)
#include <SYCL/sycl.hpp>
#else
#include <CL/sycl.hpp>
#endif

class scalar_add;

// Example device selector, looks for an Intel GPU, you may want to write a
// different device selector for the device you are looking for on your machine.
class intel_gpu_selector : public sycl::device_selector {
 public:
  int operator()(const sycl::device& dev) const override {
    if (dev.has(sycl::aspect::gpu)) {
      auto vendorName = dev.get_info<sycl::info::device::vendor>();
      if (vendorName.find("Intel") != std::string::npos) {
        return 1;
      }
    }
    return -1;
  }
};

TEST_CASE("intel_gpu_device_selector", "device_selectors_solution") {
  int a = 18, b = 24, r = 0;

  try {
    auto asyncHandler = [&](sycl::exception_list exceptionList) {
      for (auto& e : exceptionList) {
        std::rethrow_exception(e);
      }
    };

    auto defaultQueue = sycl::queue{intel_gpu_selector{}, asyncHandler};

    std::cout << "Chosen device: "
              << defaultQueue.get_device().get_info<sycl::info::device::name>()
              << std::endl;

    {
      auto bufA = sycl::buffer{&a, sycl::range{1}};
      auto bufB = sycl::buffer{&b, sycl::range{1}};
      auto bufR = sycl::buffer{&r, sycl::range{1}};

      defaultQueue
          .submit([&](sycl::handler& cgh) {
            auto accA = sycl::accessor{bufA, cgh, sycl::read_only};
            auto accB = sycl::accessor{bufB, cgh, sycl::read_only};
            auto accR = sycl::accessor{bufR, cgh, sycl::write_only};

            cgh.single_task<scalar_add>([=]() { accR[0] = accA[0] + accB[0]; });
          })
          .wait();
    }

    defaultQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  REQUIRE(r == 42);
}
