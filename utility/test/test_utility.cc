#include "testing.h"
#include "utility.h"

using Farsyte::Testing::Log;
using Farsyte::Testing::Suite;
using Farsyte::Testing::Test;
using Farsyte::Testing::Oops;

using Farsyte::Utility::quote_for_lit;
using Farsyte::Utility::literal;


#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

#include <fstream>
using std::ofstream;

#include <sstream>
using std::istringstream;
using std::ostringstream;

#include <iomanip>

/** Quote a character to go into a string in the test text.
 */
string quote(char ch) {

    switch (ch) {
    case '\t': return "\\t";
    case '\n': return "\\n";
    case '"': return "\\\"";
    case '\'': return "\\\'";
    }

    if (ch < 32)
        return "";

    if (ch > 126)
        return "";

    return string(1, ch);
}

/** Quote a string to go into a string in the test text.
 */
string quote(string const & s) {
    ostringstream       oss;
    oss << '"';
    for (size_t i = 0; i < s.length(); ++i)
        oss << quote(s[i]);
    oss << '"';
    return oss.str();
}

static int case_compare(
    Test &t, string const &title,
    string const &exp,
    string const &act)
{
    t << title << endl
      << "  expected: " << quote(exp) << endl
      << "  observed: " << quote(act) << endl;
    if (act == exp)
        return 0;
    t.fail(title + " failed");
    return 1;
}

int test_utility_quote_char(Suite &s) {
    char	const	sq = '\'';
    char	const	dq = '"';
    char	const	bs = '\\';
    
    Test t(s, "quote_for_lit(char,char)");

    return 0
        + case_compare(t, "Encoding a blank for a char literal", " ", quote_for_lit(' ', sq))
        + case_compare(t, "Encoding a letter for a char literal", "m", quote_for_lit('m', sq))
        + case_compare(t, "Encoding a digit for a char literal", "5", quote_for_lit('5', sq))
        + case_compare(t, "Encoding a star for a char literal", "*", quote_for_lit('*', sq))
        + case_compare(t, "Encoding a backslash for a char literal", "\\\\", quote_for_lit(bs, sq))
        + case_compare(t, "Encoding a single quote for a char literal", "\\'", quote_for_lit(sq, sq))
        + case_compare(t, "Encoding a double quote for a char literal", "\"", quote_for_lit(dq, sq))
        + case_compare(t, "Encoding a blank for a string literal", " ", quote_for_lit(' ', dq))
        + case_compare(t, "Encoding a letter for a string literal", "m", quote_for_lit('m', dq))
        + case_compare(t, "Encoding a digit for a string literal", "5", quote_for_lit('5', dq))
        + case_compare(t, "Encoding a star for a string literal", "*", quote_for_lit('*', dq))
        + case_compare(t, "Encoding a backslash for a string literal", "\\\\", quote_for_lit(bs, dq))
        + case_compare(t, "Encoding a single quote for a string literal", "'", quote_for_lit(sq, dq))
        + case_compare(t, "Encoding a double quote for a string literal", "\\\"", quote_for_lit(dq, dq))
        ;
}

int test_utility_quote_str(Suite &s) {

    Test t(s, "quote_for_lit(string)");

    return 0
        + case_compare(t, "Encoding the empty string", "", quote_for_lit(""))
        + case_compare(t, "Encoding a single blank", " ", quote_for_lit(" "))
        + case_compare(t, "Encoding some text", "thx-1152", quote_for_lit("thx-1152"))
        + case_compare(t, "Encoding some nasty text",
                       "'.', \\\".\\\", and \\\\ ...", 
                       quote_for_lit("\t'.', \".\", and \\ ...\n"))
        ;
}

int test_utility_quote_lit(Suite &s) {

    Test t(s, "literal(string)");

    return 0
        + case_compare(t, "Encoding the empty string", "\"\"", literal(""))
        + case_compare(t, "Encoding a single blank", "\" \"", literal(" "))
        + case_compare(t, "Encoding some text", "\"thx-1152\"", literal("thx-1152"))
        + case_compare(t, "Encoding some nasty text",
                       "\"'.', \\\".\\\", and \\\\ ...\"", 
                       literal("\t'.', \".\", and \\ ...\n"))
        ;
}

int test_utility_quote(Log &log) {

    /*
    ** There is no Quote class, but there are some
    ** functions that Quote things.
    */
    Suite               s(log, "Farsyte::Utility::Quote");

    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially independent;
    ** use boolean '|' operator to run multiple tests
    ** and return fail if any failed, after running all.
    */

    return 0
        + test_utility_quote_char(s)
        + test_utility_quote_str(s)
        + test_utility_quote_lit(s)
        ;

}

int test_utility(Log &log) {
    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially independent;
    ** use boolean '|' operator to run multiple tests
    ** and return fail if any failed, after running all.
    */
    return 0
        + test_utility_quote(log)
        ;
}

int main(void) {

    Log                 log(cout, "Utility Library");

    int ec = test_utility(log);

    if (ec)
        fprintf(stderr, "%7d FAIL test_utility\n", ec);
    else
        fprintf(stderr, "%7d PASS test_utility\n", ec);

    return 0;
}
