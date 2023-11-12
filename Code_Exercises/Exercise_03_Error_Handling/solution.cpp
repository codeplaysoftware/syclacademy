/*

Licensed under a Creative Commons Attribution-ShareAlike 4.0
International License.

Code by James Reinders, originally for class at Cornell in
September 2023. Based on Exercise 15 of SYCL Academy Code
Exercises. Updated and expanded for SC23 tutorial (November
12, 2023).

Known limitations:

Crude addition of "blurred_" to front of file name won't
work if there is a directory in the path, so such runs are
rejected.

If the image is too large - the runtime may segment fault -
this code doesn't check for limits (bad, bad, bad!)

*/

//
// These control some optional code
// MYDEBUGS - is very chatty to help follow code actions
// MAKE_TASK2_PI - adds a task to a second accelerator
// BONUS_CREDIT_01 - adds a 'print Hello World' task to a
// third accelerator
//

//#define MYDEBUGS
#define MAKE_TASK2_PI
//#define BONUS_CREDIT_01
//#define SOLVE_02_USM_FOR_PI
#define SOLVE_03_MAKE_ERRRORS
#define SOLVE_03_MAKE_ERRRORS_ADD_KERNEL_ASSERT

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <sycl/sycl.hpp>

#include "image_conv.h"

inline constexpr int filterWidth = 11;
inline constexpr int halo = filterWidth / 2;

#ifdef SOLVE_03_MAKE_ERRRORS
// borrowed from figure 5-3 in book
// Our example asynchronous handler function
auto handle_async_error = [](sycl::exception_list elist) {
  for (auto &e : elist) {
    try {
      std::rethrow_exception(e);
    } catch (sycl::exception e) {
      std::cout << "Caught SYCL ASYNC exception!!\n";
    } catch (...) {
      std::cout << "Caught unknown exception in the ASYNC handler???\n";
    }
  }
};
auto second_handle_async_error = [](sycl::exception_list elist) {
  for (auto &e : elist) {
    try {
      std::rethrow_exception(e);
    } catch (sycl::exception e) {
      std::cout << "2nd Handler Caught SYCL ASYNC exception!!\n";
    } catch (...) {
      std::cout << "2nd Handler Caught the Something Went Wrong\n";
    }
  }
};
class something_when_wrong {} ;
#endif


int main(int argc, char* argv[]) {
  const char* inFile = argv[1];
  char* outFile;

#ifdef SOLVE_03_MAKE_ERRRORS
  try {
    // borrowed from Figure 5-2 in book
    sycl::buffer<int> b{sycl::range{16}};
    sycl::buffer<int> b2{b, sycl::id{8}, sycl::range{16}};
  } catch (sycl::exception e) {
    std::cout << "Caught SYCL exception: " << e.what()
              << std::endl;
  } catch (std::exception &e) {
    std::cout << "Caught std exception: " << e.what() << "\n";
  } catch (...) {
    std::cout << "Caught unknown exception\n";
  }
  
  try {
    sycl::queue quick_queue;
    // synchronous error
    // adapted from https://developer.codeplay.com/products/computecpp/ce/2.11.0/guides/sycl-guide/error-handling
    sycl::event e2c =
      quick_queue.submit([&](sycl::handler& cgh2c) {
	auto err_range = sycl::nd_range<1>(sycl::range<1>(1), sycl::range<1>(10));
        cgh2c.parallel_for(err_range, [=](sycl::nd_item<1>) {});
      });
  } catch (sycl::exception e) {
    std::cout << "Another SYCL exception caught: " << e.what()
              << std::endl;
  } catch (std::exception &e) {
    std::cout << "Another? Caught std exception: " << e.what() << "\n";
  } catch (...) {
    std::cout << "Another? Caught unknown exception\n";
  }


  try {
    sycl::queue quick_queue( second_handle_async_error );
    // asynchronous error
    // adapted from 5-3 in book
    sycl::event e2d =
        quick_queue.submit([&](sycl::handler& cgh2d) {
	  cgh2d.host_task([]() {
	    throw( something_when_wrong{} );
	  });
	});
  } catch (sycl::exception e) {
    std::cout << "Host task SYCL exception caught: " << e.what()
              << std::endl;
  } catch (std::exception &e) {
    std::cout << "Host task Caught std exception: " << e.what() << "\n";
  } catch (...) {
    std::cout << "Host task Caught unknown exception\n";
  }
#endif

  //
  // require and parse a single file name
  // very simple <program name> <image file name>
  // output is simply the filename prepended with 'blurred_'
  //

  if (argc == 2) {
    if (strchr(inFile, '/') || strchr(inFile, '\\')) {
      std::cerr
          << "Sorry, filename cannot include a path.\n";
      exit(1);
    }
    const char* prefix = "blurred_";
    size_t len1 = strlen(inFile);
    size_t len2 = strlen(prefix);
    outFile =
        (char*)malloc((len1 + len2 + 1) * sizeof(char));
    strcpy(outFile, prefix);
    strcpy(outFile + 8, inFile);
#ifdef MYDEBUGS
    std::cout << "Input file: " << inFile
              << "\nOutput file: " << outFile << "\n";
#endif
  } else {
    std::cerr << "Usage: " << argv[0] << " imagefile\n";
    exit(1);
  }

  auto inImage = util::read_image(inFile, halo);

  auto outImage = util::allocate_image(inImage.width(),
                                       inImage.height(),
                                       inImage.channels());

  // The image convolution support code provides a
  // `filter_type` enum which allows us to choose between
  // `identity` and `blur`. The utility for generating the
  // filter data; `generate_filter` takes a `filter_type`
  // and a width.

  auto filter = util::generate_filter(
      util::filter_type::blur, filterWidth,
      inImage.channels());

//
// This code tries to grab up to 100 (MAXDEVICES) GPUs.
// If there are no GPUs, it will get a default device.
//
// The net result is an array that contains 100 devices,
// so the rest of the program can access using modulo
// math using howmany_devices
//
#define MAXDEVICES 100

  sycl::queue myQueues[MAXDEVICES];
  int howmany_devices = 0;
  try {
    auto P = sycl::platform(sycl::gpu_selector_v);
    auto RootDevices = P.get_devices();
    // auto C = sycl::context(RootDevices);
    for (auto& D : RootDevices) {
#ifdef SOLVE_03_MAKE_ERRRORS
      myQueues[howmany_devices++] = sycl::queue(
          D, handle_async_error, sycl::property::queue::enable_profiling{});
#else
      myQueues[howmany_devices++] = sycl::queue(
          D, sycl::property::queue::enable_profiling{});
#endif
      if (howmany_devices >= MAXDEVICES) break;
    }
  } catch (sycl::exception e) {
    howmany_devices = 1;
    myQueues[0] = sycl::queue(
        sycl::property::queue::enable_profiling{});
  }

#ifdef DEBUGDUMP
  for (int i = 0; i < howmany_devices; ++i) {
    std::cout
        << "Device: "
        << myQueues[i]
               .get_device()
               .get_info<sycl::info::device::name>()
        << " MaxComputeUnits: "
        << myQueues[i]
               .get_device()
               .get_info<
                   sycl::info::device::max_compute_units>();
    if (myQueues[i].get_device().has(
            sycl::aspect::ext_intel_device_info_uuid)) {
      auto UUID =
          myQueues[i]
              .get_device()
              .get_info<
                  sycl::ext::intel::info::device::uuid>();
      char foo[1024];
      sprintf(
          foo,
          "\nUUID = "
          "%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u",
          UUID[0], UUID[1], UUID[2], UUID[3], UUID[4],
          UUID[5], UUID[6], UUID[7], UUID[8], UUID[9],
          UUID[10], UUID[11], UUID[12], UUID[13], UUID[14],
          UUID[15]);
      std::cout << foo;
    }
    std::cout << "\n";
  }
#endif

  try {
    sycl::queue myQueue1 = myQueues[0];

#ifdef MYDEBUGS
    std::cout << "Running on "
              << myQueue1.get_device()
                     .get_info<sycl::info::device::name>();
#ifdef SYCL_EXT_INTEL_DEVICE_INFO
#if SYCL_EXT_INTEL_DEVICE_INFO >= 2
    if (myQueue1.get_device().has(
            sycl::aspect::ext_intel_device_info_uuid)) {
      auto UUID =
          myQueue1.get_device()
              .get_info<
                  sycl::ext::intel::info::device::uuid>();
      char foo[1024];
      sprintf(
          foo,
          "\nUUID = "
          "%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u",
          UUID[0], UUID[1], UUID[2], UUID[3], UUID[4],
          UUID[5], UUID[6], UUID[7], UUID[8], UUID[9],
          UUID[10], UUID[11], UUID[12], UUID[13], UUID[14],
          UUID[15]);
      std::cout << foo;
    }
#endif
#endif
    std::cout << "\n";
#endif

#ifdef MAKE_TASK2_PI
    sycl::queue myQueue2 =
        myQueues[(howmany_devices > 1) ? 1 : 0];
    std::cout << "Second queue is running on "
              << myQueue2.get_device()
                     .get_info<sycl::info::device::name>();
#ifdef SYCL_EXT_INTEL_DEVICE_INFO
#if SYCL_EXT_INTEL_DEVICE_INFO >= 2
    if (myQueue2.get_device().has(
            sycl::aspect::ext_intel_device_info_uuid)) {
      auto UUID =
          myQueue2.get_device()
              .get_info<
                  sycl::ext::intel::info::device::uuid>();
      char foo[1024];
      sprintf(
          foo,
          "\nUUID = "
          "%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u",
          UUID[0], UUID[1], UUID[2], UUID[3], UUID[4],
          UUID[5], UUID[6], UUID[7], UUID[8], UUID[9],
          UUID[10], UUID[11], UUID[12], UUID[13], UUID[14],
          UUID[15]);
      std::cout << foo;
    }
#endif
#endif
    std::cout << "\n";
#endif

#ifdef MYDEBUGS
    auto t1 =
        std::chrono::steady_clock::now();  // Start timing
#endif

#ifdef SOLVE_03_MAKE_ERRRORS_ADD_KERNEL_ASSERT
    // uses a useful DPC++ extension - we should encourage this into the standard
    // asynchronous error
    sycl::event e2b =
        myQueue2.submit([&](sycl::handler& cgh2b) {
          cgh2b.single_task([=]() {
	    assert(0 && "Die now");
	  });
	});
    // unfortunately - no drivers for hardware on Intel Developer Cloud
    // currently support this (as of November 10, 2023) - "coming soon"
    // this check will print a note mentioning the lack of support
    if (! myQueue2.get_device().has(sycl::aspect::ext_oneapi_native_assert)) {
      std::cout << "The assert extension to support in a kernel is not available for this device - so no async was thrown.\n";
    }
#endif

    //
    // This "second task" is very serial - and is here as
    // a demostration, and definitely a bottleneck because
    // it is serial.
    //

#ifdef MAKE_TASK2_PI
#ifdef SOLVE_02_USM_FOR_PI
    auto d4 = (int *)sycl::malloc_shared( sizeof(int)*200, myQueue2 );
#else
    std::array<int, 200> d4;
#endif
    // inspired and based upon:
    // https://cs.uwaterloo.ca/~alopez-o/math-faq/mathtext/node12.html
    // and
    // https://crypto.stanford.edu/pbc/notes/pi/code.html
    // (retrieved September 13, 2023)

#ifndef SOLVE_02_USM_FOR_PI
    sycl::buffer outD4(d4);
#endif
  sycl::event e2 =
        myQueue2.submit([&](sycl::handler& cgh2) {
#ifdef SOLVE_02_USM_FOR_PI
  #define outAccessor d4
#else
          auto outAccessor =
              outD4.get_access<sycl::access::mode::write>(
                  cgh2);
#endif
          cgh2.single_task([=]() {
            int r[2800 + 1];
            int i, k;
            int b, d;
            int c = 0;
            int hold = 0;

            for (i = 0; i < 2800; i++) {
              r[i] = 2000;
            }
            r[2800] = 0;

            for (k = 2800; k > 0; k -= 14) {
              d = 0;

              i = k;
              for (;;) {
                d += r[i] * 10000;
                b = 2 * i - 1;

                r[i] = d % b;
                d /= b;
                i--;
                if (i == 0) break;
                d *= i;
              }
              outAccessor[hold++] = c + d / 10000;
              c = d % 10000;
            }
          });
        });
#endif

    //
    // Bonus activity for Exercise 01.
    // This "third task" is another demostration of
    // a single task and printing using sycl::stream.
    //

#ifdef BONUS_CREDIT_01
    sycl::queue myQueue3 =
        myQueues[(howmany_devices > 2) ? 2 : 0];
    std::cout << "Second queue is running on "
              << myQueue2.get_device()
                     .get_info<sycl::info::device::name>();
#ifdef SYCL_EXT_INTEL_DEVICE_INFO
#if SYCL_EXT_INTEL_DEVICE_INFO >= 2
    if (myQueue2.get_device().has(
            sycl::aspect::ext_intel_device_info_uuid)) {
      auto UUID =
          myQueue2.get_device()
              .get_info<
                  sycl::ext::intel::info::device::uuid>();
      char bar[1024];
      sprintf(
          bar,
          "\nUUID = "
          "%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u.%u",
          UUID[0], UUID[1], UUID[2], UUID[3], UUID[4],
          UUID[5], UUID[6], UUID[7], UUID[8], UUID[9],
          UUID[10], UUID[11], UUID[12], UUID[13], UUID[14],
          UUID[15]);
      std::cout << bar;
    }
#endif
#endif
    sycl::event e3 =
        myQueue2.submit([&](sycl::handler& cgh3) {
          auto os = sycl::stream{128, 128, cgh3};
          cgh3.single_task(
              [=]() { os << "Hello World!\n"; });
        });
#endif

    auto inImgWidth = inImage.width();
    auto inImgHeight = inImage.height();
    auto channels = inImage.channels();
    auto filterWidth = filter.width();
    auto halo = filter.half_width();

    auto globalRange = sycl::range(inImgWidth, inImgHeight);
    auto localRange = sycl::range(1, 32);
    auto ndRange = sycl::nd_range(globalRange, localRange);

    auto inBufRange = sycl::range(inImgHeight + (halo * 2),
                                  inImgWidth + (halo * 2)) *
                      sycl::range(1, channels);
    auto outBufRange =
        sycl::range(inImgHeight, inImgWidth) *
        sycl::range(1, channels);

    auto filterRange =
        filterWidth * sycl::range(1, channels);

#ifdef MYDEBUGS
    std::cout << "inImgWidth: " << inImgWidth
              << "\ninImgHeight: " << inImgHeight
              << "\nchannels: " << channels
              << "\nfilterWidth: " << filterWidth
              << "\nhalo: " << halo << "\n";
#endif

    // Always good to limit scope of accessors,
    // so a good SYCL program will introduce a scope before
    // defining buffers.
    // Remember: While a buffer exists, the data it points
    // to should ONLY be accessed with an accessor. That
    // goes for the host just as much as the device.

    {
      auto inBuf = sycl::buffer{inImage.data(), inBufRange};
      auto outBuf = sycl::buffer<float, 2>{outBufRange};
      auto filterBuf =
          sycl::buffer{filter.data(), filterRange};
      outBuf.set_final_data(outImage.data());

      sycl::event e1 = myQueue1.submit([&](sycl::handler&
                                               cgh1) {
        sycl::accessor inAccessor{inBuf, cgh1,
                                  sycl::read_only};
        sycl::accessor outAccessor{outBuf, cgh1,
                                   sycl::write_only};
        sycl::accessor filterAccessor{filterBuf, cgh1,
                                      sycl::read_only};

        cgh1.parallel_for(ndRange, [=](sycl::nd_item<2>
                                           item) {
          auto globalId = item.get_global_id();
          globalId = sycl::id{globalId[1], globalId[0]};

          auto channelsStride = sycl::range(1, channels);
          auto haloOffset = sycl::id(halo, halo);
          auto src =
              (globalId + haloOffset) * channelsStride;
          auto dest = globalId * channelsStride;

          // 100 is a hack - so the dim is not dynamic
          float sum[/* channels */ 100];
          assert(channels < 100);

          for (size_t i = 0; i < channels; ++i) {
            sum[i] = 0.0f;
          }

          for (int r = 0; r < filterWidth; ++r) {
            for (int c = 0; c < filterWidth; ++c) {
              auto srcOffset = sycl::id(
                  src[0] + (r - halo),
                  src[1] + ((c - halo) * channels));
              auto filterOffset = sycl::id(r, c * channels);

              for (int i = 0; i < channels; ++i) {
                auto channelOffset = sycl::id(0, i);
                sum[i] +=
		  inAccessor[srcOffset + channelOffset] *
		  filterAccessor[filterOffset +
                                   channelOffset];
              }
            }
          }

          for (size_t i = 0; i < channels; ++i) {
            outAccessor[dest + sycl::id{0, i}] = sum[i];
          }
        });
      });

      myQueue1.wait_and_throw();

//
// Show very detailed and precise profiling information
// that reflects time on the actual accelerator.
// Of course, wall clock time matters a great deal-
// however the device time is very valuable when focused
// on coding and optimizing the kernel (runs on
// accelerator).
//
#ifdef MYDEBUGS
      // Timing code is from our book (2nd edition) -
      // read section on profiling in
      // Chapter 13 that includes figures 13-6 through 13-8.

      double time1A =
          (e1.template get_profiling_info<
               sycl::info::event_profiling::command_end>() -
           e1.template get_profiling_info<
               sycl::info::event_profiling::
                   command_start>());
      auto t2 =
          std::chrono::steady_clock::now();  // Stop timing
      double time1B =
          (std::chrono::duration_cast<
               std::chrono::microseconds>(t2 - t1)
               .count());

      std::cout
          << "profiling: Operation completed on device1 in "
          << time1A << " nanoseconds (" << time1A / 1.0e9
          << " seconds)\n";
      std::cout
          << "chrono: Operationd completed on device1 in "
          << time1B * 1000 << " nanoseconds ("
          << time1B * 1000 / 1.0e9 << " seconds)\n";
      std::cout << "chrono more than profiling by "
                << (time1B * 1000 - time1A)
                << " nanoseconds ("
                << (time1B * 1000 - time1A) / 1.0e9
                << " seconds)\n";

#ifdef MAKE_TASK2_PI
      e2.wait();  // make sure all digits are done being
                  // computed
#ifdef SOLVE_02_USM_FOR_PI
  #define myD4 d4
#else
      sycl::host_accessor myD4(
          outD4);  // the scope of the buffer continues - so
                   // we must not use d4[] directly
#endif
      std::cout << "First 800 digits of pi: ";
      for (int i = 0; i < 200; ++i) printf("%.4d", myD4[i]);
      std::cout << "\n";

      double time2A =
          (e2.template get_profiling_info<
               sycl::info::event_profiling::command_end>() -
           e2.template get_profiling_info<
               sycl::info::event_profiling::
                   command_start>());
      std::cout
          << "profiling: Operation completed on device2 in "
          << time2A << " nanoseconds (" << time2A / 1.0e9
          << " seconds)\n";
#endif
#endif
    }
  } catch (sycl::exception e) {
    std::cout << "Big TRY clause - Exception caught: " << e.what()
              << std::endl;
  } catch (std::exception &e) {
    std::cout << "Big TRY clause - Caught std exception: " << e.what() << "\n";
  } catch (...) {
    std::cout << "Big TRY clause - Caught unknown exception\n";
  }

  util::write_image(outImage, outFile);
}
