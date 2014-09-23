#!/bin/bash -
#
# Messy messy messy, for CLion and cmake.
#
# In order to use the "Run" button
# to do pmccabe analysis, I need a target that
# builds a progarm that when run will
# run the tests.
#
# Oh well, at least this gives me a neat way
# to deal with not finding pmccabe, without
# diving into CMake details (yet).

rm -f pmccabe
pmc=$(which pmccabe)
cat > pmccabe << EOF
#!/bin/bash -
cd "$1"

$pmc -v    < /dev/null |
sed 's/^/    /'

find . -name '.??*' -prune -o \
    \( -name '*.cc' \
    -o -name '*.h' \
    \) -type f -print |
sed 's|^[.]/||' |
tr '\n' '\0' |
xargs -0 $pmc |
awk -f bin/pmccabe.awk
EOF
chmod 0755 pmccabe
# cat ./pmccabe | sed 's/^/#xxx#\t/'
