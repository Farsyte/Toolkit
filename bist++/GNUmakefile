LIB		:= bist

-include GNUmakefile.std

LDLIBS		+= ${LIB:%=-l%}
LDFLAGS		+= -L.

SRCS            := ${wildcard *.cc}
HDRS            := ${wildcard *.hh}
OBJS		:= ${SRCS:%.cc=%.o}
PGMS		:= BistBist
SUBS		:= ${filter-out ${PGMS:%=%.o},${OBJS}}
LOGS		:= ${PGMS:%=%.log}

# -- ================================================================ --
#    Compile C++ to Objects

build::			objs
objs::			${OBJS}
clean::		; $C $R ${OBJS} *.gcno *.d

# -- ================================================================ --
#    Creation of the Static Library

LIBO            := ${SUBS}
LIBA		:= ${LIB:%=lib%.a}

${LIBA}:	${LIBO:%=${LIBA}(%)}
liba::			${LIBA}
build::			liba
clean::		; $C $R ${LIBA}

# -- ================================================================ --
#    Link Objects into Programs

build::			pgms
pgms::			${PGMS}
${PGMS}:		${LIBA}
${PGMS}:        %:              %.o
	$P '[ld] %s\n' '$(REL)$*'
	$Q $(LINK.cc) $*.o ${SUBS} $(LOADLIBES) $(LDLIBS) -o $@
clean::		; $C $R ${PGMS}

# -- ================================================================ --
#    Collect outputs of programs

execs::			logs
logs::			${LOGS}
${LOGS}:        %.log:           %
	$P '[go] %s\n' '$(REL)$*'
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
	$P '[gcov %s]\n' '$(REL)*'
	$Q gcov *.gcno | awk -f gcov.awk
	$Q $(MAKE) trimcov
clean::		; $C $R *.gcov

# -- ================================================================ --
#    Export of Library and Headers

install::	${LIBA}
	@ test -d ../lib || mkdir -p ../lib
	cp ${LIBA} ../lib
	@ test -d ../inc || mkdir -p ../inc
	cp ${HDRS} ../inc

# -- ================================================================ --
#    etc

.FORCE:
