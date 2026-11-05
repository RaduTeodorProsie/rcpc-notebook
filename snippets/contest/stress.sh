# Name: Stress test
# Description: Runs `sol` and `brute` on `gen.py` tests until
#   they disagree (default 500 tests). A third argument switches
#   to a checker: `./check in o1 o2` exits with 0 if `o1` is ok.
# Usage: ./stress.sh 1000 "tree n=6 w=9"
#   ./stress.sh 1000 "graph n=5" check
N=${1:-500}
g++ -O2 -o sol sol.cpp || exit 1
g++ -O2 -o brute brute.cpp || exit 1
for i in $(seq 1 $N); do
  python3 gen.py $i $2 > in || exit 1
  if ! ./sol < in > o1 || ! ./brute < in > o2; then
    echo "crash on seed $i:"; cat in; exit 1
  fi
  if [ -n "$3" ]; then ./$3 in o1 o2; else cmp -s o1 o2; fi
  if [ $? -ne 0 ]; then
    echo "seed $i:"; cat in; diff o1 o2 | head; exit 1
  fi
done
echo "all $N passed"
