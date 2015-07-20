Q		:= @
I		:= -
C		:= $Q $I
P		:= $C printf
R		:= /bin/rm -f

OFLAGS          := -O3
DFLAGS          := -g
PFLAGS          := -pg --coverage
SFLAGS          := --std=c++11
WFLAGS          := -W -Wall -Wextra -pedantic -Werror

CXXFLAGS        := ${OFLAGS} ${DFLAGS} ${PFLAGS} ${SFLAGS} ${WFLAGS}

SRCS            := ${wildcard *.cc}
OBJS		:= ${SRCS:%.cc=%.o}
PGMS		:= BistBist
SUBS		:= ${filter-out ${PGMS:%=%.o},${OBJS}}
LOGS		:= ${PGMS:%=%.log}

# -- ================================================================ --
#    meta-targets

default:		build

world::
	$Q $(MAKE) clean
	$Q $(MAKE) build
	$Q $(MAKE) execs
	$Q $(MAKE) check
	$Q $(MAKE) cover 

# -- ================================================================ --
#    Compile C++ to Objects

build::			objs
objs::			${OBJS}
${OBJS}:        %.o:            %.cc
	$P '[cc] %s\n' '$*'
	$Q $(COMPILE.cc) $(OUTPUT_OPTION) $<
clean::		; $C $R ${OBJS} *.gcno

# -- ================================================================ --
#    Link Objects into Programs

build::			pgms
pgms::			${PGMS}
${PGMS}:        %:              %.o ${SUBS}
	$P '[ld] %s\n' '$*'
	$Q $(LINK.cc) $*.o ${SUBS} $(LOADLIBES) $(LDLIBS) -o $@
clean::		; $C $R ${PGMS}

# -- ================================================================ --
#    Collect outputs of programs

execs::			logs
logs::			${LOGS}
${LOGS}:        %.log:           %
	$P '[go] %s\n' '$*'
	$Q './$*' 2>&1 | tee '$@'
clean::		; $C $R *.bist *.gcda

# -- ================================================================ --
#    Verify BIST log outputs

BIST		:= ${wildcard *.bist}
BREF		:= ${wildcard *.bref}
MODS		:= ${sort ${BIST:%.bist=%} ${BREF:%.bref=%}}
ERRS		:= ${MODS:%=%.berr}

check::			errs
errs::			${ERRS}
${ERRS}::	%.berr:         .FORCE
	@ if [ ! -f '$*.bref' ]; then printf 'result file "%s.bist" exists, and should not.\n' '$*'; exit 1; fi
	@ if [ ! -f '$*.bist' ]; then printf 'result file "%s.bist" should exist, but does not.\n' '$*'; exit 1; fi
	@ diff '$*.bist' '$*.bref' > '$*.berr' 
clean::		; $C $R *.berr

# -- ================================================================ --
#    Discard GCOV results outside this project

GCOV_WILD	:= ${wildcard *.gcov}
GCOV_WANT	:= ${SRCS:%.cc=%.cc.gcov} ${HDRS:%.hh=%.hh.gcov}

trimcov:
	$Q $R ${filter-out ${GCOV_WANT},${GCOV_WILD}}

# -- ================================================================ --
#    Generate Coverage Reports

cover::			covs
covs::			${LOGS}
	$P '[gcov everything]\n'
	$Q gcov *.gcno | awk -f gcov.awk
	$Q $(MAKE) trimcov
clean::		; $C $R *.gcov

# -- ================================================================ --
#    etc

.FORCE:
