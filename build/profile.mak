# -*- makefile-gmake -*-
clean::
	$C find . -name gmon.out -exec /bin/rm -f \{\} +
