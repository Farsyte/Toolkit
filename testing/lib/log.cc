#include "testing_internal.h"

#include <string>
using std::string;

#include <iostream>
using std::ostream;
using std::endl;

/** Start a new Test Log.
 *
 * Can immediately generate XML header and enter the `testsuites` entity.
 */
Log::Log(ostream &s, string const &n)
    : out       (s)
    , curr      (0)
    , suites    (0)
    , tests     (0)
    , failed_tests      (0)
    , skipped_tests     (0)
    , errored_tests     (0)
    , total_fails       (0)
    , total_skips       (0)
    , total_errors      (0)
{
    out << "<?xml version=" << sq("1.0") << " encoding=" << sq("UTF-8") << "?>" << endl;
    out << "<testsuites name=" << sq(n) << ">" << endl;
}

/** Finish the Test Log.
 * Need to exit the `testsuites` entity.
 */
Log::~Log()
{
    CHECK_OOPS(NULL == curr, "Log dtor: I still have an open Suite.");
    out << "</testsuites>" << endl;
}
