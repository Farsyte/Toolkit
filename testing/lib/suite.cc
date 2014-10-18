#include "testing_suite.hh"
#include "testing.hh"
#include "testing_internal.hh"

#include "utility.hh"

using namespace Farsyte::Testing;
using namespace Farsyte::Utility;

using std::string;
using std::ostream;
using std::endl;

/** Start a new Test Suite.
*
* This starts a new collection of tests with a common prefix
* string. One common use is to map the string to the name of a C++
* Class being tested, where the test case name would be a specific
* API within the class.
*
* Can immediately enter the `testsuite` entity.
*
* Operation is *undefined* if a previously created Suite has been
* constructed for this log which has not yet gone out of scope.
*/
Suite::Suite(Log &r, string const &n)
        : ref(r),
          name(n),
          curr(0),
          tests(0),
          failed_tests(0),
          skipped_tests(0),
          errored_tests(0),
          total_fails(0),
          total_skips(0),
          total_errors(0) {
    CHECK_OOPS(NULL == ref.curr, "Suite ctor: Log has an open Suite.");
    ref.curr = this;
    ref.suites++;
    ref << "  <testsuite name=" << quoted(n) << ">" << endl;
}

/** Finish a Test Suite.
*
* This ends a collection of tests.
*/
Suite::~Suite() {
    CHECK_OOPS(this == ref.curr, "Suite dtor: I am not the current Suite.");
    ref.curr = 0;
    CHECK_OOPS(NULL == curr, "Suite dtor: I still have an open Suite.");
    ref << "  </testsuite>" << endl;
}
