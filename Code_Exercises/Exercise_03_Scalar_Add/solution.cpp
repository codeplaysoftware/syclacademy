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

class scalar_add;

using T = float;

constexpr T value = 23;

int main {
	
  // Buffers
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

          cgh.single_task<scalar_add>([=] { accR[0] = accA[0] + accB[0]; });
        })
        .wait();
  }
  
  // USM
  T a = 0;

  auto q = sycl::queue{};

  auto devPtr = sycl::malloc_device<T>(1, q);

  q.fill(devPtr, value, 1).wait();

  q.memcpy(&a, devPtr, sizeof(T)).wait();

  if (a == value) {
    std::cout << "Got expected answer: 23\n";
  } else {
    std::cout << "Got unexpected answer: " << a << '\n';
  }


}

  




