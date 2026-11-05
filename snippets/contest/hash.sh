# Name: Hash
# Description: Hashes code ignoring whitespace and comments.
#   Compare with the six characters next to each title.
# Usage: sh hash.sh < file.cpp
cpp -dD -P -fpreprocessed | tr -d '[:space:]' \
  | md5sum | cut -c-6
