#include "testing.h"
#include "utility.h"
#include "matrix.h"

using Farsyte::Testing::Log;
using Farsyte::Testing::Suite;
using Farsyte::Testing::Test;
using Farsyte::Testing::Oops;

using Farsyte::Matrix::Position;


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
  double exp,
  double act)
{
  t << title << endl
    << "  expected: " << exp << endl
    << "  observed: " << act << endl;
  if (act == exp)
    return 0;
  t.fail(title + " failed");
  return 1;
}

int test_matrix_position_ctor(Suite &s) {

  Test t(s, "Position and operator(i,j)");

  int ec = 0;

  Position D;
  Position X {1,0,0};
  Position Y {0,1,0};
  Position Z {0,0,1};
  Position M {4,5,6};
  Position C (M);

  ec += case_compare(t, "X initialized", 0, D(1));
  ec += case_compare(t, "Y initialized", 0, D(2));
  ec += case_compare(t, "Z initialized", 0, D(3));

  ec += case_compare(t, "X.x initialized", 1, X(1));
  ec += case_compare(t, "X.y initialized", 0, X(2));
  ec += case_compare(t, "X.z initialized", 0, X(3));

  ec += case_compare(t, "Y.x initialized", 0, Y(1));
  ec += case_compare(t, "Y.y initialized", 1, Y(2));
  ec += case_compare(t, "Y.z initialized", 0, Y(3));

  ec += case_compare(t, "Z.x initialized", 0, Z(1));
  ec += case_compare(t, "Z.y initialized", 0, Z(2));
  ec += case_compare(t, "Z.z initialized", 1, Z(3));

  ec += case_compare(t, "M.x initialized", 4, M(1));
  ec += case_compare(t, "M.y initialized", 5, M(2));
  ec += case_compare(t, "M.z initialized", 6, M(3));

  ec += case_compare(t, "C.x initialized", 4, C(1));
  ec += case_compare(t, "C.y initialized", 5, C(2));
  ec += case_compare(t, "C.z initialized", 6, C(3));

  return ec;
}

int test_matrix_position(Log &log) {

  /*
  ** Tests specific to the Position Class
  */
  Suite               s(log, "Farsyte::Matrix::Position");

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** the subtests of this unit are sequentially independent;
  ** use boolean '|' operator to run multiple tests
  ** and return fail if any failed, after running all.
  */

  return 0
    + test_matrix_position_ctor(s)
    ;

}

int test_matrix(Log &log) {
  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially independent;
  ** use boolean '|' operator to run multiple tests
  ** and return fail if any failed, after running all.
  */
  return 0
    + test_matrix_position(log)
    ;
}

int main(void) {

  Log                 log(cout, "Matrix Library");

  int ec = test_matrix(log);

  if (ec)
    fprintf(stderr, "%7d FAIL test_matrix\n", ec);
  else
    fprintf(stderr, "%7d PASS test_matrix\n", ec);

  return 0;
}
