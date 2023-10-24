#set -x

prog=./cache-line
buffer_size=163840000
step_sizes=( 1 2 4 8 16 18 20 24 28 32 64 128)

for i in "${step_sizes[@]}"; do
    taskset -ac 0 $prog $buffer_size $i
done