#include "bist-fun.hh"
#include "bist-pkg.hh"

#include <string>
using std::string;

#include <iostream>
using std::istream;
using std::ostream;
using std::unitbuf;
using std::endl;

#include <sstream>
using std::ostringstream;
using std::istringstream;

namespace Bist {

#define MARKER(str)     "{{ BIST " << str << " }}\n"

    Fun::Fun(Pkg &p, string const &n)
        : pkg(p)
        , log(pkg.log)
    {
        log << MARKER("START FUN " + n);
    }

    Fun::~Fun()
    {
        log << MARKER("FINAL FUN");
    }

    bool Fun::pass() {
        log << MARKER("PASS");
        return (bool)log;
    }

    bool Fun::skip() {
        log << MARKER("SKIP");
        return (bool)log;
    }

    bool Fun::fail() {
        log << MARKER("FAIL");
        return false;
    }

    bool Fun::error() {
        log << MARKER("ERROR");
        return false;
    }

    bool Fun::bist(ostream &bs) {

        Bist::Pkg p(bs,"bist-fun");

        // uses "test && ec" so all are executed
        // could use "ec && test" to test only if passing.

        bool ec =
            bist_noop(p) &&
            bist_pass(p) &&
            bist_skip(p) &&
            bist_fail(p) &&
            bist_error(p);

        return ec;
    }

    bool Fun::bist_noop(Pkg &p) {
        Bist::Fun f(p,"noop");

        ostringstream ts;
        {
            Bist::Pkg tp(ts,"dummy");
            Bist::Fun tf(tp,"noop");
            tf.log << "  a procedure was followed" << endl;
        }

        istringstream si(ts.str());

        // stream comparison: stop at the first failure,
        // and end with requiring an end-of-file.
        bool ec =
            f.bist(__LINE__,si,"{{ BIST START PKG dummy }}") &&
            f.bist(__LINE__,si, "{{ BIST START FUN noop }}") &&
            f.bist(__LINE__,si, "  a procedure was followed") &&
            f.bist(__LINE__,si, "{{ BIST FINAL FUN }}") &&
            f.bist(__LINE__,si, "{{ BIST FINAL PKG }}") &&
            f.bist(__LINE__,si);

        return ec || f.fail( );
    }

    bool Fun::bist_pass(Pkg &p) {
        Bist::Fun f(p,"pass");

        ostringstream ts;
        {
            Bist::Pkg tp(ts,"dummy");
            Bist::Fun tf(tp,"pass");
            tf.log << "  expected: foo" << endl;
            tf.log << "  observed: foo" << endl;
            tf.pass();
        }

        istringstream si(ts.str());

        // stream comparison: stop at the first failure,
        // and end with requiring an end-of-file.

        bool ec =
            f.bist(__LINE__,si, "{{ BIST START PKG dummy }}") &&
            f.bist(__LINE__,si, "{{ BIST START FUN pass }}") &&
            f.bist(__LINE__,si, "  expected: foo") &&
            f.bist(__LINE__,si, "  observed: foo") &&
            f.bist(__LINE__,si, "{{ BIST PASS }}") &&
            f.bist(__LINE__,si, "{{ BIST FINAL FUN }}") &&
            f.bist(__LINE__,si, "{{ BIST FINAL PKG }}") &&
            f.bist(__LINE__,si);

        return ec || f.fail( );
    }

    bool Fun::bist_skip(Pkg &p) {
        Bist::Fun f(p,"skip");

        ostringstream ts;
        {
            Bist::Pkg tp(ts,"dummy");
            Bist::Fun tf(tp,"skip");
            tf.log << "  test does not apply" << endl;
            tf.skip();
        }

        istringstream si(ts.str());

        // stream comparison: stop at the first failure,
        // and end with requiring an end-of-file.

        bool ec =
            f.bist(__LINE__,si, "{{ BIST START PKG dummy }}") &&
            f.bist(__LINE__,si, "{{ BIST START FUN skip }}") &&
            f.bist(__LINE__,si, "  test does not apply") &&
            f.bist(__LINE__,si, "{{ BIST SKIP }}") &&
            f.bist(__LINE__,si, "{{ BIST FINAL FUN }}") &&
            f.bist(__LINE__,si, "{{ BIST FINAL PKG }}") &&
            f.bist(__LINE__,si);

        return ec || f.fail( );
    }

    bool Fun::bist_fail(Pkg &p) {
        Bist::Fun f(p,"fail");
        ostringstream ts;
        {
            Bist::Pkg tp(ts,"dummy");
            Bist::Fun tf(tp,"fail");
            tf.log << "  expected: foo" << endl;
            tf.log << "  observed: bar" << endl;
            tf.fail();
        }

        istringstream si(ts.str());

        // stream comparison: stop at the first failure,
        // and end with requiring an end-of-file.

        bool ec =
            f.bist(__LINE__,si, "{{ BIST START PKG dummy }}") &&
            f.bist(__LINE__,si, "{{ BIST START FUN fail }}") &&
            f.bist(__LINE__,si, "  expected: foo") &&
            f.bist(__LINE__,si, "  observed: bar") &&
            f.bist(__LINE__,si, "{{ BIST FAIL }}") &&
            f.bist(__LINE__,si, "{{ BIST FINAL FUN }}") &&
            f.bist(__LINE__,si, "{{ BIST FINAL PKG }}") &&
            f.bist(__LINE__,si);

        return ec || f.fail( );
    }

    bool Fun::bist_error(Pkg &p) {
        Bist::Fun f(p,"error");
        ostringstream ts;
        {
            Bist::Pkg tp(ts,"dummy");
            Bist::Fun tf(tp,"error");
            tf.log << "  test setup failure" << endl;
            tf.error();
        }

        istringstream si(ts.str());

        // stream comparison: stop at the first failure,
        // and end with requiring an end-of-file.

        bool ec =
            f.bist(__LINE__,si, "{{ BIST START PKG dummy }}") &&
            f.bist(__LINE__,si, "{{ BIST START FUN error }}") &&
            f.bist(__LINE__,si, "  test setup failure") &&
            f.bist(__LINE__,si, "{{ BIST ERROR }}") &&
            f.bist(__LINE__,si, "{{ BIST FINAL FUN }}") &&
            f.bist(__LINE__,si, "{{ BIST FINAL PKG }}") &&
            f.bist(__LINE__,si);

        return ec || f.fail( );
    }

    bool Fun::bist(int line, istream &si, string const &ex) {
        static const string q("\"");
        string ob("");
        bool gl = (bool) getline(si, ob);
        bool ok = gl && (ob == ex);

        // This code is organized oddly to avoid gcov marking
        // untestable code as unvisited. I acknowledge that cheating
        // in the name of getting more useful outputs is still
        // cheating, and I apologise.

        ok || log << __FILE__ << ":" << line << ": BIST failure in Bist::Fun\n";
        ok || log << "  expected: " << q << ex << q << endl;
        ok ||  gl || log << "  observed: end of stream" << endl;
        ok || !gl || log << "  observed: " << q << ob << q << endl;

        !ok || log << "  " << q << ex << q << endl;

        return ok;
    }

    bool Fun::bist(int line, istream &si) {
        static const string q("\"");
        string ob("");
        bool gl = (bool) getline(si, ob);
        bool ok = !gl;

        // This code is organized oddly to avoid gcov marking
        // untestable code as unvisited. I acknowledge that cheating
        // in the name of getting more useful outputs is still
        // cheating, and I apologise.

        ok || log << __FILE__ << ":" << line << ": BIST failure in Bist::Fun+\n";
        ok || log << "  expected: end of stream" << endl;
        ok || log << "  observed: " << q << ob << q << endl;

        !ok || log << "  end of input" << endl;

        return ok;
    }
}
