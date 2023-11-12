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

TEST_CASE("vector_add", "synchronization_buffer_acc") {
  constexpr size_t dataSize = 1024;

  int a[dataSize];
  sycl::queue Q{};

  try {
    auto bufA = sycl::buffer{a, sycl::range{dataSize}};
    Q.submit([&](sycl::handler& cgh) {
          sycl::accessor accA{bufA, cgh, sycl::write_only};
          cgh.parallel_for(
              sycl::range{dataSize},
              [=](sycl::id<1> idx) { accA[idx] = 42});
        })
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
   }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(a[i] == 42);
  }
}
