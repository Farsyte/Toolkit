#include "testing_internal.h"

#include <string>
using std::string;

#include <iostream>
using std::ostream;
using std::endl;


/** Create a new Test within a Suite.
 *
 * Can immediately enter the `testcase` entity.
 *
 * Operation is undefined if the provided Suite is not the most
 * recently constructed Suite for its associated Log.
 */
Test::Test(Suite &r, string const &n)
  : ref       (r)
  , fails     (0)
  , skips     (0)
  , errors    (0)
{
  CHECK_OOPS(NULL == ref.curr, "Test ctor: Suite has an open Test.");
  ref.curr = this;
  ref.tests ++;
  ref.ref.tests ++;
  ostream   & out(ref.ref.out);
  out << "    <testcase name=" << sq(n) << ">" << endl;
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

  fails ++;
  if (fails == 1)
    ref.failed_tests ++;
  ref.total_fails ++;
  if (fails == 1)
    ref.ref.failed_tests ++;
  ref.ref.total_fails ++;

  ostream   & out(ref.ref.out);

  out << "      <failure message=" << sq(c) << ">" << endl;

  string	const & s ( str() );
  if (s.length() > 0) {
    string	const & q ( hq(s) );
    out << q;
    if (q[q.length() - 1] != '\n')
      out << endl;
    this->str("");
  }

  out << "      </failure>" << endl;
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

  errors ++;
  if (errors == 1)
    ref.errored_tests ++;
  ref.total_errors ++;
  if (errors == 1)
    ref.ref.errored_tests ++;
  ref.ref.total_errors ++;

  ostream   & out(ref.ref.out);

  out << "      <error message=" << sq(c) << ">" << endl;

  string	const & s ( str() );
  if (s.length() > 0) {
    string	const & q ( hq(s) );
    out << q;
    if (q[q.length() - 1] != '\n')
      out << endl;
    this->str("");
  }

  out << "      </error>" << endl;
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

  skips ++;
  if (skips == 1)
    ref.skipped_tests ++;
  ref.total_skips ++;
  if (skips == 1)
    ref.ref.skipped_tests ++;
  ref.ref.total_skips ++;

  ostream   & out(ref.ref.out);

  out << "      <skipped message=" << sq(c) << ">" << endl;

  string	const & s ( str() );
  if (s.length() > 0) {
    string	const & q ( hq(s) );
    out << q;
    if (q[q.length() - 1] != '\n')
      out << endl;
    this->str("");
  }

  out << "      </skipped>" << endl;
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

  ostream   & out(ref.ref.out);

  string	const & s ( str() );
  if (s.length() > 0) {
    string	const & q ( hq(s) );
    out << q;
    if (q[q.length() - 1] != '\n')
      out << endl;
  }

  out << "    </testcase>" << endl;
}
