Testing Support
===============

Provide common code to simplify construction of tests whose output
will be parsed by an automated build system.

This package is primarily targeted at being used by C++ code, where
running a single C++ compiled executable creates one (or more) XML
files representing test results.

THIS IS A SERVICE LIBRARY, NOT A FRAMEWORK.

You design the code flow of your test system, and implement your
tests, and call these service functions as your data becomes
available. The paradigm is to open objects corresponding to tests and
sets of tests, and add information to them.

Output File Format
------------------

The intent is for the output files from this package to always be
parsable by the JUnit Parser provided in the Atlassian Bamboo
continuous integration system. According to Atlassian,

> Bamboo can parse any test output that conforms to standard JUnit XML
> format. The implementation of this is pretty simple -- Bamboo looks
> for specific tags in the JUnit XML output.

The XML file format is discussed in detail in a supporting document.

