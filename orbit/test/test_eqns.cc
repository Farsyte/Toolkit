#include "orbit.hh"
#include "testing.hh"
#include "orbit_eqns.hh"

#include <sstream>
#include <iomanip>
#include <cmath>

using std::string;
using std::vector;

namespace Farsyte {
    namespace Orbit {

static T r4(T const &t) {
    if (t < 0) return -r4(-t);
    if (t < 0.01) return r4(t*100)/100;
    static const double rf = 10000.0;
    return ((int)(t * rf + 0.5)) / rf;
}

UT_CASE(Orbit, Esum_est) {

    // sqrt_alpha = sqrt(alpha) or sqrt(-alpha)
    // X2 = X * X
    // tf = alpha * X2

    EXPECT_EQ(Esum_sel(1, 1, 0), 0);
    EXPECT_EQ(Esum_est(1, 1, 1), 0.5);

// for small pos X, Esum_est approximates Esum_pos
// for small neg X, Esum_est approximates Esum_neg
// more terms is better, until it converges.

};

// repeat for Osum


UT_CASE(Orbit, UnitCircle) {

    Orbit const O(1, 0, {1,0,0}, {0,1,0});

    EXPECT_EQ(O.mu, 1);
    EXPECT_EQ(O.n, 1);
    EXPECT_EQ(O.t0, 0);
    EXPECT_EQ(O.R0, (V{1,0,0}));
    EXPECT_EQ(O.r0, 1);
    EXPECT_EQ(O.V0, (V{0,1,0}));
    EXPECT_EQ(O.vv0, 1);
    EXPECT_EQ(O.alpha, 1);
    EXPECT_EQ(O.sqrt_alpha, 1);

    {
        Projection const P = O.at_t(0.1);
        EXPECT_EQ(&P._, &O);
        EXPECT_EQ(P.t, 0.1);
        EXPECT_EQ(P.X, 0);
    }

    {
        Projection const P = O.at_X(0.1);
        EXPECT_EQ(&P._, &O);
        EXPECT_EQ(P.X, 0.1);
        EXPECT_EQ(r4(O.Esum(P.X)), 0.004996);
        EXPECT_EQ(r4(O.Osum(P.X)), 0.000167);
        EXPECT_EQ(P.t, 0.1);
    }

};

UT_CASE(Orbit, Elliptical) {

    T const two(2);
    T const sqrt_2(sqrt(two));

    Orbit const O(2, 0, {2,0,0}, {0,1,0});

    EXPECT_EQ(O.mu, 2);
    EXPECT_EQ(r4(O.n), r4(sqrt_2));
    EXPECT_EQ(O.t0, 0);
    EXPECT_EQ(O.R0, (V{2,0,0}));
    EXPECT_EQ(O.r0, 2);
    EXPECT_EQ(O.V0, (V{0,1,0}));
    EXPECT_EQ(O.vv0, 1);
    EXPECT_EQ(O.alpha, 0.5);
    EXPECT_EQ(r4(O.sqrt_alpha), 0.7071);


    {
        Projection const P = O.at_t(0.1);
        EXPECT_EQ(&P._, &O);
        EXPECT_EQ(P.t, 0.1);
        EXPECT_EQ(P.X, 0);
    }

    {
        Projection const P = O.at_X(0.1);
        EXPECT_EQ(&P._, &O);
        EXPECT_EQ(r4(P.t), 0.1414);
        EXPECT_EQ(P.X, 0.1);
        EXPECT_EQ(r4(O.Esum(P.X)), 0.004998);
        EXPECT_EQ(r4(O.Osum(P.X)), 0.000167);
    }
};

UT_CASE(Orbit, Hyperbolic) {

    Orbit const O(1, 0, {1,0,0}, {0,2,0});

    EXPECT_EQ(O.mu, 1);
    EXPECT_EQ(O.n, 1);
    EXPECT_EQ(O.t0, 0);
    EXPECT_EQ(O.R0, (V{1,0,0}));
    EXPECT_EQ(O.r0, 1);
    EXPECT_EQ(O.V0, (V{0,2,0}));
    EXPECT_EQ(O.vv0, 4);
    EXPECT_EQ(O.alpha, -2);
    EXPECT_EQ(r4(O.sqrt_alpha), 1.4142);


    {
        Projection const P = O.at_t(0.1);
        EXPECT_EQ(&P._, &O);
        EXPECT_EQ(P.t, 0.1);
        EXPECT_EQ(P.X, 0);
    }

    {
        Projection const P = O.at_X(0.1);
        EXPECT_EQ(&P._, &O);
        EXPECT_EQ(r4(P.t), 0.1005);
        EXPECT_EQ(P.X, 0.1);
        EXPECT_EQ(r4(O.Esum(P.X)), 0.005008);
        EXPECT_EQ(r4(O.Osum(P.X)), 0.000167);
    }
};

UT_CASE(Orbit, Parabolic) {
    T const two(2);
    T const sqrt_2(sqrt(two));

    Orbit const O(2, 0, {1,0,0}, {0,2,0});

    EXPECT_EQ(O.mu, 2);
    EXPECT_EQ(r4(O.n), r4(sqrt_2));
    EXPECT_EQ(O.t0, 0);
    EXPECT_EQ(O.R0, (V{1,0,0}));
    EXPECT_EQ(O.r0, 1);
    EXPECT_EQ(O.V0, (V{0,2,0}));
    EXPECT_EQ(O.vv0, 4);
    EXPECT_EQ(O.alpha, 0);
    EXPECT_EQ(O.sqrt_alpha, 0);


    {
        Projection const P = O.at_t(0.1);
        EXPECT_EQ(&P._, &O);
        EXPECT_EQ(P.t, 0.1);
        EXPECT_EQ(P.X, 0);
    }

    {
        Projection const P = O.at_X(0.1);
        EXPECT_EQ(&P._, &O);
        EXPECT_EQ(r4(P.t), 0.0708);
        EXPECT_EQ(P.X, 0.1);
        EXPECT_EQ(r4(O.Esum(P.X)), 0.005);
        EXPECT_EQ(r4(O.Osum(P.X)), 0.000167);
    }
};

    }
}
