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
 * // Set up the kernel
 * q.submit([&](sycl::handler& cgh) {
 * 
 * // Set up the output stream
 * auto os = sycl::stream{128, 128, cgh};
 *
 * // Print hello world
 * cgh.single_task<hello_world>([=]() { os << "Hello World!\n"; });
 *
 * // End the kernel scope 
 * }).wait();
 */

int main() {
    // Construct a queue

    // Set up the kernel

    // Print Hello World
}

