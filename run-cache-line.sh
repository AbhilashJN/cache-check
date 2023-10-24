#set -x

prog=./cache-line
buffer_size=163840000
step_sizes=( 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 24 32 40 48 56 64 80 96 128 )

for i in "${step_sizes[@]}"; do
    taskset -ac 0 $prog $buffer_size $i
done