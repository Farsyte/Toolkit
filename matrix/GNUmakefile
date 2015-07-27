-include GNUmakefile.std

LIB		= matrix

IMPORTLIBS      = matrix bist
SEARCHLIBD      = .

SRCS            := ${wildcard *.cc}
HDRS            := ${wildcard *.hh}
OBJS		:= ${SRCS:%.cc=%.o}
LIBA		:= ${LIB:%=lib%.a}
INST		:= ${HDRS:%=${TOPINC}%} ${LIBA:%=${TOPLIB}%}

# -- ================================================================ --
#    Compile C++ to Objects

build::			objs
objs::			${OBJS}
clean::		; $C $R ${OBJS} *.gcno *.gcda *.d

# -- ================================================================ --
#    Creation of the Static Library

LIBO            := ${OBJS}

${LIBA}:	${LIBO}
	$P '[ar] %s :: %s\n' '$@' '${LIBO}'
	$C $R '$@'
	$Q $(AR) c$(ARFLAGS) '$@' ${LIBO:%='%'} >/dev/null

liba::			${LIBA}
build::			liba
clean::		; $C $R ${LIBA}

# -- ================================================================ --
#    Export of Library and Headers

build::		install
install::	${INST}
${TOPINC}%:	%
	$P '[*inc*] %s\n' '$*'
	@ test -d ${TOPINC} || mkdir -p ${TOPINC}
	$Q cp '$*' '${TOPINC}$*'
${TOPLIB}%:	%
	@ test -d ${TOPLIB} || mkdir -p ${TOPLIB}
	$P '[*lib*] %s\n' '$*'
	$Q cp '$*' '${TOPLIB}$*'

clean::		uninstall
uninstall::	; $C $R ${INST}

# -- ================================================================ --
#    Generate Coverage Reports
#
# running test programs elsewhere writes the .gcno files here.

cover::			covs
covs::			.FORCE
	$P '[gcov %s]\n' '$(REL)*'
	$Q gcov *.gcno | awk -f ../bin/gcov.awk
	$Q $(MAKE) trimcov
GCOV_WILD	:= ${wildcard *.gcov}
GCOV_WANT	:= ${SRCS:%.cc=%.cc.gcov} ${HDRS:%.hh=%.hh.gcov}
trimcov:
	$C $R ${filter-out ${GCOV_WANT},${GCOV_WILD}}
clean::		; $C $R *.gcov
