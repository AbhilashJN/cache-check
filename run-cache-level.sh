#set -x

prog=./cache-level
buffer_size=1
b_array_lengths=( 1 2 4 8 16 32 64 128 256 512 )
kb_array_lengths=( 1 2 4 8 16 32 64 128 256 512 )
mb_array_lengths=( 1 2 3 )

for i in "${b_array_lengths[@]}"; do
    taskset -ac 0 $prog $i
done

for i in "${kb_array_lengths[@]}"; do
    taskset -ac 0 $prog $((i * 1024))
done

for i in "${mb_array_lengths[@]}"; do
    taskset -ac 0 $prog $((i * 1024 * 1024))
done