#include "testing.hh"
#include "utility.hh"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <assert.h>

using Farsyte::Testing::Log;
using Farsyte::Testing::Oops;
using Farsyte::Testing::Suite;
using Farsyte::Testing::Test;
using Farsyte::Utility::literal;
using Farsyte::Utility::quoted;
using Farsyte::Utility::streamlines;
using std::cerr;
using std::setw;
using std::cerr;
using std::cout;
using std::endl;
using std::istringstream;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

/** Test that Log objects have correct initial state.
*/
UT_CASE(Log, Init) {
    ostringstream oss;
    Log tl(oss, "Log Tester Log Name");

    // tl.out is now private, can not compare to oss.
    EXPECT_EQ(tl.curr, (void *) 0);                             // initial Suite link
    EXPECT_EQ(tl.suites, 0);                                    // initial Suite count
    EXPECT_EQ(tl.tests, 0);                                     // initial Test count
}

UT_CASE(Log, MinimumOutput) {

    ostringstream oss;

    // Create, then immediately destroy a Log,
    // in order to collect its net effect
    // on the output stream.
    (void) Log (oss, "Log Tester Log Name");

    vector<string> vos(streamlines(oss));

    ASSERT_GE(vos.size(), 1u); EXPECT_EQ(vos[0], "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    ASSERT_GE(vos.size(), 2u); EXPECT_EQ(vos[1], "<testsuites name=\"Log Tester Log Name\">");
    ASSERT_GE(vos.size(), 3u); EXPECT_EQ(vos[2], "</testsuites>");
    EXPECT_EQ(vos.size(), 3u);
}

