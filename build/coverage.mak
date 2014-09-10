# -*- makefile-gmake -*-
clean::
	$C find . -name \*.gcov -exec /bin/rm -f \{\} +
	$C find . -name \*.gcno -exec /bin/rm -f \{\} +
	$C find . -name \*.gcda -exec /bin/rm -f \{\} +
