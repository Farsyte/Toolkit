#include "simple.hh"

using std::string;
using std::vector;

namespace Farsyte {
    namespace Simple {

        vector<string> const &simple_versions() {
            static const vector<string> ret{
                _simple_h,
                    _simple_row_h,
                    _simple_col_h,
                    _simple_mat_h,
                    };
            return ret;
        }

    }
}
