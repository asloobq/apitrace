sed -n -e 's/^\s\+\(EGL_\)\?\(\S\+\)\s*=\s*\(0x3\w\w\w\)\s*\(#.*\)\?$/\3 \2/p' "$@" \
| sort -u \
| sed -e 's/\(\S\+\)\s\+\(\S\+\)/    "EGL_\2",\t\t# \1/'