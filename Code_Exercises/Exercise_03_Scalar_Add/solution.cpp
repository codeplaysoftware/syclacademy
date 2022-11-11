/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#if __has_include(<sycl/sycl.hpp>)
#include <sycl/sycl.hpp>
#else
#include <CL/sycl.hpp>
#endif

class scalar_add_usm;
class scalar_add_buff_acc;

TEST_CASE("scalar_add_usm", "scalar_add_solution") {
  int a = 18, b = 24, r = 0;

  auto defaultQueue = sycl::queue{};

  auto dev_A = sycl::malloc_device<int>(1, defaultQueue);
  auto dev_B = sycl::malloc_device<int>(1, defaultQueue);
  auto dev_R = sycl::malloc_device<int>(1, defaultQueue);

  defaultQueue.memcpy(dev_A, &a, 1 * sizeof(int));
  defaultQueue.memcpy(dev_B, &b, 1 * sizeof(int));

  defaultQueue
      .submit([&](sycl::handler &cgh) {
        cgh.single_task<scalar_add_usm>([=] { dev_R[0] = dev_A[0] + dev_B[0]; });
      });

  defaultQueue.memcpy(&r, dev_R, 1 * sizeof(int)).wait();

  sycl::free(dev_A, defaultQueue);
  sycl::free(dev_B, defaultQueue);
  sycl::free(dev_R, defaultQueue);

  REQUIRE(r == 42);
}

TEST_CASE("scalar_add_buff_acc", "scalar_add_solution") {
  int a = 18, b = 24, r = 0;

  auto defaultQueue = sycl::queue{};

  {
    auto bufA = sycl::buffer{&a, sycl::range{1}};
    auto bufB = sycl::buffer{&b, sycl::range{1}};
    auto bufR = sycl::buffer{&r, sycl::range{1}};

    defaultQueue
        .submit([&](sycl::handler &cgh) {
          auto accA = sycl::accessor{bufA, cgh, sycl::read_only};
          auto accB = sycl::accessor{bufB, cgh, sycl::read_only};
          auto accR = sycl::accessor{bufR, cgh, sycl::write_only};

          cgh.single_task<scalar_add_buff_acc>([=] { accR[0] = accA[0] + accB[0]; });
        })
        .wait();
  }

  REQUIRE(r == 42);
}
