#!/usr/bin/awk -f

BEGIN {
    triv = 0
    bad = 0
    semi = 0
    hi = 10
    lo = 3

    sorter = "sort -k1,1nr -k2,2nr -k3nr -k5nr -k6df"
}

$1<lo {
    triv ++
    next
}

{
    if ($1 >= hi)
        bad ++
    else
        semi ++

    rest = $6
    for (f = 7; f <= NF; ++f)
        rest = rest " " $f
    printf "%5d %7d %8d %7d %7d  %s\n", $1,$2,$3,$4,$5,rest | sorter
    next
}

{
    printf "%4d: %3d fields\n", NR, NF
    for (f = 1; f <= NF; ++f)
        printf "%6d: %s\n", f, $f
}

END {
    close (sorter)
    printf "\n"
    printf "%5d functions rated %d or higher\n", bad, hi
    printf "%5d functions rated below %d\n", triv, lo
    printf "%5d functions between thresholds", semi
    printf "\n"
}
