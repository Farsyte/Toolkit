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

typedef TriVec V;

UT_CASE(Quat, CtorAccess) {
    {
        const Quat Q;
        EXPECT_EQ(Q.scalar(), 0);       // Scalar part of Quat::Quat()
        EXPECT_EQ(Q.vector(), (V(0, 0, 0))); // Scalar part of Quat::Quat()
    }
    {
        const Quat Q(0, V(0, 0, 0));
        EXPECT_EQ(Q.scalar(), 0);       // Scalar part of Quat{0,{0,0,0}}
        EXPECT_EQ(Q.vector(), (V(0, 0, 0))); // Scalar part of Quat{0,{0,0,0}}
    }
    {
        const Quat Q(1, V(0, 0, 0));
        EXPECT_EQ(Q.scalar(), 1);       // Scalar part of Quat{1,{0,0,0}}
        EXPECT_EQ(Q.vector(), (V(0, 0, 0))); // Scalar part of Quat{1,{0,0,0}}
    }
    {
        const Quat Q(0, V(1, 0, 0));
        EXPECT_EQ(Q.scalar(), 0);       // Scalar part of Quat{0,{1,0,0}}
        EXPECT_EQ(Q.vector(), (V(1, 0, 0))); // Scalar part of Quat{0,{1,0,0}}
    }
    {
        const Quat Q(0, V(0, 1, 0));
        EXPECT_EQ(Q.scalar(), 0);       // Scalar part of Quat{0,{0,1,0}}
        EXPECT_EQ(Q.vector(), (V(0, 1, 0))); // Scalar part of Quat{0,{0,1,0}}
    }
    {
        const Quat Q(0, V(0, 0, 1));
        EXPECT_EQ(Q.scalar(), 0);       // Scalar part of Quat{0,{0,0,1}}
        EXPECT_EQ(Q.vector(), (V(0, 0, 1))); // Scalar part of Quat{0,{0,0,1}}
    }
    {
        Quat Q(1, V(2, 3, 4));
        V v(5, 6, 7);
        Q.vector() = v;
        Q.vector()[1] = Q.scalar();
        Q.scalar() = Q.vector()[2];
        EXPECT_EQ(Q.scalar(), 7);       // Scalar part of modified Quat
        EXPECT_EQ(Q.vector(), (V(5, 1, 7))); // Scalar part of modified Quat
    }
}

UT_CASE(Quat, Compare) {

    Quat D;
    Quat W(1, V(0, 0, 0));
    Quat X(0, V(1, 0, 0));
    Quat Y(0, V(0, 1, 0));
    Quat Z(0, V(0, 0, 1));

    EXPECT_NE((bool)0, (bool)(D == D));                     // D == D
    EXPECT_EQ((bool)0, (bool)(D == W));                     // D == W
    EXPECT_EQ((bool)0, (bool)(D == X));                     // D == X
    EXPECT_EQ((bool)0, (bool)(D == Y));                     // D == Y
    EXPECT_EQ((bool)0, (bool)(D == Z));                     // D == Z

    EXPECT_EQ((bool)0, (bool)(W == D));                     // W == D
    EXPECT_NE((bool)0, (bool)(W == W));                     // W == W
    EXPECT_EQ((bool)0, (bool)(W == X));                     // W == X
    EXPECT_EQ((bool)0, (bool)(W == Y));                     // W == Y
    EXPECT_EQ((bool)0, (bool)(W == Z));                     // W == Z

    EXPECT_EQ((bool)0, (bool)(X == D));                     // X == D
    EXPECT_EQ((bool)0, (bool)(X == W));                     // X == W
    EXPECT_NE((bool)0, (bool)(X == X));                     // X == X
    EXPECT_EQ((bool)0, (bool)(X == Y));                     // X == Y
    EXPECT_EQ((bool)0, (bool)(X == Z));                     // X == Z

    EXPECT_EQ((bool)0, (bool)(Y == D));                     // Y == D
    EXPECT_EQ((bool)0, (bool)(Y == W));                     // Y == W
    EXPECT_EQ((bool)0, (bool)(Y == X));                     // Y == X
    EXPECT_NE((bool)0, (bool)(Y == Y));                     // Y == Y
    EXPECT_EQ((bool)0, (bool)(Y == Z));                     // Y == Z

    EXPECT_EQ((bool)0, (bool)(Z == D));                     // Z == D
    EXPECT_EQ((bool)0, (bool)(Z == W));                     // Z == W
    EXPECT_EQ((bool)0, (bool)(Z == X));                     // Z == X
    EXPECT_EQ((bool)0, (bool)(Z == Y));                     // Z == Y
    EXPECT_NE((bool)0, (bool)(Z == Z));                     // Z == Z

    EXPECT_EQ((bool)0, (bool)(D != D));                     // D != D
    EXPECT_NE((bool)0, (bool)(D != W));                     // D != W
    EXPECT_NE((bool)0, (bool)(D != X));                     // D != X
    EXPECT_NE((bool)0, (bool)(D != Y));                     // D != Y
    EXPECT_NE((bool)0, (bool)(D != Z));                     // D != Z

    EXPECT_NE((bool)0, (bool)(W != D));                     // W != D
    EXPECT_EQ((bool)0, (bool)(W != W));                     // W != W
    EXPECT_NE((bool)0, (bool)(W != X));                     // W != X
    EXPECT_NE((bool)0, (bool)(W != Y));                     // W != Y
    EXPECT_NE((bool)0, (bool)(W != Z));                     // W != Z

    EXPECT_NE((bool)0, (bool)(X != D));                     // X != D
    EXPECT_NE((bool)0, (bool)(X != W));                     // X != W
    EXPECT_EQ((bool)0, (bool)(X != X));                     // X != X
    EXPECT_NE((bool)0, (bool)(X != Y));                     // X != Y
    EXPECT_NE((bool)0, (bool)(X != Z));                     // X != Z

    EXPECT_NE((bool)0, (bool)(Y != D));                     // Y != D
    EXPECT_NE((bool)0, (bool)(Y != W));                     // Y != W
    EXPECT_NE((bool)0, (bool)(Y != X));                     // Y != X
    EXPECT_EQ((bool)0, (bool)(Y != Y));                     // Y != Y
    EXPECT_NE((bool)0, (bool)(Y != Z));                     // Y != Z

    EXPECT_NE((bool)0, (bool)(Z != D));                     // Z != D
    EXPECT_NE((bool)0, (bool)(Z != W));                     // Z != W
    EXPECT_NE((bool)0, (bool)(Z != X));                     // Z != X
    EXPECT_NE((bool)0, (bool)(Z != Y));                     // Z != Y
    EXPECT_EQ((bool)0, (bool)(Z != Z));                     // Z != Z
}
