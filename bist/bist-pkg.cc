#include "bist-pkg.hh"
#include "bist-fun.hh"

#include <string>
using std::string;

#include <iostream>
using std::ostream;
using std::unitbuf;
using std::endl;

#include <sstream>
using std::istringstream;
using std::ostringstream;

#include <fstream>
using std::ofstream;

namespace Bist {

#define MARKER(str)     "{{ BIST " << str << " }}\n"
    
    Pkg::Pkg(ostream &s, string const &n)
        : log(s)
    {
        if (bist_pend) bist();
        log << unitbuf;
        log << MARKER("START PKG " + n);
    }

    Pkg::~Pkg()
    {
        log << MARKER("FINAL PKG");
    }

    bool Pkg::bist_pend = true;

    bool Pkg::bist() {
        if (!bist_pend) return true;
        bist_pend = false;
        
        ofstream bs("bist-pkg.bist");
        Bist::Pkg p(bs,"bist-pkg");

        bool ec =
            // bist_more_tests(p) &&
            bist_text(p);

        return ec;
    }

    bool Pkg::bist_text(Pkg &p) {
        Bist::Fun f(p,"text");

        ostringstream ts;
        {
            Bist::Pkg tp(ts,"empty");
            tp.log << "  a procedure was followed" << endl;
        }

        istringstream si(ts.str());

        // stream comparison: stop at the first failure,
        // and end with requiring an end-of-file.
        bool ec =
            f.bist(__LINE__,si,"{{ BIST START PKG empty }}") &&
            f.bist(__LINE__,si, "  a procedure was followed") &&
            f.bist(__LINE__,si, "{{ BIST FINAL PKG }}") &&
            f.bist(__LINE__,si);

        return ec || f.fail( );
    }
}
