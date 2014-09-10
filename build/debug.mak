# -*- makefile-gmake -*-

dump-make-variables:
	$(foreach V,                                            \
	     $(sort $(.VARIABLES)),                             \
	     $(if                                               \
	         $(filter-out environment% default automatic,   \
	             $(origin $V)),                             \
	         $(warning $V=$($V) ($(value $V)))              \
	      )                                                 \
	 )

.PHONY:         dump-make-variables
