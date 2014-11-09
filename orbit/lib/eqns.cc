#include "orbit.hh"
#include "orbit_eqns.hh"

#include <cmath>

namespace Farsyte {
    namespace Orbit {

        T Orbit::Esum(
            T const & X) const
        {
            return Esum_sel(alpha, sqrt_alpha, X);
        }

        T Orbit::Osum(
            T const & X) const
        {
            return Osum_sel(alpha, sqrt_alpha, X);
        }

        T Orbit::XtoM(T const &X) const {
            return
                Esum(X) * sigma0 +
                Osum(X) * (1-r0*alpha) +
                X * r0;
        }

        T Orbit::MtoX(T const &M) const {
            T X = T();
            
            (void)M;       // \todo solve for X such that M = XtoM(X).

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
