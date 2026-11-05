# Name: Stress test
# Description: Runs `sol` and `brute` on tests from `gen`
#   (seeded by the test number) until the outputs differ.
# Usage: ./stress.sh 1000
for i in $(seq 1 ${1:-500}); do
  ./gen $i > in
  ./sol < in > o1
  ./brute < in > o2
  if ! cmp -s o1 o2; then
    echo "mismatch on seed $i"; cat in; exit 1
  fi
done
echo "all passed"
