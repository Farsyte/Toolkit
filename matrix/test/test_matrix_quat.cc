#include "matrix.hh"
#include "testing.hh"

#include <fstream>

#include <assert.h>

using Farsyte::Testing::Log;
using Farsyte::Testing::Suite;
using Farsyte::Testing::Test;

using Farsyte::Matrix::Quat;
using Farsyte::Matrix::TriVec;

using std::ofstream;
using std::cerr;
using std::endl;
using std::setw;

static int test_matrix_quat_ctor_access(Suite &s) {
    int ec = 0;

    {
        Test t(s, "Default Constructor");
        const Quat Q;
        ec += t.eq(Q.scalar(), 0, "Scalar part of Quat::Quat()");
        ec += t.eq(Q.vector(), TriVec{0, 0, 0}, "Scalar part of Quat::Quat()");
    }
    {
        Test t(s, "Quat{0,{0,0,0}}");
        const Quat Q{0, {0, 0, 0}};
        ec += t.eq(Q.scalar(), 0, "Scalar part of Quat{0,{0,0,0}}");
        ec += t.eq(Q.vector(), TriVec{0, 0, 0}, "Scalar part of Quat{0,{0,0,0}}");
    }
    {
        Test t(s, "Quat{1,{0,0,0}}");
        const Quat Q{1, {0, 0, 0}};
        ec += t.eq(Q.scalar(), 1, "Scalar part of Quat{1,{0,0,0}}");
        ec += t.eq(Q.vector(), TriVec{0, 0, 0}, "Scalar part of Quat{1,{0,0,0}}");
    }
    {
        Test t(s, "Quat{0,{1,0,0}}");
        const Quat Q{0, {1, 0, 0}};
        ec += t.eq(Q.scalar(), 0, "Scalar part of Quat{0,{1,0,0}}");
        ec += t.eq(Q.vector(), TriVec{1, 0, 0}, "Scalar part of Quat{0,{1,0,0}}");
    }
    {
        Test t(s, "Quat{0,{0,1,0}}");
        const Quat Q{0, {0, 1, 0}};
        ec += t.eq(Q.scalar(), 0, "Scalar part of Quat{0,{0,1,0}}");
        ec += t.eq(Q.vector(), TriVec{0, 1, 0}, "Scalar part of Quat{0,{0,1,0}}");
    }
    {
        Test t(s, "Quat{0,{0,0,1}}");
        const Quat Q{0, {0, 0, 1}};
        ec += t.eq(Q.scalar(), 0, "Scalar part of Quat{0,{0,0,1}}");
        ec += t.eq(Q.vector(), TriVec{0, 0, 1}, "Scalar part of Quat{0,{0,0,1}}");
    }
    {
        Test t(s, "Mutability");
        Quat Q{1, {2, 3, 4}};
        TriVec V{5, 6, 7};
        Q.vector() = V;
        Q.vector()[1] = Q.scalar();
        Q.scalar() = Q.vector()[2];
        ec += t.eq(Q.scalar(), 7, "Scalar part of modified Quat");
        ec += t.eq(Q.vector(), TriVec{5, 1, 7}, "Scalar part of modified Quat");
    }

    return ec;
}

static int test_matrix_quat(Log &log) {

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
            + test_matrix_quat_ctor_access(s);

}


/* -- ================================================================ -- */

static int test_matrix(Log &log) {
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
