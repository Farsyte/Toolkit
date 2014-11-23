cmake_minimum_required (VERSION 2.6)
project (Toolkit)

enable_testing ()

if(MSVC) # MSVC compiler (Win32 only)
  # While I do not test on Windows, I am told this is how one would
  # add the "turn up the warnings" flag over there.
  set(CMAKE_CXX_FLAGS "/W3")
elseif(UNIX OR CMAKE_COMPILER_IS_GNUCXX) # GCC or Clang (Linux, MacOS, or Win32)

  SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   --std=c99   -W -Wall -Wextra -pedantic -Werror")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++98 -W -Wall -Wextra -pedantic -Werror")

  # Example of quenching a new and unwanted warning.
  # Note that this particular case, which appeared on Stack overflow,
  # causes many "unknown warning option" errors to appear
  # from Apple LLVM version 6.0 (clang-600.0.54) (based on LLVM 3.5svn)
  # which is "current XCode" on MacOS Yosemite,
  # so obviously some refinement would be needed.
  #
  # if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.8)
  #   # turn off a warning produced by newer versions of GCC.
  #   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs")
  # endif()

  # Example of adding Clang/MacOS specific flags.
  # This particuilar example appeared on Stack Overflow as something that
  # had to be done under MacOS "XCode" for C++11 (but in practice, I have
  # not had to do it when I use C++11 so still just an example.)
  #
  # if(APPLE) # Clang / MacOS Only
  #   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -mmacosx-version-min=10.7")
  # endif()

endif()

# Turning this on allows me to see WTF is going on.
# Turning this off makes my compilation logs cleaner.
#
# SET(CMAKE_VERBOSE_MAKEFILE 1)

macro (test_module package which)
  add_executable (test_${which} test_${which}.cc)
  target_link_libraries (test_${which} ${package} ${ARGN} testing utility)
  add_test (test_${which} test_${which})
  set_tests_properties (test_${which}
    PROPERTIES 
    FAIL_REGULAR_EXPRESSION "<failure")
  install (TARGETS test_${which} DESTINATION bin)
endmacro (test_module)

add_subdirectory (inc)

add_subdirectory (utility)
add_subdirectory (testing)
add_subdirectory (simple)
add_subdirectory (matrix)

add_custom_target(runtests
    COMMAND
        /bin/bash ${CMAKE_SOURCE_DIR}/bin/make-runtests.sh
    DEPENDS
        bin/make-runtests.sh
        utility testing simple matrix
        utility-test-all
        testing-test-all
	simple-test-all
        matrix-test-all
    )

add_custom_target(pmccabe
    COMMAND
        /bin/bash ${CMAKE_SOURCE_DIR}/bin/make-pmccabe.sh ${CMAKE_SOURCE_DIR}
    )
