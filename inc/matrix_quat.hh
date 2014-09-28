#ifndef _matrix_quat_h
#define _matrix_quat_h "matrix quat v0.1" /**< for header vs library matching */

/** \file
* \brief Matrix Library Exported API
*
* This file provides data types, function prototypes and macro
* definitions for C code using this Matrix library.
*/

#include "matrix_trivec.hh"

#include <iostream>

namespace Farsyte {
    namespace Matrix {

        /** Quat Class.
        *
        * This class implements a representation of
        * a Quaternion, a four-degree-of-freedom
        * hypercomplex number comprising a real scalar
        * part and a complex vector part.
        */
        class Quat {
            double w;
            TriVec v;
        public:

            /** Quat Default Constructor.
            * This class assures that all Quat objects are initialized
            * to zero when they are constructed, if no initial value is
            * specified via a different constructor.
            */
            Quat();

            /** Quat Constructor for Given Value.
            */
            Quat(double iw, TriVec const &iv);

            /** Access (read-only) to Scalar Part.
            */
            double const &scalar() const {
                return w;
            }

            /** Access (mutable) to Scalar Part.
            *
            */
            double &scalar() {
                return w;
            }

            /** Access (read-only) to Vector Part.
            */
            TriVec const &vector() const {
                return v;
            }

            /** Access (mutable) to Vector Part.
            *
            */
            TriVec &vector() {
                return v;
            }

            /** Equality Comparison Operation.
            */
            bool eq(Quat const &that) const {
                return (w == that.w) && (v == that.v);
            }

            /** Inequality Comparison Operation.
            */
            bool ne(Quat const &that) const {
                return (w != that.w) || (v != that.v);
            }

        };

        /** Quat Equality Operator
        */
        inline bool operator==(Quat const &p, Quat const &q) {
            return p.eq(q);
        }

        /** Quat Equality Operator
        */
        inline bool operator!=(Quat const &p, Quat const &q) {
            return p.ne(q);
        }

        /** Stream Output Operation.
        */
        extern std::ostream &operator<<(std::ostream &s, Quat const &q);
    }
}

#endif//_matrix_quat_h
