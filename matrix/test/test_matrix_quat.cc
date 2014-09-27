#include "matrix.hh"
#include "testing.hh"

#include <fstream>

#include <assert.h>

using Farsyte::Testing::Log;
using Farsyte::Testing::Suite;
using Farsyte::Testing::Test;

using Farsyte::Matrix::Quat;

using std::ofstream;
using std::cerr;
using std::endl;
using std::setw;

static int test_matrix_quat_ctor(Suite &s) {
    Test t(s, "Construct without Exceptions");

    Quat D;

    t.pass("Quat constructor did not throw an exception.");

    return 0
        ;
}

static int test_matrix_quat(Log & log) {

    /*
    ** Tests specific to the Quat Class
    */
    Suite s(log, "Farsyte::Matrix::Quat");

    /*
    ** return convention: 0 is success, nonzero is failure.
    ** the subtests of this unit are sequentially independent;
    ** use boolean '|' operator to run multiple tests
    ** and return fail if any failed, after running all.
    */

    return 0
            + test_matrix_quat_ctor(s)
            ;

}


/* -- ================================================================ -- */

static int test_matrix(Log & log) {
    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially independent;
    ** use boolean '|' operator to run multiple tests
    ** and return fail if any failed, after running all.
    */
    return 0
            + test_matrix_quat(log);
}

int main(void) {

    ofstream xml("test_matrix_quat_log.xml");
    assert(xml);
    Log log(xml, "Matrix Library");

    int ec = test_matrix(log);

    if (ec)
        cerr << setw(7) << ec << " FAIL test_matrix_quat" << endl;
    else
        cerr << setw(7) << ec << " PASS test_matrix_quat" << endl;

    return 0;
}
