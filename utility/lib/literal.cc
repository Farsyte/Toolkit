#include "utility.h"

using std::ostringstream;
using std::string;

string Farsyte::Utility::literal(char ch) {
    switch (ch) {
        case '\'':
            return "\\\'";
        case '\"':
            return "\\\"";
        case '\0':
            return "\\0";
        case '\\':
            return "\\\\";
        case '\?':
            return "\\?";
        case '\a':
            return "\\a";
        case '\b':
            return "\\b";
        case '\f':
            return "\\f";
        case '\n':
            return "\\n";
        case '\r':
            return "\\r";
        case '\t':
            return "\\t";
        case '\v':
            return "\\v";
        default:
            if ((32 <= ch) && (ch < 127))
                return string(1, ch);
            return "\\?";
    }
}

string Farsyte::Utility::literal(string const &str) {
    ostringstream oss;
    for (size_t i = 0; i < str.size(); ++i)
        oss << literal(str[i]);
    return oss.str();
}

string Farsyte::Utility::quoted(string const &str) {
    ostringstream oss;
    oss << '"';
    for (size_t i = 0; i < str.size(); ++i)
        oss << literal(str[i]);
    oss << '"';
    return oss.str();
}

