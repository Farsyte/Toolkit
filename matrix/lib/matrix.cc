#include "matrix_matrix.hh"

#include <sstream>

using std::ostringstream;
using std::string;

string Farsyte::Matrix::matrix_range_error(
        int Nr, int Nc, int ri, int ci) {
    ostringstream msg;
    msg << "matrix subscript range error\n";
    if ((ri < 0) || (ri >= Nr))
        msg << "    ri (" << ri << ")"
                << " is not in the range 0.." << (Nr - 1)
                << " inclusive.\n";
    if ((ci < 0) || (ci >= Nc))
        msg << "    ci (" << ci << ")"
                << " is not in the range 0.." << (Nc - 1)
                << " inclusive.\n";
    return msg.str();
}
