#include "testing_internal.h"

#include <string>
using std::string;

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;

Oops::Oops(
    string          f,
    int             l,
    string          c)
    : file(f)
    , line(l)
    , cond(c)
    , pend(true)
{
}

ostream& Oops::print(ostream&s) const {
    pend = false;
    return
        s << file << ":"
          << line << ": "
          << "assertion failed\n"
          << "\t" << cond;
}

void Oops::cancel() const {
    pend = false;
}

Oops::~Oops() {
    if (pend)
        print(cerr);
}

ostream& operator<<(ostream&s, Oops const &f) {
    return f.print(s);
}