Toolkit: Testing
================

This library can be used by test programs to generate XML text streams
targetted at the JUnit XML results parser provided by the Atlassian
Bamboo Continuous Integration system. The capabilities of this library
are restricted to those semantic elements that have useful impact on
the Bamboo test display.

Bamboo Note
-----------

Bamboo expects tests to be organized in a two layer structure, where
Tests are grouped into Suites. Bamboo accumulates all tests from a
given job, grouping them by Suite name. If a given Suite is opened in
several different files or even several times in one file, Bamboo will
combine the data from all instances. Similarly, if a given Test name
appears multiple times (with the same Suite name), the data for the
test are combined, with tests being marked as failed for that job if
any instance of the test in the results has a failure.

The recommended organization is to assocate a Test Suite with each C++
class being tested, and a Test with each Method being tested within
the class, where there may be several conditions being checked but
only one pass or fail counted for the test; this extends neatly out to
other Suite and Test sets at similar levels of abstraction.

The Oops Object
---------------

Some library usage errors may be detected at runtime, and may be
reported by throwing an Oops object. This contains a reference to a
source file and line number, which may be within the library, and a
string representing why the Oops was being thrown. The object can be
asked to print itself to an output stream. Using this method is
recommended over merely printing the contents of the fields, to allow
future expansion of the mechanism to allow some conditions to provide
more complete diagnostic information.

The Test Object
---------------

Under Bamboo, a test is some procedure that either passes, or fails
with some additional information about the failure. Typically a Test
will involve doing something, then testing a series of conditions, and
reporting conditions that fail. Test objects are members of a Suite
(see below).
The Test object constructor writes appropriate opening text to the XML
file associatd with the Suite. The destructor writes appropriate text
to the XML file to close the XML element corresponding to the
test. Methods on Test objects are available for reporting test
conditions that are skipped, test conditions that fail, and errors
encountered during testing. It is an error to construct a Test object
for a Suite that currently has an active Test object. Be sure that
each Test object goes out of scope before the next one is constructed.

The Suite Object
----------------

The Suite object constructor writes appropraite opening text to the
XML output stream. The destructor writes appropriate text to the XML
stream to close the XML element corresponding to the suite. It is an
error to construct a Suite object for a Log that currently has an
active Suite object; be sure that each Suite object goes out of scope
before the next one is constructed.

The Log Object
--------------

The Log object constructor writes XML text to the specified output
stream to start a new log file. The destructor writes trailer data to
finish the XML element opened at the top.  Test programs create a Log
object for each file they want to write, and may have several Log file
objects open at the same time.
