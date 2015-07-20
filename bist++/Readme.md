Built-In Self Test
==================

I recently did some tinkering where it was useful to have an automatic
"built-in self test" in some of the C++ classes, which in that case
was useful to trigger the first time an object of that class was
constructed.

Of course this led to tinkering with making the BIST related classes
test themselves. So this is where I start in this round of tinkering
with my Toolkit.

>  ***NOTE: The Built-In Self Tests implemented within the Built-In
>  Self-Test classes are not good example code, as they have to
>  provide BIST services but can not assume the BIST code works.***

Test Reporting Heirarchy
------------------------

- A record of tests contains a test of one package, which has
- Tests of severfal functions, each of which has
- Several PASS/SKIP/FAIL/ERROR markers, each preceeded by
- Several lines of supporting text.

For bookkeeping purposes, each function counts
as a single PASS/SKIP/FAIL/ERROR result. The results
are prioritized to combine them.

Each program is expected to produce a separate
record of BIST results. Records from multiple
programs are expected to be merged based on the
names of the packages and functions, deduplicating
results and accumulating non-overlapping data.

Bist::Pkg
---------

The lifetime of this object encapsulates the testing
for a single package, or a collection of tests at that
rough level of abstraction. It is responsible for
generating markers in the BIST results stream to
indicate the start of testing for a package, and
to confirm completion of such testing.

Bist::Fun
---------

The lifetime of this object encapsulates the testing
for a single function, or a collection of tests at that
rough level of abstraction. It is responsible for
generating markers in the BIST results stream to
indicate the start of testing for a function, and
to confirm completion of such testing.

This object presents a member which is an output
stream to be used by the testing sequence for
reporting supporting information about the test.

> Bamboo (for example) does not provide any means
> to view supporting text within a Function that
> has a **`PASS`** result. It is strongly encouraged
> that any CI implementations arrange to make the
> original BIST logs available to the engineer.

Bist of Bist classes
--------------------

Setting up a test class to test itself without
depending on itself being correct is a puzzle
which does not need to be solved. Instead, these
classes contain normal self-test calls, and we do
an external check that the resulting BIST logs
match a reference output exactly.

This does mean that any change to Bist will require
the new logs to be examined manually -- or at least
their changes -- but it is not clear we could get
away from that, in any case.

