#include "testing.h"
#include "utility.h"
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

static int test_testing_version(Log &l) {
    Suite s(l, "Farsyte::Testing::Version");
    Test t(s, "Version Comparison");

    vector<string> ver_list = Farsyte::Testing::testing_versions();
    size_t min_size = 1;
    size_t ver_size = ver_list.size();

    return 0
            || t.ge(ver_size, min_size, "version string list too short")
            || t.eq(ver_list[0], string(_testing_h), "master version string mismatch");
}

/** Verify the next entry in a string list is as expected.
*/

/** Verify that we are at the end of the string list.
*/

/** Test that Log objects have correct initial state.
*/


















static int test_testing(Log &log) {
    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially independent;
    ** use boolean '|' operator to run multiple tests
    ** and return fail if any failed, after running all.
    */
    return 0
            + test_testing_version(log);
}

int main(int argc, char **argv) {
    assert(argc > 1);
    ofstream xml(argv[1]);
    assert(xml);
    Log log(xml, "Testing Library");

    int ec = test_testing(log);

    if (ec)
        cerr << setw(7) << ec << " FAIL test_testing" << endl;
    else
        cerr << setw(7) << ec << " PASS test_testing" << endl;

    return 0;
}
