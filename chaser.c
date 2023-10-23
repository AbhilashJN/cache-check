#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define KB 1024
#define MB 1024 * 1024

typedef long int l_int;

l_int gen_random_int(l_int max)
{
    l_int rand_int = rand() % max;
    return rand_int + 1;
}

void shuffle_indices(l_int *indices, l_int length)
{
    for (l_int i = 0; i < length - 1; i++)
    {
        l_int swap_index = i + gen_random_int(length - i - 1);
        if (swap_index != i)
        {
            l_int tmp = indices[i];
            indices[i] = indices[swap_index];
            indices[swap_index] = tmp;
        }
    }
}

void setup_pointer_path(int **table, l_int *indices, l_int length)
{
    for (l_int i = 0; i < length - 1; i++)
    {
        table[indices[i]] = (int *)&table[indices[i + 1]];
    }
    table[indices[length - 1]] = (int *)&table[indices[0]];
}

int **create_pointer_table(l_int length)
{
    int **table = malloc(length * (sizeof(int *)));
    l_int *indices = malloc(length * (sizeof(l_int)));
    for (l_int i = 0; i < length; i++)
    {
        indices[i] = i;
    }

    shuffle_indices(indices, length);
    setup_pointer_path(table, indices, length);

    free(indices);
    return table;
}

void run_pointer_chase(int **table, l_int length, l_int iterations)
{
    struct timeval tv1, tv2;
    unsigned long sec, usec;

    gettimeofday(&tv1, NULL);

    register int **p = (int **)table;

    for (l_int i = 0; i < iterations; i++)
    {
        p = (int **)*p;
    }

    gettimeofday(&tv2, NULL);

    int **touch = p;

    if (tv2.tv_usec < tv1.tv_usec)
    {
        usec = 1000000 + tv2.tv_usec - tv1.tv_usec;
        sec = tv2.tv_sec - tv1.tv_sec - 1;
    }
    else
    {
        usec = tv2.tv_usec - tv1.tv_usec;
        sec = tv2.tv_sec - tv1.tv_sec;
    }

    printf("Buffer size: %ld B, time %d.%06d s, latency %.2f ns\n",
           length * (sizeof(int *)), sec, usec, (sec * 1000000 + usec) * 1000.0 / (iterations));
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("provide arg");
        exit(-1);
    }
    int l = atoi(argv[1]);

    l_int length = l;
    l_int iterations = 1000000000;
    int **table = create_pointer_table(length);
    run_pointer_chase(table, length, iterations);
    return 0;
}