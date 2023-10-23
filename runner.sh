#set -x

work=./chaser
buffer_size=1

for i in `seq 1 25`; do
    taskset -ac 0 $work $buffer_size
    buffer_size=$(($buffer_size*2))
done