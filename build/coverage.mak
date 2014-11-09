# -*- makefile-gmake -*-
clean::
	$C find . -name \*.gcov -exec /bin/rm -f \{\} +
	$C find . -name \*.gcno -exec /bin/rm -f \{\} +
	$C find . -name \*.gcda -exec /bin/rm -f \{\} +

wild.gcda       = $(shell find . -name \*.gcda -print)
wild.gcov       = $(shell find . -name \*.gcov -print)

uncov:
	/bin/rm -f ${wild.gcov}

UNAME_S          = $(shell uname -s)

coverage::
ifeq ($(wild.gcda),)
	$Q $P '%s: %s\n' '$*' 'no code coverage data recorded.'
else
	/bin/rm -f ${wild.gcov}
ifeq ($(UNAME_S),Darwin)
	gcov    -p ${wild.gcda}                 | \
	sed 'N;s/\n/ /' | grep "^File '"        | \
	grep -v "File '/Library/"               | \
	sed "s/^File '/coverage: /"             | \
	sed "s/' Lines executed:/ /"            | \
	sed "s/ of / /"                         | \
	column -t                               | \
	sed 's/\([0-9.]*% \)\( *\)/\2\1of /'    | \
	sort -u
else
	gcov -m -r ${wild.gcda}                 | \
	sed 'N;s/\n/ /' | grep "^File '"        | \
	sed "s/^File '/coverage: /"             | \
	sed "s/' Lines executed:/ /"            | \
	sed "s/ of / /"                         | \
	column -t                               | \
	sed 's/\([0-9.]*% \)\( *\)/\2\1of /'    | \
	sort -u
endif
endif
