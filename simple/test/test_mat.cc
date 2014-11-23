#include "simple_mat.hh"
#include "simple_row.hh"
#include "testing.hh"

using Farsyte::Simple::Mat;
using Farsyte::Simple::R;

UT_CASE(Mat, InitCompare) {

    Mat const Zero;
    Mat const Unit(1);
    Mat const Diag(1, 2, 3);

    EXPECT_EQ(Zero, (Mat(R(0, 0, 0), R(0, 0, 0), R(0, 0, 0))));
    EXPECT_EQ(Unit, (Mat(R(1, 0, 0), R(0, 1, 0), R(0, 0, 1))));
    EXPECT_EQ(Diag, (Mat(R(1, 0, 0), R(0, 2, 0), R(0, 0, 3))));

    EXPECT_NE(Diag, Zero);
    EXPECT_NE(Diag, Unit);
    EXPECT_EQ(Diag, Diag);

    EXPECT_NE(Unit, Zero);
    EXPECT_EQ(Unit, Unit);
    EXPECT_NE(Unit, Diag);

    EXPECT_EQ(Zero, Zero);
    EXPECT_NE(Zero, Unit);
    EXPECT_NE(Zero, Diag);
}

UT_CASE(Mat, Access) {
    Mat const C(R(9, 8, 7), R(6, 5, 4), R(3, 2, 1));
    Mat M(R(9, 6, 3), R(8, 5, 2), R(7, 4, 1));

    EXPECT_EQ(M(0, 0), 9);
    EXPECT_EQ(M(1, 2), 2);
    M(2, 2) = 0;
    M(2, 1) = C(2, 2);
    EXPECT_EQ(M, (Mat(R(9, 6, 3), R(8, 5, 2), R(7, 1, 0))));
}

UT_CASE(Mat, Add) {
    Mat const I(R(33, 42, 59), R(68, 56, 22), R(34, 12, 30));
    Mat A(R(3233, 2142, 4259), R(6804, 2256, 5622), R(3412, 1272, 3028));

    EXPECT_EQ(I, (Mat(R(33, 42, 59), R(68, 56, 22), R(34, 12, 30))));
    EXPECT_EQ(A += I, (Mat(R(3266, 2184, 4318), R(6872, 2312, 5644), R(3446, 1284, 3058))));
    EXPECT_EQ(A, (Mat(R(3266, 2184, 4318), R(6872, 2312, 5644), R(3446, 1284, 3058))));
    EXPECT_EQ(A + I, (Mat(R(3299, 2226, 4377), R(6940, 2368, 5666), R(3480, 1296, 3088))));
    EXPECT_EQ(A + (-I), (Mat(R(3233, 2142, 4259), R(6804, 2256, 5622), R(3412, 1272, 3028))));
}

UT_CASE(Mat, Sub) {
    Mat const I(R(33, 42, 59), R(68, 56, 22), R(34, 12, 30));
    Mat A(R(3299, 2226, 4377), R(6940, 2368, 5666), R(3480, 1296, 3088));

    EXPECT_EQ(I, (Mat(R(33, 42, 59), R(68, 56, 22), R(34, 12, 30))));
    EXPECT_EQ(A -= I, (Mat(R(3266, 2184, 4318), R(6872, 2312, 5644), R(3446, 1284, 3058))));
    EXPECT_EQ(A, (Mat(R(3266, 2184, 4318), R(6872, 2312, 5644), R(3446, 1284, 3058))));
    EXPECT_EQ(A - I, (Mat(R(3233, 2142, 4259), R(6804, 2256, 5622), R(3412, 1272, 3028))));
    EXPECT_EQ(A - (-I), (Mat(R(3299, 2226, 4377), R(6940, 2368, 5666), R(3480, 1296, 3088))));
}

UT_CASE(Mat, Mul) {
    Mat i(R(1, 0, 0), R(0, 1, 0), R(0, 0, 1));
    Mat a(R(12, 27, 49), R(59, 21, 50), R(18, 34, 55));
    Mat b(R(28, 16, 11), R(53, 37, 42), R(40, 31, 25));

    EXPECT_EQ(i * i, (Mat(R(1, 0, 0), R(0, 1, 0), R(0, 0, 1))));

    EXPECT_EQ(i * a, (Mat(R(12, 27, 49), R(59, 21, 50), R(18, 34, 55))));
    EXPECT_EQ(a * i, (Mat(R(12, 27, 49), R(59, 21, 50), R(18, 34, 55))));

    EXPECT_EQ(i * b, (Mat(R(28, 16, 11), R(53, 37, 42), R(40, 31, 25))));
    EXPECT_EQ(b * i, (Mat(R(28, 16, 11), R(53, 37, 42), R(40, 31, 25))));

    EXPECT_EQ(a * b, (Mat(R(3727, 2710, 2491), R(4765, 3271, 2781), R(4506, 3251, 3001))));
    EXPECT_EQ(b * a, (Mat(R(1478, 1466, 2777), R(3575, 3636, 6757), R(2759, 2581, 4885))));
}

UT_CASE(Mat, Scale) {
    Mat A(R(3297, 2226, 4377), R(6930, 2364, 5664), R(3480, 1296, 3090));
    Mat const C(R(28, 42, 56), R(70, 56, 21), R(28, 14, 28));

    EXPECT_EQ(A *= 2, (Mat(R(6594, 4452, 8754), R(13860, 4728, 11328), R(6960, 2592, 6180))));
    EXPECT_EQ(C * 2, (Mat(R(56, 84, 112), R(140, 112, 42), R(56, 28, 56))));
    EXPECT_EQ(3 * C, (Mat(R(84, 126, 168), R(210, 168, 63), R(84, 42, 84))));
    EXPECT_EQ(C / 7, (Mat(R(4, 6, 8), R(10, 8, 3), R(4, 2, 4))));
    EXPECT_EQ(A /= 3, (Mat(R(2198, 1484, 2918), R(4620, 1576, 3776), R(2320, 864, 2060))));
}
