#include "matrix.hh"

using std::string;
using std::vector;

const char ** Farsyte::Matrix::matrix_versions() {
    static const char * ret[] = {
            _matrix_h,
            _matrix_matrix_h,
            _matrix_colvec_h,
            0
    };
    return ret;
}
