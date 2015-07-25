Toolkit
=======

This is a re-collection of tools I use from time to time.

Bits of useful and not-so-useful code will tend to appear
here over time; this is where I tinker with ideas on how
to do software engineering, not where I do my tinkering
with the code itself.


Long Term Targets
-----------------

 - Controlled Rigid Body Motion in a gravitational field

 - Kalman Filter Toolkit
 - Neural Network Toolkit
 - P-I-D Controller Toolit

 - Matrix Math Library
 - Quaternion Math Library
 - Vector Math Library

See the "Details" document for more thinking.

Languages
---------

My intention is to use mutliple languages, and to document exactly
which variant of the language is in use in any given set of files.

Currently, I'm considering using C++, C, and Lua. The precise list
of the language variants -- and links to the definitions of those
variants -- can be found in the Details.

Clean
-----

My goals are for this to compile cleanly and work correctly -- and in
my world, this means having an automatic testing mechanism that can be
run on the project as a whole, to assure that an update actually does
what it says on the tin, and does not break anything else.

By "compile cleanly" I mean no warnings from the compiler. Exceptions
may have to be made, but should reflect exceptional circumstances.

By "work correctly" I mean that the code should pass automated testing
that checks all documented features. Test coverage should include all
of the intended common usage scenarios.

See the "Details" document for the exact list of warning flags.

Doxygen Output
--------------

Doxygen can provide a handy set of reference documents. If they are
built, [find them here](inc/html/index.html).

Tools Required
--------------

Various tools that a complete build of the Toolkit may require:

  * markdown
  * emacs "org mode"
  * doxyen
  * graphviz
