#include "bist.hh"

#include <iostream>
using std::ostream;
using std::endl;

#include <fstream>
using std::ofstream;

/* -- ================================================================ --
 *    function table of contents
 */

extern int main();
static bool example_pkg_one(ostream &bs);
static bool example_none(Bist::Pkg &p);
static bool example_pass(Bist::Pkg &p);
static bool example_skip(Bist::Pkg &p);
static bool example_pkg_two(ostream &bs);
static bool example_skip_pass(Bist::Pkg &p);
static bool example_pass_skip(Bist::Pkg &p);

/* -- ================================================================ --
 *    run several packages
 */

int main() {
    bool ok = true;
    ofstream bs("bist-example.bist");

    ok = example_pkg_one(bs) && ok;
    ok = example_pkg_two(bs) && ok;

    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}

/* -- ================================================================ --
 *    example package one
 */

static bool example_pkg_one(ostream &bs) {
    bool ok = true;
    Bist::Pkg p(bs,"bist-example-one");

    ok = example_none(p) && ok;
    ok = example_pass(p) && ok;
    ok = example_skip(p) && ok;

    return ok;
}

static bool example_none(Bist::Pkg &p) {
    Bist::Fun f(p,"none");
    f.log << "no logged result is PASS." << endl;
    return true;
}

static bool example_pass(Bist::Pkg &p) {
    Bist::Fun f(p,"pass");
    f.log << "explicit pass marker is PASS." << endl;
    return f.pass();
}

static bool example_skip(Bist::Pkg &p) {
    Bist::Fun f(p,"skip");
    f.log << "explicit skip marker is SKIP." << endl;
    return f.skip();
}

/* -- ================================================================ --
 *    example package two
 */

static bool example_pkg_two(ostream &bs) {
    bool ok = true;
    Bist::Pkg p(bs,"bist-example-two");

    ok = example_pass_skip(p) && ok;
    ok = example_skip_pass(p) && ok;

    return ok;
}

static bool example_skip_pass(Bist::Pkg &p) {
    bool ok = true;
    Bist::Fun f(p,"pass-skip");
    f.log << "both pass and skip is SKIP." << endl;
    ok = f.skip() && ok;
    ok = f.pass() && ok;
    return ok;
}

static bool example_pass_skip(Bist::Pkg &p) {
    bool ok = true;
    Bist::Fun f(p,"skip-pass");
    f.log << "both skip and pass is SKIP." << endl;
    ok = f.pass() && ok;
    ok = f.skip() && ok;
    return ok;
}
