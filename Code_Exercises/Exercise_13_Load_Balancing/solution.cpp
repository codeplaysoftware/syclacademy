/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <sycl/sycl.hpp>

#include <algorithm>

class vector_add_first;
class vector_add_second;

// This function returns a vector of two (not necessarily distinct) devices,
// allowing computation to be split across said devices.
std::vector<sycl::device> get_two_devices() {
  auto devs_gpu = sycl::device::get_devices(sycl::info::device_type::gpu);
  auto devs = sycl::device::get_devices(sycl::info::device_type::cpu);
  devs.insert(devs.end(), devs_gpu.begin(), devs_gpu.end());
  if (devs.size() == 0) throw "No devices available";
  if (devs.size() == 1)
    return {devs[0], devs[0]};

  return {devs[0], devs[1]};
}

TEST_CASE("load_balancing", "load_balancing_solution") {
  constexpr size_t dataSize = 1024;
  constexpr float ratio = 0.5f;
  constexpr size_t dataSizeFirst = ratio * dataSize;
  constexpr size_t dataSizeSecond = dataSize - dataSizeFirst;

  float a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i);
    r[i] = 0.0f;
  }

  try {
    auto devs = get_two_devices();
    auto Q1 = sycl::queue{devs[0]};
    auto Q2 = sycl::queue{devs[1]}; // if only one device is found, both queues
                                    // will use same device

    std::cout << "Running on devices:" << std::endl;
    std::cout << "1:\t" << Q1.get_device().get_info<sycl::info::device::name>()
              << std::endl;
    std::cout << "2:\t" << Q2.get_device().get_info<sycl::info::device::name>()
              << std::endl;

    auto bufFirstA = sycl::buffer{a, sycl::range{dataSizeFirst}};
    auto bufFirstB = sycl::buffer{b, sycl::range{dataSizeFirst}};
    auto bufFirstR = sycl::buffer{r, sycl::range{dataSizeFirst}};

    auto bufSecondA =
        sycl::buffer{a + dataSizeFirst, sycl::range{dataSizeSecond}};
    auto bufSecondB =
        sycl::buffer{b + dataSizeFirst, sycl::range{dataSizeSecond}};
    auto bufSecondR =
        sycl::buffer{r + dataSizeFirst, sycl::range{dataSizeSecond}};

    Q1.submit([&](sycl::handler &cgh) {
      sycl::accessor accA{bufFirstA, cgh, sycl::read_only};
      sycl::accessor accB{bufFirstB, cgh, sycl::read_only};
      sycl::accessor accR{bufFirstR, cgh, sycl::write_only};

      cgh.parallel_for<vector_add_first>(
          sycl::range{dataSizeFirst},
          [=](sycl::id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
    });

    Q2.submit([&](sycl::handler &cgh) {
      sycl::accessor accA{bufSecondA, cgh, sycl::read_only};
      sycl::accessor accB{bufSecondB, cgh, sycl::read_only};
      sycl::accessor accR{bufSecondR, cgh, sycl::write_only};

      cgh.parallel_for<vector_add_second>(
          sycl::range{dataSizeSecond},
          [=](sycl::id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
    });

    Q1.wait_and_throw();
    Q2.wait_and_throw();
  } catch (const sycl::exception &e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == static_cast<float>(i) * 2.0f);
  }
}
