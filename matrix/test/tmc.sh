#!/bin/bash -

for L in I A B C D E F
do
cat <<EOF

    + case_T("($L == $L) is True",  ($L == $L))
    + case_F("($L != $L) is False", ($L != $L))
EOF
    for R in I A B C D E F
    do
	test $L == $R ||
	cat <<EOF
    + case_T("($L != $R) is True",  ($L != $R))
    + case_F("($L == $L) is False", ($L == $R))
EOF
    done
done
