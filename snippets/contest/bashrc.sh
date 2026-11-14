# Name: Bashrc
# Description: Append to `~/.bashrc`, then `source ~/.bashrc`.
#   `cs sol.cpp` compiles to `./sol` with warnings, debug info
#   and sanitizers; run it with `./sol < in`. The `ulimit`
#   line gives deep recursion a 1 GB stack.
cs() {
  g++ -std=gnu++20 -Wall -Wextra -Wshadow -g \
    -fsanitize=address,undefined -o "${1%.cpp}" "$1"
}
ulimit -s 1000000
