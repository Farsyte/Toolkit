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

static int test_matrix_quat_compare(Suite &s) {
    int ec = 0;
    Quat D;
    Quat W{1, {0, 0, 0}};
    Quat X{0, {1, 0, 0}};
    Quat Y{0, {0, 1, 0}};
    Quat Z{0, {0, 0, 1}};

    {
        Test t(s, "Comparing D == ...");
        ec += t.is_T((D == D), "D == D");
        ec += t.is_F((D == W), "D == W");
        ec += t.is_F((D == X), "D == X");
        ec += t.is_F((D == Y), "D == Y");
        ec += t.is_F((D == Z), "D == Z");
    }

    {
        Test t(s, "Comparing W == ...");
        ec += t.is_F((W == D), "W == D");
        ec += t.is_T((W == W), "W == W");
        ec += t.is_F((W == X), "W == X");
        ec += t.is_F((W == Y), "W == Y");
        ec += t.is_F((W == Z), "W == Z");
    }

    {
        Test t(s, "Comparing X == ...");
        ec += t.is_F((X == D), "X == D");
        ec += t.is_F((X == W), "X == W");
        ec += t.is_T((X == X), "X == X");
        ec += t.is_F((X == Y), "X == Y");
        ec += t.is_F((X == Z), "X == Z");
    }

    {
        Test t(s, "Comparing Y == ...");
        ec += t.is_F((Y == D), "Y == D");
        ec += t.is_F((Y == W), "Y == W");
        ec += t.is_F((Y == X), "Y == X");
        ec += t.is_T((Y == Y), "Y == Y");
        ec += t.is_F((Y == Z), "Y == Z");
    }

    {
        Test t(s, "Comparing Z == ...");
        ec += t.is_F((Z == D), "Z == D");
        ec += t.is_F((Z == W), "Z == W");
        ec += t.is_F((Z == X), "Z == X");
        ec += t.is_F((Z == Y), "Z == Y");
        ec += t.is_T((Z == Z), "Z == Z");
    }

    {
        Test t(s, "Comparing D != ...");
        ec += t.is_F((D != D), "D != D");
        ec += t.is_T((D != W), "D != W");
        ec += t.is_T((D != X), "D != X");
        ec += t.is_T((D != Y), "D != Y");
        ec += t.is_T((D != Z), "D != Z");
    }

    {
        Test t(s, "Comparing W != ...");
        ec += t.is_T((W != D), "W != D");
        ec += t.is_F((W != W), "W != W");
        ec += t.is_T((W != X), "W != X");
        ec += t.is_T((W != Y), "W != Y");
        ec += t.is_T((W != Z), "W != Z");
    }

    {
        Test t(s, "Comparing X != ...");
        ec += t.is_T((X != D), "X != D");
        ec += t.is_T((X != W), "X != W");
        ec += t.is_F((X != X), "X != X");
        ec += t.is_T((X != Y), "X != Y");
        ec += t.is_T((X != Z), "X != Z");
    }

    {
        Test t(s, "Comparing Y != ...");
        ec += t.is_T((Y != D), "Y != D");
        ec += t.is_T((Y != W), "Y != W");
        ec += t.is_T((Y != X), "Y != X");
        ec += t.is_F((Y != Y), "Y != Y");
        ec += t.is_T((Y != Z), "Y != Z");
    }

    {
        Test t(s, "Comparing Z != ...");
        ec += t.is_T((Z != D), "Z != D");
        ec += t.is_T((Z != W), "Z != W");
        ec += t.is_T((Z != X), "Z != X");
        ec += t.is_T((Z != Y), "Z != Y");
        ec += t.is_F((Z != Z), "Z != Z");
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
            + test_matrix_quat_ctor_access(s)
            + test_matrix_quat_compare(s);

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
