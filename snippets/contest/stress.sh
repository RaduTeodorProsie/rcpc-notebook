# Name: Stress test
# Description: Runs `sol` and `brute` on tests from a generator
#   (with its maxima, if any) until they disagree; 500 tests by
#   default. A third argument switches to a checker:
#   `./check in o1 o2` exits with 0 if `o1` is ok.
# Usage: ./stress.sh gen_tree.py
#   ./stress.sh "gen_graph.py 5 6 0 1" 1000 check
N=${2:-500}
G=${1%% *}; A=${1#"$G"}
g++ -O2 -o sol sol.cpp || exit 1
g++ -O2 -o brute brute.cpp || exit 1
for i in $(seq 1 $N); do
  python3 $G $i $A > in || exit 1
  if ! ./sol < in > o1 || ! ./brute < in > o2; then
    echo "crash on seed $i:"; cat in; exit 1
  fi
  if [ -n "$3" ]; then ./$3 in o1 o2; else cmp -s o1 o2; fi
  if [ $? -ne 0 ]; then
    echo "seed $i:"; cat in; diff o1 o2 | head; exit 1
  fi
done
echo "all $N passed"
