# Name: Hash
# Description: Hashes code ignoring whitespace and comments;
#   compare with the six characters next to each title. Give a
#   line range to hash only the snippet inside a bigger file.
# Usage: sh hash.sh sol.cpp         # whole file
#   sh hash.sh sol.cpp 40 75   # only lines 40 to 75
#   sh hash.sh < sol.cpp       # or paste, then Ctrl-D
cat "${1:--}" | sed -n "${2:-1},${3:-\$}p" \
  | cpp -dD -P -fpreprocessed \
  | tr -d '[:space:]' | md5sum | cut -c-6
