#!/usr/bin/awk -f

/^File '\// {
    r = ""
    next
}

/^File/ {
    r = $2
    for (f = 3; f <= NF; ++f)
        r = r " " $f
    sub(/^'/, "", r)
    sub(/'$/, "", r)
    sub(/^\.\//, "", r)
    next
}

/^Lines/ {
    if (r == "")
        next
    p = $2
    sub(/executed:/, "", p)
    sub(/%/, "", p)
    t = $NF
    x = (1 - p/100) * t
    printf "%7.0f %8.2f %% of %5d in %s\n", x, p, t, r
    next
}

{
    r = ""
    next
}
