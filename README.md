Toolkit
=======

This is a collection of tools I use from time to time.

I will be moving tools into this project, generally by rewriting them
from scratch.

Along the way, it is my intention to be strict about software
engineering ideals and methods: I would really like this code to
compile cleanly and work correctly, at least on all the machines that
I use from day to day.

Goals
-----

By "compile cleanly" I mean no warnings from the compiler. Exceptions
may have to be made, but should reflect exceptional circumstances.

By "work correctly" I mean that the code should pass automated testing
that checks all documented features. Test coverage should include all
of the intended common usage scenarios.

Contents
--------

This Toolkit is intended to grow to contain libraries, frameworks,
utility programs, and utility scripts. It may also contain data files
supporting any of the above. The distinction between kinds of things
is strong, but it will not be a top level organizational criterion.

Generally, I prefer libraries to frameworks: you can often write a
program to make use of facilities from more than one library, but
dealing with two frameworks battling for who gets to be the Main Loop
is something that I never ever want to have to do again.

My intention is to provide frameworks for some of the very common
kinds of programs that I find myself writing, where the framework is a
fairly small scaffolding that makes use of library code. The intention
is to assure that a program is not forced to use a specific framework
if it wants to gain access to a useful service.

Tools Required
--------------

Less common tools that a complete build of the Toolkit needs:

  * markdown
  * doxyen
  * dot
