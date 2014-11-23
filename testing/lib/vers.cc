#include "testing.hh"
#include "testing_internal.hh"

using std::string;
using std::vector;

using namespace Farsyte::Testing;

const char ** Farsyte::Testing::testing_versions() {
    static const char * ret[] = {
        _testing_h,
        _testing_log_h,
        _testing_suite_h,
        _testing_test_h,
        _testing_oops_h,
        _testing_internal_h,
        0
    };
    return ret;
}
