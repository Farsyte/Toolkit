#include "testing_internal.h"

#include <string>
using std::string;

#include <sstream>
using std::ostringstream;

std::string Farsyte::Testing::cq(char ch, char qc) {

  switch (ch) {
  case '"': return "&quot;";
  case '&': return "&amp;";
  case '\'': return "&apos;";
  case '<': return "&lt;";
  case '>': return "&gt;";
  case '\n': if (qc) return "\\n" ; return "\n";
  case '\t': if (qc) return "\\t" ; return "\t";
  default:
    if (ch < 32) return "";
    if (ch > 126) return "";
    return string(1, ch);
  }
}

string Farsyte::Testing::hq(string const &str, char qc) {
  ostringstream  oss;
  if (qc) oss << qc;
  for (size_t i = 0; i < str.length(); ++i)
    oss << cq(str[i], qc);
  if (qc) oss << qc;
  return oss.str();
}

string Farsyte::Testing::sq(string const &str) {
  return hq(str, '"');
}
