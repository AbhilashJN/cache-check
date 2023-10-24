#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef long int l_int;

float get_time_diff(struct timeval start, struct timeval end)
{
    unsigned long sec, usec;

    if (end.tv_usec < start.tv_usec)
    {
        usec = 1000000 + end.tv_usec - start.tv_usec;
        sec = end.tv_sec - start.tv_sec - 1;
    }
    else
    {
        usec = end.tv_usec - start.tv_usec;
        sec = end.tv_sec - start.tv_sec;
    }

    float total_time = (sec * 1000000 + usec) * 1000.0;

    return total_time;
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

    printf("Array Length: %ld, Array size: %ld B, Step size: %d, Stride size: %d B, run time %.2f ms\n",
           length, length * (sizeof(int)), step, step * sizeof(int), total_time);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("\nUsage: cache-level <array_length> <step_size>\n\n");
        printf("   - array_length: anumber of elements in the array to be used for the test.\n");
        printf("   - step_size: the number of array elements to be used as step size.\n");
        exit(-1);
    }

    int l = atoi(argv[1]);
    if (l < 1)
    {
        printf("Invalid array length\n");
        exit(-1);
    }

    int step = atoi(argv[2]);
    if (step < 1)
    {
        printf("Invalid step size\n");
        exit(-1);
    }

    l_int length = l;
    int *table = malloc(length * (sizeof(int)));
    for (l_int i = 0; i < length; i++)
    {
        table[i] = 1;
    }

    array_step_traverse(table, length, step);

    return 0;
}