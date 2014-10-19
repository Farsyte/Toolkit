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

UT_CASE(Testing, Version) {

    vector<string> ver_list = Farsyte::Testing::testing_versions();
    size_t min_size = 1;
    size_t ver_size = ver_list.size();

    EXPECT_GE(ver_size, min_size);                              // version string list too short
    EXPECT_EQ(ver_list[0], string(_testing_h));                 // master version string mismatch
};
