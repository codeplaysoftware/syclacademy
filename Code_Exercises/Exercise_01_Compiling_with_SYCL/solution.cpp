/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#if defined(SYCL_LANGUAGE_VERSION) && defined(__INTEL_LLVM_COMPILER)
#include <CL/sycl.hpp>
#else
#include <SYCL/sycl.hpp>
#endif

TEST_CASE("empty_sycl_source_file", "compiling_with_sycl_solution") {
  REQUIRE(true);
}
