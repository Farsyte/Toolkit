p#!/usr/bin/awk -f
#
# Reduce the size of "make" output logs
#   - join lines separated by backslash
#   - drop excess Entering and Leaving messages

BEGIN {
    idir = ""
    odir = ""
    pend = ""
    last_output_endl = "\n"
}

function text(t) {
    if (last_output_endl == "")
	sub(/^[ \t]+/, "", t)
    if (t ~ /\\$/) {
        sub(/[ \t]+\\$/, " ", t)
        last_output_endl = ""
    } else
        last_output_endl = "\n"
    printf "%s%s", t, last_output_endl
}

(last_output_endl != "\n") {
    printf " "
    text($0)
    next
}

# /^make: Nothing to be done for /                        { next }
# /^make: \*\*\* \[.*\] Error [0-9]+$/                    { next }
# /^make: `.*' is up to date.$/                           { next }

# /^make\[[0-9]+\]: Nothing to be done for /              { next }
# /^make\[[0-9]+\]: \*\*\* \[.*\] Error [0-9]+$/          { next }
# /^make\[[0-9]+\]: \[.*\] Error [0-9]+ [(]ignored[)]$/   { next }
# /^make\[[0-9]+\]: `.*' is up to date.$/                 { next }

/^make(\[[0-9]+\])?: Entering directory / {
    itag = $1; mdir[itag] = idir
    idir = $4; for (f = 5; f <= NF; ++f) idir = idir " " $f
    next
}

/^make(\[[0-9]+\])?: Leaving directory / {
    itag = $1
    idir = mdir[itag = $1]
    next
}

{ 
    if (idir != odir) {
        printf "\n"
        odir = idir
        if (idir != "")
            printf "make: Entering directory %s\n", odir
    }

    text($0)
    next
}
