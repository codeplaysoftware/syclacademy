/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#if __has_include(<SYCL/sycl.hpp>)
#include <SYCL/sycl.hpp>
#else
#include <CL/sycl.hpp>
#endif

#include <iostream>

class buffer_scalar_add;
class usm_scalar_add;
constexpr size_t dataSize = 1024;

using T = float;

constexpr T value = 42;

int main () {
	
  // Buffers
  int a = 18, b = 24, r = 0;

  auto q = sycl::queue{};

  {
    auto bufA = sycl::buffer{&a, sycl::range{1}};
    auto bufB = sycl::buffer{&b, sycl::range{1}};
    auto bufR = sycl::buffer{&r, sycl::range{1}};

    q.submit([&](sycl::handler &cgh) {
          auto accA = sycl::accessor{bufA, cgh, sycl::read_only};
          auto accB = sycl::accessor{bufB, cgh, sycl::read_only};
          auto accR = sycl::accessor{bufR, cgh, sycl::write_only};

          cgh.single_task<buffer_scalar_add>([=] { accR[0] = accA[0] + accB[0]; });
        })
        .wait();
	if (r == value) {
      std::cout << "Got expected answer: 42\n";
    } else {
      std::cout << "Got unexpected answer: " << a << '\n';
    }
  }
  
  // USM
  r = 0;
  auto aPtr = sycl::malloc_device<T>(1, q);
  auto bPtr = sycl::malloc_device<T>(1, q);
  auto rPtr = sycl::malloc_device<T>(1, q);

  q.fill(aPtr, value, 0).wait();
  q.fill(bPtr, value, 0).wait();
  q.fill(rPtr, value, 0).wait();

  {
    q.memcpy(aPtr, &a, sizeof(T)).wait();
    q.memcpy(bPtr, &b, sizeof(T)).wait();
    q.memcpy(rPtr, &r, sizeof(T)).wait();
    
    q.submit([&](sycl::handler &cgh) {
          cgh.single_task<usm_scalar_add>([=] { rPtr[0] = aPtr[0] + bPtr[0]; });
        })
        .wait();

  q.memcpy(&r, rPtr, sizeof(T)).wait();

  sycl::free(aPtr, q);
  sycl::free(bPtr, q);
  sycl::free(rPtr, q);
  
  }
  if (r == value) {
    std::cout << "Got expected answer: 42\n";
  } else {
    std::cout << "Got unexpected answer: " << a << '\n';
  }


}
