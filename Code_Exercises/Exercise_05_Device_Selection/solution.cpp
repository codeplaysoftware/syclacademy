/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <SYCL/sycl.hpp>

class scalar_add;

class intel_gpu_selector : public sycl::device_selector {
 public:
  virtual int operator()(const sycl::device& dev) const {
    if (dev.get_info<sycl::info::device::device_type>() ==
        sycl::info::device_type::gpu) {
      auto vendorName = dev.get_info<sycl::info::device::vendor>();
      if (std::strstr(vendorName.c_str(), "Intel") != nullptr) {
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
            auto accA = bufA.get_access<sycl::access::mode::read>(cgh);
            auto accB = bufB.get_access<sycl::access::mode::read>(cgh);
            auto accR = bufR.get_access<sycl::access::mode::write>(cgh);

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
