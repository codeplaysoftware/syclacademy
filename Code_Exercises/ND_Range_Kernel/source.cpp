/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

 * SYCL Quick Reference
 * ~~~~~~~~~~~~~~~~~~~~
 *
 * // Default construct a queue
 * auto q = sycl::queue{};
 *
 * // Construct an in-order queue
 * auto q = sycl::queue{sycl::default_selector_v,
 *        {sycl::property::queue::in_order{}}};
 *
 * // Declare a USM device pointer
 * auto ptr = sycl::malloc_device<T>(size, queue);
 *
 * // Do a USM memcpy
 * auto event = q.memcpy(dst_ptr, src_ptr, sizeof(T)*n);
 * // Do a USM memcpy with dependent events
 * auto event = q.memcpy(dst_ptr, src_ptr, sizeof(T)*n, {event1, event2});
 *
 * // Wait on an event
 * event.wait();
 *
 * // Wait on a queue
 * q.wait();
 *
 * // Submit work to the queue
 * auto event = q.submit([&](sycl::handler &cgh) {
 *   // COMMAND GROUP
 * });
 *
 *
 * // You can declare a parallel_for:
 * //    1. Within a command group
 *          auto event = q.submit([&](sycl::handler &cgh) {
 *            cgh.parallel_for<class mykernel>(sycl::range{n}, kernelFunc
 *          });
 * //    2. Using a shortcut to the command group handler
 *          auto event = queue.parallel_for<class mykernel>(sycl::range{n}, kernelFunc);
 * // A parallel for can be enqueued:
 * //    i:  With range:
 *              parallel_for<class mykernel>(sycl::range{n},
 *                  [=](sycl::id<1> i) { // Do something });
 * //    ii: With nd_range:
 *              parallel_for<class mykernel>(sycl::nd_range{globalRange, localRange},
 *                  [=](sycl::nd_item<1> i) { // Do something });
*/


int main () {
  constexpr size_t dataSize = 1024;

  int a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = i;
    b[i] = i;
    r[i] = 0;
  }

  // Task: parallelise the vector add kernel using nd_range
  for (int i = 0; i < dataSize; ++i) {
      if(ptrR[i] != i * 2)
	    {
		std::cout << "The results are incorrect in the first loop at iteration " << i << std::endl;
	    return 0;
		}
  }
  std::cout << "The first set of results are correct"<< std::endl;

  for (int i = 0; i < dataSize; ++i) {
    if(r[i] != i * 2)
	  {
	  std::cout << "The results are incorrect in the second loop at iteration " << i << std::endl;
	  return 0;
	  }
  }
  std::cout << "All results are correct"<< std::endl;
  return 1;
}
