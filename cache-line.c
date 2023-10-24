#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <time.h>
#include <sys/time.h>
#include <assert.h>

typedef long int l_int;

int *create_pointer_table(l_int length, l_int step)
{
    int *table = malloc(length * (sizeof(int)));

    return table;
}

void array_step_traverse(int *array, l_int length, int step)
{
    struct timeval tv1, tv2;
    unsigned long sec, usec;

    gettimeofday(&tv1, NULL);

    for (l_int i = 0; i < length; i += step)
    {
        array[i] *= i;
    }
    gettimeofday(&tv2, NULL);

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

    float total_time = (sec * 1000000 + usec) / 1000.0;

    printf("Array Length: %ld, Buffer size: %ld B, Step size: %d, Int size: %d, latency %.2f ms\n",
           length, length * (sizeof(int)), step, sizeof(int), total_time);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("provide arg");
        exit(-1);
    }
    int l = atoi(argv[1]);
    int s = atoi(argv[2]);

    l_int length = l;
    int step = s;
    l_int iterations = 100;
    int *table = create_pointer_table(length, step);

    for (l_int i = 0; i < length; i++)
    {
        table[i] = 1;
    }

    array_step_traverse(table, length, step);
    return 0;
}