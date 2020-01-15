//------------------------------------------------------------------------------
//
// Name:       exercise_1.cpp
//
// Tutorial:    Vector addition on SYCL
//
// Author:     Codeplay May 2015
//
//------------------------------------------------------------------------------

#include "SYCL/sycl.hpp"

#include <iostream>

using namespace cl::sycl;

int main(void) {
  //cl::sycl::float4 is a cl::sycl::vec<float,4> type, that provides OpenCL
  //vector functionality for host and device.
  //The following are 2 unary OpenCL float4 vectors and the output vector.
  float4 a = { 1.0, 1.0, 1.0, 1.0 }; //input 1
  float4 b = { 1.0, 1.0, 1.0, 1.0 }; //input 2
  float4 c = { 0.0, 0.0, 0.0, 0.0 }; //output


  //The default selector will select a device based on heuristics for the system.
  default_selector deviceSelector;
  //A different or custom selector can be used instead, e.g.
  //cpu_selector device_selector;

  //The cl::sycl::queue constructor will create a queue on the device the
  //deviceSelector will return.
  queue myQueue(deviceSelector);

  {
  // Create buffers to handle data with SYCL
  // The constructor for buffers for a raw data pointer to the data to be
  // managed is the following:
  // cl::sycl::buffer<typename T, int dimensions> (T * ptr, range<dimensions>(int range_size));
  buffer<float4,1> a_sycl(&a,range<1>(1));
  buffer<float4,1> b_sycl(&b,range<1>(1));
  buffer<float4,1> c_sycl(&c,range<1>(1));

  //Submit a command group functor for execution on a queue. This functor
  //encapsulates the kernel and the data needed for its execution.
  myQueue.submit( [&](handler& cgh) {

      /* Request access from the buffers for access to the data on the device.
         The different access modes are encapsulated in the enum class:
         access::mode{ read, write, read_write, discard_wirte,
        discard_read_write}
      */
      auto a_acc = a_sycl.get_access<access::mode::read>(cgh);
      auto b_acc = b_sycl.get_access<access::mode::read>(cgh);
      auto c_acc = c_sycl.get_access<access::mode::write>(cgh);

      //A kernel that is executed on one thread using NDRange(1,1,1)
      //can be enqueued using the 'single_task' API
      //single_task<typename kernel_lambda_name>([=](){});
      cgh.single_task<class vector_addition>([=]() {
        //vector addition code where the accessors of a,b,c make the vectors
        //available for calculating c = a+b;
        c_acc[0] = a_acc[0] + b_acc[0];
      });
    });

  }  // data is copied back to the host at the end of the scope

  //Simple vector swizzles are available in SYCL for the cl::sycl::vec class
  //for up to width of 4 and are defined as functions, e.g. a.xy()
  //The cl::sycl::vec class works for host as well so the same functionality
  //is available on the host application.
  std::cout << "result (c=a+b): "<< c.x() << " " << c.y() << " " << c.z() << " ";
  std::cout << c.w() << std::endl;

  return c.x();
}
