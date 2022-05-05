/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

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

