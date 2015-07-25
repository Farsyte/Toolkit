Toolkit
=======

This is a re-collection of tools I use from time to time.

Bits of useful and not-so-useful code will tend to appear
here over time; this is where I tinker with ideas on how
to do software engineering, not where I do my tinkering
with the code itself.

Long Term Targets
-----------------

While my focus here is on writing tested code methodically,
this works better if I have some longer term use cases in mind,
even if they are just larger library-like abstractions.

Currently, I am aiming for these programming toys:

 - Controlled Rigid Body Motion in a gravitational field

Note that this requires tracking position, momentum,
orientation and angular momentum of a rigid body with
slowly changing mass and moment of inertia, as it moves
through a space containing gravitational fields, under
control of a collection of actuators fixed to the body.

Yes, this has been done before. Yes, I could probably fork
an existing repository with working code. And yes, that
would completely and utterly miss the point of this project.

I have in mind the following higher level support tools:

 - Kalman Filter Toolkit
 - Neural Network Toolkit
 - P-I-D Controller Toolit

Below this, I am aiming at a collection of smaller support
facilities; curently thinking:

 - Matrix Math Library
   - with run-time MxN dimensions (maybe not)
   - with compile-time MxN dimensions
   - specific code for 4x4 matrices
   - specific code for 3x3 matrices
   - specific code for 2x2 matrices

 - Quaternion Math Library

 - Vector Math Library
   - with run-time N dimensions (maybe not)
   - with compile-time N dimensions
   - specific code for 4-vectors
   - specific code for 3-vectors
   - specific code for 2-vectors



Languages
---------

My intention is to use mutliple languages, and to document exactly
which variant of the language is in use in any given set of files.

The languages I have in mind at the moment are:

 - C++1y

   The latest publicly available draft standard
   as I write this (on 2015-07-18)
   is "2013-10-13 14882 2014 Draft N3797.pdf"

   N3797 is publicly available
   [here](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2011/n3797.pdf).

 - C++11

   I use "2011-02-28 14882 2011 Draft N3242.pdf" as my source for the
   definition of this very recent version of the C++ programming language.

   N3242 is publicly available
   [here](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2011/n3242.pdf).

 - C++03

   I purchased "INCITS ISO IEC C++ 14882 2003.pdf" in order to have a
   correct and true copy of the language standard as signed.

 - C++98

   I refer to a copy of "Committee Draft 2" from 1996, but to be honest,
   when I write that code is C++98, what I really mean is that GCC, when
   set to `--std=c++98` with all warnings enabled, compiles the code
   cleanly and the result runs correctly.

 - C11

   I use "2011-04-12 9899 201x Draft N1570.pdf" as my source for the
   definition of this most recent update of the C programing language.

   N1570 is publicly available
   [here](http://www.open-std.org/jtc1/sc22/WG14/www/docs/n1570.pdf).

 - C99

   I use "2007-09-07 9899 TC3 Draft N1256.pdf" as my source for the
   definition of the C99 language in practice.

   N1256 is publicly available
   [here](http://www.open-std.org/jtc1/sc22/WG14/www/docs/n1256.pdf).

   I also purchased "INCITS ISO IEC C99  9899 1999.pdf" in order to have a
   correct and true copy of the language standard as signed.

 - C90

   I have a copy of _The Annotated ANSI C Standard_ by Herbert Schildt
   which has this standard, interwoven with commentary. General advice
   seems to be to ignore the commentary, and that this is possibly the
   only reasonable source for the text.

   I consider "Strict C90" to be of only historical interest.

Clean
-----

By "compile cleanly" I mean no warnings from the compiler. Exceptions
may have to be made, but should reflect exceptional circumstances.

By "work correctly" I mean that the code should pass automated testing
that checks all documented features. Test coverage should include all
of the intended common usage scenarios.

Typical compiler warnings enabled:

  * `--std=c++11` (or similar)
	to enable C++11 facilities without compiler extensions.

  * `-pedantic`
	Issue all warnings demanded by Strict ISO C and C++.
	Reject all programs that use forbidden extensions,
	and some programs that do not follow ISO C and C++.

  * `-Wall`
    Turn on nearly every warning in the compiler.

  * `-Wextra` and `-W`
    Turn on even more warnings.

  * `-Weffc++`
    Warnings from _Effective C++_ by Scott Meyers.

  * `-Werror`
	I am serious about not having warnings.

Doxygen Output
--------------

Doxygen can provide a handy set of reference documents. If they are
built, [find them here](inc/html/index.html).

Tools Required
--------------

Various tools that a complete build of the Toolkit may require:

  * markdown
  * doxyen
  * graphviz
