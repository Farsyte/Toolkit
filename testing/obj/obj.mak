# -*- makefile-gmake -*-
clean::
	$C $R testing/obj/*.o
	$C $R testing/obj/*.gcda
	$C $R testing/obj/*.gcno
