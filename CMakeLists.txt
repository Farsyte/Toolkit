cmake_minimum_required (VERSION 2.6)
project (Tutorial)

enable_testing ()

macro (test_module which)
  add_executable (test_${which} test_${which}.cc)
  target_link_libraries (test_${which} ${which} ${ARGN} testing utility)
  add_test (test_${which} test_${which})
  set_tests_properties (test_${which}
    PROPERTIES 
    FAIL_REGULAR_EXPRESSION "<failure")
  install (TARGETS test_${which} DESTINATION bin)
endmacro (test_module)

add_subdirectory (inc)

add_subdirectory (utility)
add_subdirectory (testing)
add_subdirectory (matrix)
