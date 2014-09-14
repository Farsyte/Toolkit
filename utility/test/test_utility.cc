#include "testing.h"
#include "utility.h"

using Farsyte::Testing::Log;
using Farsyte::Testing::Suite;
using Farsyte::Testing::Test;
using Farsyte::Testing::Oops;

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

static int case_compare(
  Test &t, string const &title,
  string const &exp,
  string const &act)
{
  char  const   qc = '"';
  t << title << endl
    << "  expected: " << qc << exp << qc << endl
    << "  observed: " << qc << act << qc << endl;
  if (act == exp) {
    t.pass(title);
    return 0;
  } else {
    t.fail(title + " failed");
    return 1;
  }
}

int test_utility_literal_char(Suite &s) {
  char  const   sq = '\'';
  char  const   dq = '"';
  char  const   bs = '\\';

  Test t(s, "literal(char)");

  return 0
    + case_compare(t, "Encoding a blank char for a literal", " ", literal(' '))
    + case_compare(t, "Encoding a letter char for a literal", "m", literal('m'))
    + case_compare(t, "Encoding a digit char for a literal", "5", literal('5'))
    + case_compare(t, "Encoding a star char for a literal", "*", literal('*'))
    + case_compare(t, "Encoding a backslash char for a literal", "\\\\", literal(bs))
    + case_compare(t, "Encoding a single quote char for a literal", "\\'", literal(sq))
    + case_compare(t, "Encoding a double quote char for a literal", "\\\"", literal(dq))
    ;
}

int test_utility_literal_str(Suite &s) {

  Test t(s, "literal(string)");

  return 0
    + case_compare(t, "Encoding the empty string", "", literal(""))
    + case_compare(t, "Encoding a single blank", " ", literal(" "))
    + case_compare(t, "Encoding some text", "thx-1152", literal("thx-1152"))
    + case_compare(t, "Encoding some nasty text",
                   "\\t\\'.\\', \\\".\\\", and \\\\ ...\\n",
                   literal("\t'.', \".\", and \\ ...\n"))
    ;
}

int test_utility_literal(Log &log) {

  /*
  ** There is no Literal class, but there are some
  ** functions that work with Literals.
  */
  Suite               s(log, "Farsyte::Utility::Literal");

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially independent;
  ** use boolean '|' operator to run multiple tests
  ** and return fail if any failed, after running all.
  */

  return 0
    + test_utility_literal_char(s)
    + test_utility_literal_str(s)
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
    + test_utility_literal(log)
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