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
using std::setw;

int case_compare(
  Test &t, string const &title,
  double x, double y, double z,
  Position const &r)
{

  t << title << endl
    << "  expected: "
    << setw(16) << x
    << setw(16) << y
    << setw(16) << z
    << endl
    << "  observed: "
    << setw(16) << r(1)
    << setw(16) << r(2)
    << setw(16) << r(3)
    << endl;
  if ((x == r(1)) && (y == r(2)) && (z == r(3)))
    return 0;
  t.fail(title + " failed");
  return 1;
}

int test_matrix_position_ctor(Suite &s) {

  Test t(s, "Constructors and Access");

  Position D;
  Position X {1,0,0};
  Position Y {0,1,0};
  Position Z {0,0,1};

  return 0
    + case_compare(t, "Default initialized to Zero", 0, 0, 0, D)
    + case_compare(t, "X Axis Initialization", 1, 0, 0, X)
    + case_compare(t, "Y Axis Initialization", 0, 1, 0, Y)
    + case_compare(t, "Z Axis Initialization", 0, 0, 1, Z)
    ;
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
