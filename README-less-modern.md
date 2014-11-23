Less Modern Conversion
======================

Roll back to using strict C99 everywhere, then adding
light amounts of C++98 to provide "C with Classes" as
the preferred classical programming paradigm.

Why am I doing this
-------------------

I want to mess around with software engineering tools that
may only support C99 and C++98 and may not support compiler
extensions that we would usually expect to see from most
compilers of that vintage.

Features I will Miss
--------------------

I liked being able to use `auto` when declaring and
initializing variables, and in one case in the unit
test macros, this allowed me to distinguish between
an exception when evaluating an expression and an
exception while executing the condition check method.

I liked the new `for` loop facility for iterating
across members of a collection.

I liked using C++11 Lambda notation for expressing
the logic of a unit test, when adding a test clause
to a named test in a named suite.

Unit Tests stay in C++
----------------------

Transparently registering unit tests by suite and test
name is fairly easy in C++ as we can use function calls
in initializers, but initializers in C have to be
compile time constants. No sneaky calling a regitration
function that does work before main starts.

In the short term, my resolution on this is going to be
to place the unit tests for the C code into source files
processed by the C++ compiler, and acknowledge that the
unit test macros are only available in C++.

As it is, lack of `auto` already drives us to have toward
using something like the GCC `typeof` extension, and I
really want to keep this code within the four corners of
the C99 and C++98 standards as much as possible.

