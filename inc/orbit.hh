#ifndef _orbit_h
#define _orbit_h "orbit v0.1" /**< for header vs library matching */

/** \file
 * \brief Orbit Library Exported API
 *
 * This file provides data types, function prototypes and macro
 * definitions for C code using this Orbit library.
 */

#include <vector>
#include <string>

#include "simple.hh"

namespace Farsyte {
    namespace Orbit {

        typedef Farsyte::Simple::T T;
        typedef Farsyte::Simple::R R;
        typedef Farsyte::Simple::V V;
        typedef Farsyte::Simple::M M;

        class Projection;

        /** Information about the orbit of a test mass.
         */
        class Orbit {
        public:

            /** Gravitational Field Strength. */
            T const mu;

            /** Initial Time. */
            T const t0;

            /** Initial Position. */
            V const R0;

            /** Initial Velocity. */
            V const V0;

            /** Square root of field strength.
             * This is the equivalent of the mean angular
             * rate when using the Universal formulation
             * of the Kepler equation.
             */
            T const n;

            /** Initial Radius.
             * Calculated during construction as the
             * two-norm of the radius vector.
             */
            T const r0;

            /** Square of initial speed.
             * Calculated during construction as the
             * square of the two-norm of the velocity vector.
             */
            T const vv0;

            /** Inverse of semi-major axis.
             * Calculated during construction.
             * Will be negative for hyperbolic trajectories.
             * Will be zero for parabolic trajectories.
             * Will be positive for elliptical orbits,
             * including degenerate orbits.
             */
            T const alpha;

            /** Square root of absolute value of alpha.
             */
            T const sqrt_alpha;

            /** Sigma Zero.
             * Common subexpression for Universal Kepler Equation,
             * dot product of V0 and R0, divided by sqrt(mu).
             */
            T const sigma0;

            Orbit (
                T const & mu,
                T const & t0,
                V const & R0,
                V const & V0 );

            Projection at_t(T const &t) const;

            Projection at_X(T const &X) const;

            T Esum(T const &X) const;
            T Osum(T const &X) const;
            T XtoM(T const &X) const;
            T MtoX(T const &M) const;
        };

        class Projection {
        public:
            Orbit const &_;
            T const t;
            T const X;

            Projection(
                Orbit const &_,
                T const & t,
                T const & X );
        };


        /** Retrieve "orbit" version strings from library.
         * This method provides access to a list containing
         * the version strings from the headers used to compile
         * the orbit library.
         */
        extern std::vector<std::string> const &orbit_versions();

    }
}

#endif//_orbit_h
