#include "testing_test.hh"
#include "testing.hh"
#include "utility.hh"
#include "testing_internal.hh"

using std::endl;
using std::ostream;
using std::string;

using namespace Farsyte::Testing;
using namespace Farsyte::Utility;

/** Create a new Test within a Suite.
*
* Can immediately enter the `testcase` entity.
*
* Operation is undefined if the provided Suite is not the most
* recently constructed Suite for its associated Log.
*/
Test::Test(Suite &r, string const &n)
        : ref(r), name(n), fails(0), skips(0), errors(0) {
    CHECK_OOPS(NULL == ref.curr, "Test ctor: Suite has an open Test.");
    ref.curr = this;
    ref.tests++;
    ref.ref.tests++;
    ref << "    <testcase name=" << quoted(n) << ">" << endl;
}

/** Indicate that a Test Condition has Failed.
*
* When this function is called, a `failure` entity is
* created in the log file for this test, using the provided
* condition name as the `message` attribute (it will appear
* as the first line of expanded text).
*
* Any data sent to the test using the `<<` operator before this
* function is called is collected and presented as content within the
* failure element. It will be displayed in the expanded text box for
* the test, separated from the condition name by a blank line.
*
* Multiple failures can be logged for a single test, and each can
* have their own supporting content. Bamboo will collect all of the
* failures into a single table line, and present their supporting
* text with blank lines separating each failing case.
*/
void Test::fail(string const &c) {

#ifdef  TEST_RESULTS_ALSO_TO
  TEST_RESULTS_ALSO_TO << ref.ref.name << "|"
                       << ref.name << "|"
                       << name << "|"
                       << "FAIL: " << c << endl;
#endif/*TEST_RESULTS_ALSO_TO*/

    fails++;
    if (fails == 1)
        ref.failed_tests++;
    ref.total_fails++;
    if (fails == 1)
        ref.ref.failed_tests++;
    ref.ref.total_fails++;

    ref << "      <failure message=" << quoted(c) << ">" << endl;

    string const s = drain();
    if (s.length() > 0) {
        string const &q(htmlify(s));
        ref << q;
        if (q[q.length() - 1] != '\n')
            ref << endl;
    }

    ref << "      </failure>" << endl;
}

/** Indicate that a Test has encountered an Error.
*
* When this function is called, a `error` entity is
* created in the log file for this test, using the provided
* condition name as the `message` attribute (it will appear
* as the first line of expanded text).
*
* Any data sent to the test using the `<<` operator before this
* function is called is collected and presented as content within the
* error element. It will be displayed in the expanded text box for
* the test, separated from the condition name by a blank line.
*
* Treatment of "error" cases by Bamboo needs to be explored.
*/
void Test::error(string const &c) {

#ifdef  TEST_RESULTS_ALSO_TO
  TEST_RESULTS_ALSO_TO << ref.ref.name << "|"
                       << ref.name << "|"
                       << name << "|"
                       << "ERROR: " << c << endl;
#endif/*TEST_RESULTS_ALSO_TO*/

    errors++;
    if (errors == 1)
        ref.errored_tests++;
    ref.total_errors++;
    if (errors == 1)
        ref.ref.errored_tests++;
    ref.ref.total_errors++;

    ref << "      <error message=" << quoted(c) << ">" << endl;

    /*
    ** Include the supporting text whether Bamboo is willing
    ** to display it or not: this represents a logic error in
    ** the testing library or in the test code itself, or an
    ** error in the code under test with unanticipated and very
    ** bad effects on the testing. Anything we can do to help
    ** diagnose this is a good thing.
    */
    string const s = drain();
    if (s.length() > 0) {
        string const &q(htmlify(s));
        ref << q;
        if (q[q.length() - 1] != '\n')
            ref << endl;
    }

    ref << "      </error>" << endl;
}

/** Indicate that a Test Condition has been Skiped.
*
* When this function is called, a `skipped` entity is
* created in the log file for this test, using the provided
* condition name as the `message` attribute.
*
* Any data sent to the test using the `<<` operator before this
* function is called is collected and presented as content within the
* skipped element. It will be displayed in the expanded text box for
* the test, separated from the condition name by a blank line.
*
* Multiple skips can be logged for a single test, and each can have
* their own supporting content.  Bamboo does not report "skipped"
* condition results, but this function is retained in order to
* support other tools that might provide useful reporting about
* skipped conditions.
*/
void Test::skip(string const &c) {

#ifdef  TEST_RESULTS_ALSO_TO
  TEST_RESULTS_ALSO_TO << ref.ref.name << "|"
                       << ref.name << "|"
                       << name << "|"
                       << "skip: " << c << endl;
#endif/*TEST_RESULTS_ALSO_TO*/

    skips++;
    if (skips == 1)
        ref.skipped_tests++;
    ref.total_skips++;
    if (skips == 1)
        ref.ref.skipped_tests++;
    ref.ref.total_skips++;

    ref << "      <skipped message=" << quoted(c) << ">" << endl;

    string const s = drain();
    if (s.length() > 0) {
        string const &q(htmlify(s));
        ref << q;
        if (q[q.length() - 1] != '\n')
            ref << endl;
    }

    ref << "      </skipped>" << endl;
}

/** Indicate that a Test Condition has Passed.
*
* Currently, the XML representation of test results as pared
* by the Bamboo `JUnit` oriented parser does not make provision
* for explicitly noting a passing condition corresponding to
* a fail or skip notation; and there is no provision for
* presentation of text associated with passing conditions or
* with passing tests.
*
* This method exists in the hope that at some time in the
* future we will have a useful way to log and display the
* conditions that pass together with their supporting log
* information.
*
* For now, this *IMPLEMENTATION* will consume the text associated
* with the passing condition, so that it is not erroneously
* included in a subsequent fail, skip, or error block.
*/
void Test::pass(string const &c) {

#ifdef  TEST_RESULTS_ALSO_TO
  TEST_RESULTS_ALSO_TO << ref.ref.name << "|"
                       << ref.name << "|"
                       << name << "|"
                       << "pass: " << c << endl;
#else /*TEST_RESULTS_ALSO_TO*/
    (void) c;                      // not used
#endif/*TEST_RESULTS_ALSO_TO*/

    (void) drain();
}

/** Finish a Test.
*
* If there is any supporting text remaining in the test,
* it is appended as content for the testcase entity.
* It then leaves the `testcase` entity.
*/
Test::~Test() {
    CHECK_OOPS(this == ref.curr, "Test dtor: I am not the current Test.");
    ref.curr = 0;

#if 0
  /*
  ** If Bamboo provided us with a way to view supporting
  ** text for a test not associated with a fail or skip
  ** object, then this could be turned on.
  */
  string        const   s = drain();
  if (s.length() > 0) {
    string      const & q ( htmlify(s) );
    ref << q;
    if (q[q.length() - 1] != '\n')
      ref << endl;
  }
#endif

    ref << "    </testcase>" << endl;
}
