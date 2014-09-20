#include "testing_internal.h"

using std::string;

string Farsyte::Testing::testing_version(int i)
{
  switch (i) {
  case 0: return _testing_h;
  case 1: return _testing_internal_h;
  default: return "";
  }
}
