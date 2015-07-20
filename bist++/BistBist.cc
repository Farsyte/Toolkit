#include "BistPkg.hh"
#include "BistFun.hh"

#include <fstream>
using std::ofstream;

#include <iostream>
using std::endl;

int main() {
    ofstream bs("BistBist.bist");
    Bist::Pkg p(bs,"BistBist");
    {
        Bist::Fun f(p,"none");
        f.log << "no logged result is PASS." << endl;
    }

    {
        Bist::Fun f(p,"pass");
        f.log << "explicit pass marker is PASS." << endl;
        f.pass();
    }

    {
        Bist::Fun f(p,"skip");
        f.log << "explicit skip marker is SKIP." << endl;
        f.skip();
    }

    {
        Bist::Fun f(p,"pass-skip");
        f.log << "both pass and skip is SKIP." << endl;
        f.skip();
        f.pass();
    }

    {
        Bist::Fun f(p,"skip-pass");
        f.log << "both skip and pass is SKIP." << endl;
        f.skip();
        f.pass();
    }

    return 0;
}
