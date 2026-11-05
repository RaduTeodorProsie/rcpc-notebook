# Name: Hash
# Description: Checks that a snippet was typed correctly. Setup,
#   once: type the three lines below into a file `hash.sh`. Then
#   run it on the lines of your solution where you typed the
#   snippet; it prints six characters, which must equal the six
#   next to the snippet's title. Comments and whitespace are
#   ignored, so they may differ.
# Usage: sh hash.sh sol.cpp 40 75   # lines 40 to 75 of sol.cpp
#   sh hash.sh sol.cpp         # the whole file
#   sh hash.sh                 # paste, then Ctrl-D
cat "${1:--}" | sed -n "${2:-1},${3:-\$}p" \
  | cpp -dD -P -fpreprocessed \
  | tr -d '[:space:]' | md5sum | cut -c-6
