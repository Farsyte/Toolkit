#include "matrix.h"

using std::string;
using std::vector;

vector<string> const &Farsyte::Matrix::matrix_versions() {
    static const vector<string> ret{
            _matrix_h,
            _matrix_matrix_h,
            _matrix_colvec_h,
    };
    return ret;
}
