#include "orbit.hh"

#include <cmath>

namespace Farsyte {
    namespace Orbit {

        T Orbit::Esum(
            T const & X) const
        {
            T const X2 = X * X;
            T const tf = alpha * X2;

            if (tf > +0.0001) {
                T const theta = X * sqrt_alpha;
                return (1 - cos (theta)) / alpha;
            }

            if (tf < -0.001) {
                T const itheta = X * sqrt_alpha;
                return (1 - cosh (itheta)) / alpha;
            }

            return (X2 / (1 * 2)) * (1 - (tf / (3 * 4)) * (1 - (tf / (5 * 6))));
        }

        T Orbit::Osum(
            T const & X) const
        {
            T const X2 = X * X;
            T const tf = alpha * X2;

            if (tf > +0.0001) {
                T const theta = X * sqrt_alpha;
                return (theta - sin (theta)) / (alpha * sqrt_alpha);
            }

            if (tf < -0.001) {
                T const itheta = X * sqrt_alpha;
                return (itheta - sinh (itheta)) / (alpha * sqrt_alpha);
            }

            T const X3 = X2 * X;

            return (X3 / (2 * 3)) * (1 - (tf / (4 * 5)) * (1 - (tf / (6 * 7))));
        }

        T Orbit::XtoM(T const &X) const {
            T const sigma0 = 0;
            return sigma0 * Esum(X) +
                (1-r0*alpha) * Osum(X) +
                r0 * X;
        }

        T Orbit::MtoX(T const &M) const {
            T X = T();

            // XXX: adjust X until M == XtoM(X).
            (void)M;


            return X;
        }

        Orbit::Orbit (
            T const & mu,
            T const & t0,
            V const & R0,
            V const & V0 )
            : mu(mu)
            , t0(t0)
            , R0(R0)
            , V0(V0)

            , n(sqrt(mu))
            , r0(norm(R0))
            , vv0(normsq(V0))
            , alpha(2/r0 - vv0 / mu)
            , sqrt_alpha(sqrt(fabs(alpha)))
            , sigma0(dot(R0,V0)/n)
        {
        }

        Projection::Projection(
                Orbit const &_,
                T const & t,
                T const & X )
            : _(_), t(t), X(X) { }

        Projection Orbit::at_t(T const &t) const {
            T const M = n * (t - t0);
            T const X = MtoX(M);
            return Projection(*this, t, X);
        }

        Projection Orbit::at_X(T const &X) const {
            T const M = XtoM(X);
            T const t = t0 + M / n;
            return Projection(*this, t, X);
        }

    }
}
