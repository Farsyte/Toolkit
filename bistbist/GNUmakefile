-include GNUmakefile.std

IMPORTLIBS      = bist
SEARCHLIBD      = ../lib
SEARCHINCD      = ../inc

SRCS            := ${wildcard *.cc}
HDRS            := ${wildcard *.hh}
OBJS		:= ${SRCS:%.cc=%.o}
PGMS		:= BistBist
INST		:= ${PGMS:%=${TOPBIN}%}
LOGS		:= ${PGMS:%=%.log}

# -- ================================================================ --
#    Compile C++ to Objects

build::			objs
objs::			${OBJS}
clean::		; $C $R ${OBJS} *.gcno *.d

# -- ================================================================ --
#    Link Objects into Programs

build::			pgms
pgms::			${PGMS}
${PGMS}:		${LIBA}
${PGMS}:        %:              %.o
	$P '[ld] %s\n' '$(REL)$*'
	$Q $(LINK.cc) $*.o $(LOADLIBES) $(LDLIBS) -o $@
clean::		; $C $R ${PGMS}

build::			install
${TOPBIN}%:		%
	@ test -d ${TOPBIN} || mkdir -p ${TOPBIN}
	$P '[*bin*] %s\n' '$*'
	$Q cp '$*' ${TOPBIN}'$*'
install::		${INST}
uninstall::	; $C $R ${INST}
clean::			uninstall

# -- ================================================================ --
#    Collect outputs of programs

execs::			logs
logs::			${LOGS}
${LOGS}:        %.log:           ${TOPBIN}%
	$P '[go] %s\n' '$(REL)$*'
	$Q '${TOPBIN}$*' 2>&1 | tee '$@'
clean::		; $C $R *.bist *.gcda ${LOGS}

# -- ================================================================ --
#    Verify BIST log outputs

BIST		:= ${wildcard *.bist}
ERRS		:= ${BIST:%.bist=%.berr}

check::			errs
errs::			${ERRS}
${ERRS}::	%.berr:         .FORCE
	@ diff '${TOPREF}$*.bist' '$*.bist' > '$*.berr' 
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
	$Q gcov *.gcno | awk -f ../bin/gcov.awk
	$Q $(MAKE) trimcov
clean::		; $C $R *.gcov
