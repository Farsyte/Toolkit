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
using std::cout;
using std::endl;
using std::istringstream;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

UT_CASE(Test, Ierr) {

    ostringstream oss;
    Log tl(oss, "Test Tester Log Name");
    Suite ts(tl, "Test Tester Suite Name");
    Test tc1(ts, "Test Tester Test Name 1");

    // Opening a second suite inside a Log
    // triggers an exception.

    Test *tp = 0;
    EXPECT_EX(tp = new Test(ts, "Test Tester Test Name 2"));
    if (tp) delete tp;

};

UT_CASE(Test, Init) {
    ostringstream oss;
    Log tl(oss, "Test Tester Log Name");
    Suite ts(tl, "Test Tester Suite Name");
    Test tc(ts, "Test Tester Test Name");

    EXPECT_EQ(&tc.ref, &ts);            // Test link to Suite object
    EXPECT_EQ(ts.curr, &tc);            // Suite link to Test object
    EXPECT_EQ(tl.tests, 1);             // Log count of tests incremented
    EXPECT_EQ(ts.tests, 1);             // Suite count of tests incremented
    EXPECT_EQ(tc.fails, 0);             // Test count or condition FAILs clear
    EXPECT_EQ(tc.skips, 0);             // Test count of condition SKIPs clear
    EXPECT_EQ(tc.errors, 0);            // Test count of testing ERROSs clear"
};

UT_CASE(Test, Init2) {

    ostringstream oss;
    Log tl(oss, "Test Tester Log Name");
    Suite ts(tl, "Test Tester Suite Name");
    Test(ts, "Test Tester Test Name 1");
    Test tc(ts, "Test Tester Test Name 2");

    EXPECT_EQ(&tc.ref, &ts);                                    // Test link to Suite
    EXPECT_EQ(ts.curr, &tc);                                    // Suite link to Test
    EXPECT_EQ(tl.tests, 2);                                     // Log counter of Tests
    EXPECT_EQ(ts.tests, 2);                                     // Suite counter of Tests
    EXPECT_EQ(tc.fails, 0);                                     // Test counter of FAILs
    EXPECT_EQ(tc.skips, 0);                                     // Test counter of SKIPs
    EXPECT_EQ(tc.errors, 0);                                    // Test counter of ERRORs
};

UT_CASE(Test, Init4) {

    ostringstream oss;
    Log tl(oss, "Test Tester Log Name");

    {
        Suite ts(tl, "Test Tester Suite Name 1");
        Test(ts, "Test Tester Test Name 1");
        Test(ts, "Test Tester Test Name 2");
    }

    Suite ts(tl, "Test Tester Suite Name 2");
    Test(ts, "Test Tester Test Name 1");
    Test tc(ts, "Test Tester Test Name 2");

    EXPECT_EQ(&tc.ref, &ts);                                    // Test link to Suite
    EXPECT_EQ(ts.curr, &tc);                                    // Suite link to Test
    EXPECT_EQ(tl.tests, 4);                                     // Log test counter
    EXPECT_EQ(ts.tests, 2);                                     // Suite test counter
    EXPECT_EQ(tc.fails, 0);                                     // Test counter of FAILs
    EXPECT_EQ(tc.skips, 0);                                     // Test counter of SKIPs
    EXPECT_EQ(tc.errors, 0);                                    // Test counter of ERRORs

};

UT_CASE(Test, MinimumOutput) {

    ostringstream oss;

    Log tl(oss, "Test Tester Log");
    Suite ts(tl, "Test Tester Suite Name");

    oss.str("");

    // Create and immediately destroy a Test object:
    // all we want is the net effect on the Log stream.

    (void) Test(ts, "Test Tester Test Name");

    vector<string> vos(streamlines(oss));

    ASSERT_GE(vos.size(), 1u);
    EXPECT_EQ(vos[0], "    <testcase name=\"Test Tester Test Name\">");
    ASSERT_GE(vos.size(), 2u);
    EXPECT_EQ(vos[1], "    </testcase>");
    EXPECT_EQ(vos.size(), 2u);

};

UT_CASE(Test, Fail) {

    ostringstream oss;

    Log tl(oss, "Fail Tester Log");
    Suite ts(tl, "Fail Tester Suite Name");
    Test tc(ts, "Fail Tester Test Name");

    tc.fail("Fail Tester Condition Name (before clear)");
    oss.str("");
    tc.fail("Fail Tester Condition Name");

    vector<string> vos(streamlines(oss));

    ASSERT_GE(vos.size(), 1u);
    EXPECT_EQ(vos[0], "      <failure message=\"Fail Tester Condition Name\">");
    ASSERT_GE(vos.size(), 2u);
    EXPECT_EQ(vos[1], "      </failure>");
    EXPECT_EQ(vos.size(), 2u);

    EXPECT_EQ(tc.fails, 2);                                     // Test FAILs counter
    EXPECT_EQ(tc.skips, 0);                                     // Test SKIPs counter
    EXPECT_EQ(tc.errors, 0);                                    // Test ERRORs counter

    EXPECT_EQ(ts.failed_tests, 1);                              // Suite count of Test FAILs
    EXPECT_EQ(ts.skipped_tests, 0);                             // Suite count of Test SKIPs
    EXPECT_EQ(ts.errored_tests, 0);                             // Suite count of Test ERRORs

    EXPECT_EQ(ts.total_fails, 2);                               // Suite cont of Cond FAILs
    EXPECT_EQ(ts.total_skips, 0);                               // Suite count of Cond SKIPs
    EXPECT_EQ(ts.total_errors, 0);                              // Suite count of Cond ERRORs

    EXPECT_EQ(tl.failed_tests, 1);                              // Log count of Test FAILs
    EXPECT_EQ(tl.skipped_tests, 0);                             // Log count of Test FAILs
    EXPECT_EQ(tl.errored_tests, 0);                             // Log count of Test ERRORs

    EXPECT_EQ(tl.total_fails, 2);                               // Log count of Cond FAILs
    EXPECT_EQ(tl.total_skips, 0);                               // Log count of Cond SKIPs
    EXPECT_EQ(tl.total_errors, 0);                              // Log count of Cond ERRORs

};

UT_CASE(Test, Text) {

    static const vector<string> exp = {
            Farsyte::Utility::quoted("      <failure message=\"Text Tester Condition Name\">"),
            Farsyte::Utility::quoted("Text Tester Detail Line #1"),
            Farsyte::Utility::quoted("Text Tester Detail Line #2"),
            Farsyte::Utility::quoted("Text Tester Detail Line #3"),
            Farsyte::Utility::quoted("      </failure>"),
    };

    static const vector<string> msg = {
            "open failure entity",
            "evidence line 1",
            "evidence line 2",
            "evidence line 3",
            "close failure entity"
    };

    ostringstream oss;

    Log tl(oss, "Text Tester Log");
    Suite ts(tl, "Text Tester Suite Name");
    Test tc(ts, "Text Tester Test Name");

    oss.str("");

    tc << "Text Tester Detail Line #1" << endl;
    tc << "Text Tester Detail Line #2\n";
    tc << "Text Tester Detail Line #3";

    tc.fail("Text Tester Condition Name");

    vector<string> vos(streamlines(oss));

    for (unsigned i = 0; i < exp.size(); ++i) {
        ASSERT_GE(vos.size(), i+1);
        EXPECT_EQ(vos[i], exp[i]);
    }
    EXPECT_EQ(vos.size(), exp.size());

};

UT_CASE(Test, Skip) {

    static const vector<string> exp = {
            Farsyte::Utility::quoted("      <skipped message=\"Skip Tester Condition Name\">"),
            Farsyte::Utility::quoted("Skip Tester Detail Line #1"),
            Farsyte::Utility::quoted("Skip Tester Detail Line #2"),
            Farsyte::Utility::quoted("Skip Tester Detail Line #3"),
            Farsyte::Utility::quoted("      </skipped>"),
    };
    static const vector<string> msg = {
            "open skipped entity",
            "evidence line 1",
            "evidence line 2",
            "evidence line 3",
            "close skipped entity"
    };

    ostringstream oss;

    Log tl(oss, "Skip Tester Log");
    Suite ts(tl, "Skip Tester Suite Name");
    Test tc(ts, "Skip Tester Test Name");

    tc.skip("Skip Tester Condition Name (before clear)");
    oss.str("");
    tc << "Skip Tester Detail Line #1" << endl;
    tc << "Skip Tester Detail Line #2\n";
    tc << "Skip Tester Detail Line #3";
    tc.skip("Skip Tester Condition Name");

    vector<string> vos(streamlines(oss));

    for (unsigned i = 0; i < exp.size(); ++i) {
        ASSERT_GE(vos.size(), i+1);
        EXPECT_EQ(vos[i], exp[i]);
    }
    EXPECT_GE(vos.size(), 5u);                                  // Enough XML output

    EXPECT_EQ(tc.fails, 0);                                     // Test FAILs counter
    EXPECT_EQ(tc.skips, 2);                                     // Test SKIPs counter
    EXPECT_EQ(tc.errors, 0);                                    // Test ERRORs counter

    EXPECT_EQ(ts.failed_tests, 0);                              // Suite count of Test FAILs
    EXPECT_EQ(ts.skipped_tests, 1);                             // Suite count of Test SKIPs
    EXPECT_EQ(ts.errored_tests, 0);                             // Suite count of Test ERRORs

    EXPECT_EQ(ts.total_fails, 0);                               // Suite cont of Cond FAILs
    EXPECT_EQ(ts.total_skips, 2);                               // Suite count of Cond SKIPs
    EXPECT_EQ(ts.total_errors, 0);                              // Suite count of Cond ERRORs

    EXPECT_EQ(tl.failed_tests, 0);                              // Log count of Test FAILs
    EXPECT_EQ(tl.skipped_tests, 1);                             // Log count of Test FAILs
    EXPECT_EQ(tl.errored_tests, 0);                             // Log count of Test ERRORs

    EXPECT_EQ(tl.total_fails, 0);                               // Log count of Cond FAILs
    EXPECT_EQ(tl.total_skips, 2);                               // Log count of Cond SKIPs
    EXPECT_EQ(tl.total_errors, 0);                              // Log count of Cond ERRORs

};

UT_CASE(Test, Error) {

    static const vector<string> exp = {
            Farsyte::Utility::quoted("      <error message=\"Error Tester Condition Name\">"),
            Farsyte::Utility::quoted("Error Tester Detail Line #1"),
            Farsyte::Utility::quoted("Error Tester Detail Line #2"),
            Farsyte::Utility::quoted("Error Tester Detail Line #3"),
            Farsyte::Utility::quoted("      </error>"),
    };
    static const vector<string> msg = {
            "open error entity",
            "evidence line 1",
            "evidence line 2",
            "evidence line 3",
            "close error entity"
    };

    ostringstream oss;

    Log tl(oss, "Error Tester Log");
    Suite ts(tl, "Error Tester Suite Name");
    Test tc(ts, "Error Tester Test Name");

    tc.error("Error Tester Condition Name (before clear)");
    oss.str("");
    tc << "Error Tester Detail Line #1" << endl;
    tc << "Error Tester Detail Line #2\n";
    tc << "Error Tester Detail Line #3";
    tc.error("Error Tester Condition Name");

    vector<string> vos(streamlines(oss));

    for (unsigned i = 0; i < exp.size(); ++i) {
        ASSERT_GE(vos.size(), i);
        EXPECT_EQ(vos[i], exp[i]);
    }
    EXPECT_EQ(vos.size(), 5u);                                  // No extra XML output.

    EXPECT_EQ(tc.fails, 0);                                     // Test FAILs counter
    EXPECT_EQ(tc.skips, 0);                                     // Test SKIPs counter
    EXPECT_EQ(tc.errors, 2);                                    // Test ERRORs counter

    EXPECT_EQ(ts.failed_tests, 0);                              // Suite count of Test FAILs
    EXPECT_EQ(ts.skipped_tests, 0);                             // Suite count of Test SKIPs
    EXPECT_EQ(ts.errored_tests, 1);                             // Suite count of Test ERRORs

    EXPECT_EQ(ts.total_fails, 0);                               // Suite cont of Cond FAILs
    EXPECT_EQ(ts.total_skips, 0);                               // Suite count of Cond SKIPs
    EXPECT_EQ(ts.total_errors, 2);                              // Suite count of Cond ERRORs

    EXPECT_EQ(tl.failed_tests, 0);                              // Log count of Test FAILs
    EXPECT_EQ(tl.skipped_tests, 0);                             // Log count of Test FAILs
    EXPECT_EQ(tl.errored_tests, 1);                             // Log count of Test ERRORs

    EXPECT_EQ(tl.total_fails, 0);                               // Log count of Cond FAILs
    EXPECT_EQ(tl.total_skips, 0);                               // Log count of Cond SKIPs
    EXPECT_EQ(tl.total_errors, 2);                              // Log count of Cond ERRORs

};
