#include "testing.h"
#include "testing_internal.h"

using std::string;
using std::vector;

using namespace Farsyte::Testing;

vector<string> const & Farsyte::Testing::testing_versions ()
{
  static const vector<string> ret{
      _testing_h,
      _testing_log_h,
      _testing_suite_h,
      _testing_test_h,
      _testing_oops_h,
      _testing_internal_h,
  };
  return ret;
}
