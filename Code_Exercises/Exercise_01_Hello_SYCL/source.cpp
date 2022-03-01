/*
 * SYCL Quick Reference
 * ~~~~~~~~~~~~~~~~~~~~
 *
 * // Include SYCL header
 * #include <CL/sycl.hpp>
 *
 * // Default construct a queue
 * auto q = sycl::queue{};
 *
 * // Get the queue's device
 * auto d = q.get_device();
 *
 * // Get the name of the device
 * auto dev_name = d.get_info<sycl::info::device::name>();
 *
 */

int main() {
    // Construct a queue

    // Get the device associated with queue

    // Print the device name to stdout
}


