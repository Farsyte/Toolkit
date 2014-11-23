#include "testing.hh"
#include "utility.hh"
#include <iomanip>
#include <fstream>
#include <assert.h>

using Farsyte::Testing::Log;
using Farsyte::Testing::Oops;
using Farsyte::Testing::Suite;
using Farsyte::Testing::Test;
using Farsyte::Utility::literal;
using std::cout;
using std::endl;
using std::istringstream;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

UT_CASE(Utility, Version) {

    const char ** vers = Farsyte::Utility::utility_versions();

    ASSERT_NotNull(vers);
    ASSERT_NotNull(vers[0]);
    EXPECT_EQ(vers[0], string(_utility_h));

}

UT_CASE(Literal, Char) {

    char const sq = '\'';
    char const dq = '"';
    char const bs = '\\';

    EXPECT_EQ(literal(' '), " ");       // Encoding a blank char for a literal
    EXPECT_EQ(literal('m'), "m");       // Encoding a letter char for a literal
    EXPECT_EQ(literal('5'), "5");       // Encoding a digit char for a literal
    EXPECT_EQ(literal('*'), "*");       // Encoding a star char for a literal
    EXPECT_EQ(literal(bs), "\\\\");     // Encoding a backslash char for a literal
    EXPECT_EQ(literal(sq), "\\'");      // Encoding a single quote char for a literal
    EXPECT_EQ(literal(dq), "\\\"");     // Encoding a double quote char for a literal

}

UT_CASE(Literal, String) {

    EXPECT_EQ(literal(""), "");         // Encoding the empty string
    EXPECT_EQ(literal(" "), " ");       // Encoding a single blank
    EXPECT_EQ(literal("thx-1152"), "thx-1152"); // Encoding some text

    // A significantly more complex case.
    EXPECT_EQ(
        literal("\t'.', \".\", and \\ ...\n"),
        "\\t\\'.\\', \\\".\\\", and \\\\ ...\\n");

}


