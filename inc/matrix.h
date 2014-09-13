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

    class Position {
      double data[3];
    public:

      Position()
        : data{0,0,0} {
      }

      Position(double x, double y, double z)
        : data{x,y,z} {
      }

      Position(Position const &p)
        : data{p.data[0], p.data[1], p.data[2]} {
      }

      double const & operator()(int i) const { 
        return data[i-1];
      }

      double       & operator()(int i)       {
        return data[i-1];
      }

      Position & operator=(Position const &p) {
        data[0] = p.data[0];
        data[1] = p.data[1];
        data[2] = p.data[2];
        return *this;
      }

      Position & operator+=(Position const &p) {
        data[0] += p.data[0];
        data[1] += p.data[1];
        data[2] += p.data[2];
        return *this;
      }

      Position & operator-=(Position const &p) {
        data[0] -= p.data[0];
        data[1] -= p.data[1];
        data[2] -= p.data[2];
        return *this;
      }

    };

    Position operator+(Position L, Position const &R) {
      return L += R;
    }

    Position operator-(Position L, Position const &R) {
      return L -= R;
    }

  }
}

#endif//_matrix_h
