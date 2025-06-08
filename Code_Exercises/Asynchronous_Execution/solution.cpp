/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#include <sycl/sycl.hpp>
#include "../helpers.hpp"
using namespace sycl;



void test_buffer_event_wait() {
  constexpr size_t dataSize = 1024;

  int a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = i;
    b[i] = i;
    r[i] = 0;
  }

  try {
    queue defaultQueue = queue{};

    buffer bufA = buffer{a, range{dataSize}};
    buffer bufB = buffer{b, range{dataSize}};
    buffer bufR = buffer{r, range{dataSize}};

    defaultQueue
        .submit([&](handler& cgh) {
          accessor accA = accessor{bufA, cgh, read_only};
          accessor accB = accessor{bufB, cgh, read_only};
          accessor accR = accessor{bufR, cgh, write_only};

          cgh.parallel_for(
              range{dataSize},
              [=](id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
        })
        .wait();  // Synchronize

    defaultQueue.throw_asynchronous();
  } catch (const exception& e) {  // Copy back
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  SYCLACADEMY_ASSERT_EQUAL(r, [](size_t i) { return i * 2; });
}

void test_buffer_queue_wait() {
  constexpr size_t dataSize = 1024;

  int a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = i;
    b[i] = i;
    r[i] = 0;
  }

  try {
    queue defaultQueue = queue{};

    buffer bufA = buffer{a, range{dataSize}};
    buffer bufB = buffer{b, range{dataSize}};
    buffer bufR = buffer{r, range{dataSize}};

    defaultQueue.submit([&](handler& cgh) {
      accessor accA = accessor{bufA, cgh, read_only};
      accessor accB = accessor{bufB, cgh, read_only};
      accessor accR = accessor{bufR, cgh, write_only};

      cgh.parallel_for(
          range{dataSize},
          [=](id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
    });

    defaultQueue.wait_and_throw();      // Synchronize
  } catch (const sycl::exception& e) {  // Copy back
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  SYCLACADEMY_ASSERT_EQUAL(r, [](size_t i) { return i * 2; });
}

void test_buffer_buffer_destruction() {
  constexpr size_t dataSize = 1024;

  int a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = i;
    b[i] = i;
    r[i] = 0;
  }

  try {
    queue defaultQueue = queue{};

    {
      buffer bufA = buffer{a, range{dataSize}};
      buffer bufB = buffer{b, range{dataSize}};
      buffer bufR = buffer{r, range{dataSize}};

      defaultQueue.submit([&](sycl::handler& cgh) {
        accessor accA = accessor{bufA, cgh, read_only};
        accessor accB = accessor{bufB, cgh, read_only};
        accessor accR = accessor{bufR, cgh, write_only};

        cgh.parallel_for(
            range{dataSize},
            [=](id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
      });
    }  // Synchronize and copy-back

    defaultQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  SYCLACADEMY_ASSERT_EQUAL(r, [](size_t i) { return i * 2; });
}


void test_buffer_host_accessor() {
  constexpr size_t dataSize = 1024;

  int a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = i;
    b[i] = i;
    r[i] = 0;
  }

  try {
    queue defaultQueue = queue{};

    {
      buffer bufA = buffer{a, range{dataSize}};
      buffer bufB = buffer{b, range{dataSize}};
      buffer bufR = buffer{r, range{dataSize}};

      defaultQueue.submit([&](sycl::handler& cgh) {
        accessor accA = accessor{bufA, cgh, read_only};
        accessor accB = accessor{bufB, cgh, read_only};
        accessor accR = accessor{bufR, cgh, write_only};

        cgh.parallel_for(
            range{dataSize},
            [=](sycl::id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
      });

      defaultQueue.wait();  // Synchronize

      {
        host_accessor hostAccR = bufR.get_host_access(read_only);  // Copy-to-host

        SYCLACADEMY_ASSERT_EQUAL(hostAccR, [](size_t i) { return i * 2; });
      }

    }  // Copy-back

    defaultQueue.throw_asynchronous();
  } catch (const exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }
}

int main() {
  test_buffer_event_wait();
  test_buffer_queue_wait();
  test_buffer_buffer_destruction();
  test_buffer_host_accessor();
}
