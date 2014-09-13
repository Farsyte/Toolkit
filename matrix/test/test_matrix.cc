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

  Test t(s, "Constructor (and access)");

  Position D;
  Position X {1,0,0};
  Position Y {0,1,0};
  Position Z {0,0,1};
  Position M {4,5,6};

  return 0
    + case_compare(t, "D initialized", 0, 0, 0, D)
    + case_compare(t, "X initialized", 1, 0, 0, X)
    + case_compare(t, "Y initialized", 0, 1, 0, Y)
    + case_compare(t, "Z initialized", 0, 0, 1, Z)
    + case_compare(t, "M initialized", 4, 5, 6, M)
    ;
}

int test_matrix_position_copy(Suite &s) {

  Test t(s, "Copy Constructor");

  Position A {5,3,7};
  Position M {4,5,6};
  Position C (M);

  M = A;

  return 0
    + case_compare(t, "C copied from M", 4, 5, 6, C)
    + case_compare(t, "M copied from A", 5, 3, 7, M)
    ;

}

int test_matrix_position_add(Suite &s) {

  Test t(s, "Position Addition");

  Position A {3,2,1};
  Position B {3,5,7};

  Position S, R;

  S = (A +  B);
  R = (A += B);

  return 0
    + case_compare(t, "S gets Sum", 6, 7, 8, S)
    + case_compare(t, "A incremented by B", 6, 7, 8, A)
    + case_compare(t, "B not modified", 3, 5, 7, B)
    + case_compare(t, "R also gets A", 6, 7, 8, R)
    ;

}

int test_matrix_position_sub(Suite &s) {

  Test t(s, "Position Difference");

  Position A {4,6,8};
  Position B {3,2,1};

  Position D, R;

  D = (A -  B);
  R = (A -= B);

  return 0
    + case_compare(t, "D gets Difference", 1, 4, 7, D)
    + case_compare(t, "A incremented by B", 1, 4, 7, A)
    + case_compare(t, "B not modified", 3, 2, 1, B)
    + case_compare(t, "R also gets A", 1, 4, 7, R)
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
    + test_matrix_position_copy(s)
    + test_matrix_position_add(s)
    + test_matrix_position_sub(s)
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
