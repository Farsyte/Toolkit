# -*- makefile-gmake -*-

Q               = @
I		= -
C		= $Q $I
P		= $C printf
R		= /bin/rm -fr
X		= /bin/cp -vf
S               = md5sum

ifeq ($(DEBUG),)
OPT             = -O2
else
OPT             = -O0
DBG             += -g
endif

ifneq ($(PROFILE),)
PROF            += -pg
endif

ifneq ($(COVERAGE),)
PROF            += -fprofile-arcs -ftest-coverage
endif

CSTD            = --std=c11
XSTD            = --std=c++11
ERR             = -W -Wall -Wextra -pedantic -Werror \
		  -Weffc++ \
		  -Wno-missing-braces

IPATH           = $(IDIRS:%=-I%)
LPATH           = $(LDIRS:%=-L%)
LDLIBS          = $(LLIBS:%=-l%)

CFLAGS          = $(CSTD) $(OPT) $(PROF) $(ERR) $(IPATH)
CPPFLAGS        = $(XSTD) $(OPT) $(PROF) $(ERR) $(IPATH)
LDFLAGS         = $(LPATH) $(PROF) $(LDLIBS)

