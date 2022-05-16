/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("hello_world", "hello_world_source") {
<<<<<<< HEAD

  // Print "Hello World!\n"
  std::cout << "Hello World!\n";

  // Task: Have this message print from the SYCL device instead of the host
=======
  
  // Create a default SYCL queue for submitting events using sycl::queue{}
  // the slides use a GPU queue, but we recommend default queue as this 
  // will select a device for you
  // E.g. auto defaultQueue = sycl::queue{};

  // use the default queue to submit a task
  // This starts with  defaultQueue.submit(
  
  // Using sycl::stream and the single_task template function print hello world,
  // to set up a stream use 
  // auto os = sycl::stream{128, 128, cgh};
  
  // Submit the task using inside your queue.submit, see the slides for hints
  // cgh.single_task<hello_world>([=]() { os << "Hello World!\n"; });
>>>>>>> origin/isc21

  REQUIRE(true);
}
