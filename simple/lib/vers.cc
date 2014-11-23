#include "simple.hh"

using std::string;
using std::vector;

namespace Farsyte {
    namespace Simple {

        const char ** simple_versions() {
            static const char * ret[] = {
                _simple_h,
                _simple_row_h,
                _simple_col_h,
                _simple_mat_h,
                0
            };
            return ret;
        }

    }
}
