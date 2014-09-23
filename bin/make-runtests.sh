#!/bin/bash -
#
# Messy messy messy, for CLion and cmake.
#
# In order to use the "Run" button
# to rerun tests, I need a target that
# builds a progarm that when run will
# run the tests.

cat > runtests << \EOF
#!/bin/bash -
ctest "$@"
es="$?"
home=$(cd ; env PWD= /bin/pwd)
here=$(     env PWD= /bin/pwd | sed "s|^$home/||")
cat << EOM

:::::::::::::::: build results ::::::::::::::::
$here
searching for test_*_log.xml ...
EOM
find . -name 'test_*_log.xml' -print 2>/dev/null | sed 's|^[.]/|    |'
exit "$es"
EOF
chmod 0755 runtests
