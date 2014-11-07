#ifndef _orbit_eqns_h
#define _orbit_eqns_h "orbit_eqns v0.1" /**< for header vs library matching */

/** \file
 * \brief Orbit Library Detailed Equations
 *
 * These subroutines are exposed mainly for unit testing
 * and debugging.
 */

#include "orbit.hh"

#include <cmath>

namespace Farsyte {
    namespace Orbit {

        /** Sum of even-powered infinite series.
         * \param X2 Square of input X.
         * \param tf Common factor in ratio of adjacent terms.
         * \param terms Number of terms to evaluate.
         * \returns Sum of the truncated series.
         *
         * The Universal formulation of the Kepler equation
         * makes use of a sum of an infinite series of even
         * powers of the input X. 
         *
         * This function evaluates the series by calculating
         * the sum of the specified number of leading terms.
         */
        static inline
        T Esum_est(T X2, T tf, unsigned terms) {
            if (terms < 1) return 0;
            T calc = 1;
            switch (terms) {
            default:
                while (terms > 4) {
                    calc = 1 - calc * tf / ((2*terms-1)*(2*terms));
                    terms --;
                }
            case 4: calc = 1 - calc * tf / (7*8);
            case 3: calc = 1 - calc * tf / (5*6);
            case 2: calc = 1 - calc * tf / (3*4);
            case 1: calc = 1 - calc * X2 / (1*2);
            case 0: return 1 - calc;
            }
        }

        /** Sum of even-powered infinite series (positive case).
         * \param alpha inverse of semimajor axis
         * \param sqrt_alpha precalculated square root of alpha
         * \param X value of the affine variable
         * \returns sum of the series
         *
         * This function performs the closed form calculation of the
         * limit value of the sum. It can be used only in cases where
         * alpha is positive; it is most useful when the infinite
         * series takes many terms to converge.
         */
        static inline
        T Esum_pos(T alpha, T sqrt_alpha, T X) {
            T theta = X * sqrt_alpha;
            return (1 - cos (theta)) / alpha;
        }

        /** Sum of even-powered infinite series (negative case).
         * \param alpha inverse of semimajor axis
         * \param sqrt_alpha precalculated square root of negative of alpha
         * \param X value of the affine variable
         * \returns sum of the series
         *
         * This function performs the closed form calculation of the
         * limit value of the sum. It can be used only in cases where
         * alpha is negative; it is most useful when the infinite
         * series takes many terms to converge.
         */
        static inline
        T Esum_neg(T alpha, T sqrt_alpha, T X) {
            T theta = X * sqrt_alpha;
            return (1 - cosh (theta)) / alpha;
        }

        /** Sum of even-powered infinite series (selector).
         * \param alpha inverse of semimajor axis
         * \param sqrt_alpha precalculated square root of negative of alpha
         * \param X value of the affine variable
         * \returns sum of the series
         *
         * This function performs the closed form calculation of the
         * limit value of the sum via one of the three imlementations
         * above.
         *
         * In production: the number of terms should be tuned so that
         * the polynomial evaluation is not too slow, and the
         * thresholds at which the closed forms are used are tuned to
         * activate before the series truncation errors become
         * significant.
         */
        static inline
        T Esum_sel(T alpha, T sqrt_alpha, T X) {
            T const X2 = X * X;
            T const tf = alpha * X2;

            if (tf > +0.0001)
                return Esum_pos(alpha, sqrt_alpha, X);

            if (tf < -0.001)
                return Esum_neg(alpha, sqrt_alpha, X);

            return Esum_est(X2, tf, 3);
        }

        /** Sum of odd-powered infinite series.
         * \param X3 Cube of input X.
         * \param tf Common factor in ratio of adjacent terms.
         * \param terms Number of terms to evaluate.
         * \returns Sum of the truncated series.
         *
         * The Universal formulation of the Kepler equation
         * makes use of a sum of an infinite series of odd
         * powers of the input X. 
         *
         * This function evaluates the series by calculating
         * the sum of the specified number of leading terms.
         */
        static inline
        T Osum_est(T X3, T tf, int terms) {
            T calc = 1;
            switch (terms) {
            default:
                while (terms > 4) {
                    calc = 1 - calc * tf / ((terms*2)*(terms*2+1));
                    terms --;
                }
            case 4: calc = 1 - calc * tf / (8*9);
            case 3: calc = 1 - calc * tf / (6*7);
            case 2: calc = 1 - calc * tf / (4*5);
            case 1: calc = 1 - calc * X3 / (2*3);
            case 0: return 1 - calc;
            }
        }

        /** Sum of odd-powered infinite series (positive case).
         * \param alpha inverse of semimajor axis
         * \param sqrt_alpha precalculated square root of alpha
         * \param X value of the affine variable
         * \returns sum of the series
         *
         * This function performs the closed form calculation of the
         * limit value of the sum. It can be used only in cases where
         * alpha is positive; it is most useful when the infinite
         * series takes many terms to converge.
         */
        static inline
        T Osum_pos(T alpha, T sqrt_alpha, T X) {
            T const theta = X * sqrt_alpha;
            return (theta - sin (theta)) / (alpha * sqrt_alpha);
        }

        /** Sum of odd-powered infinite series (negative case).
         * \param alpha inverse of semimajor axis
         * \param sqrt_alpha precalculated square root of negative of alpha
         * \param X value of the affine variable
         * \returns sum of the series
         *
         * This function performs the closed form calculation of the
         * limit value of the sum. It can be used only in cases where
         * alpha is negative; it is most useful when the infinite
         * series takes many terms to converge.
         */
        static inline
        T Osum_neg(T alpha, T sqrt_alpha, T X) {
            T const theta = X * sqrt_alpha;
            return (theta - sinh (theta)) / (alpha * sqrt_alpha);
        }

        /** Sum of odd-powered infinite series (selector).
         * \param alpha inverse of semimajor axis
         * \param sqrt_alpha precalculated square root of negative of alpha
         * \param X value of the affine variable
         * \returns sum of the series
         *
         * This function performs the closed form calculation of the
         * limit value of the sum via one of the three imlementations
         * above.
         *
         * In production: the number of terms should be tuned so that
         * the polynomial evaluation is not too slow, and the
         * thresholds at which the closed forms are used are tuned to
         * activate before the series truncation errors become
         * significant.
         */
        static inline
        T Osum_sel(T alpha, T sqrt_alpha, T X) {
            T const X2 = X * X;
            T const tf = alpha * X2;

            if (tf > +0.0001)
                return Osum_pos(alpha, sqrt_alpha, X);

            if (tf < -0.001)
                return Osum_neg(alpha, sqrt_alpha, X);

            return Osum_est(X * X2, tf, 3);
        }

    }
}

#endif//_orbit_eqns_h
