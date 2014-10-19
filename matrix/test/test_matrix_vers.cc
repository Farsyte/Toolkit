#include "matrix.hh"
#include "testing.hh"
#include <fstream>
#include <assert.h>

using Farsyte::Matrix::ColVec;
using Farsyte::Matrix::Matrix;
using Farsyte::Matrix::TriVec;
using Farsyte::Testing::Log;
using Farsyte::Testing::Oops;
using Farsyte::Testing::Suite;
using Farsyte::Testing::Test;
using std::cerr;
using std::setw;
using std::cout;
using std::endl;
using std::istringstream;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::setw;
using std::string;
using std::vector;

/* -- ================================================================ -- */

UT_CASE(Matrix, Versions) {
    
    vector<string> const & vers = Farsyte::Matrix::matrix_versions();

    EXPECT_GE(vers.size(), 1u);
    EXPECT_EQ(vers[0], string(_matrix_h));
    
};
