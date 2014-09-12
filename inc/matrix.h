#ifndef _matrix_h
#define _matrix_h

/** \file
 * \brief Matrix Library Exported API
 *
 * This file provides data types, function prototypes and macro
 * definitions for C code using this Matrix library.
 */

#include <array>

#include <iostream>
using std::cerr;
using std::endl;

#include <iomanip>
using std::fixed;
using std::setw;
using std::setprecision;

namespace Farsyte {
    namespace Matrix {

        class Position
        {
            double data[3];
          public:
            Position() : data{0,0,0} { }
            Position(double x, double y, double z) : data{x,y,z} { }
            double const & operator()(int i) const { return data[i-1]; }
            double       & operator()(int i)       { return data[i-1]; }
        };

    }
}

#endif//_matrix_h
