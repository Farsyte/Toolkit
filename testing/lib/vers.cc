#include "testing_internal.h"

using std::string;
using std::vector;

vector<string> const & Farsyte::Testing::testing_versions ()
{
  static const vector<string> ret{
      _testing_h,
      _testing_internal_h,
  };
  return ret;
}
