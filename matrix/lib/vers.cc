#include "matrix.h"

using std::string;

string Farsyte::Matrix::matrix_version(int i)
{
  switch (i) {
  case 0: return _matrix_h;
  default: return "";
  }
}
