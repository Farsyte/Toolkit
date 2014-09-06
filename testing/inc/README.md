Toolkit: Testing Documentation
==============================

This library can be used by test programs to generate log files that
the Atlassian Bamboo continuous integration system can parse using its
built-in JUnit output parser.

Capabilities of this library are restricted to those semantic elements
that have useful impact on the Bamboo test display.

Test Log Files
--------------

The Bamboo "Parse JUnit Results" task is intended to locate a
collection of XML files containing test results appropriate to that
particular build job. 
