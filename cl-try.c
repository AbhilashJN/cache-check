#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <time.h>
#include <assert.h>

typedef uint64_t my_int_t;

void mesureArrayMult(my_int_t *arr, size_t sz, size_t step)
{
    clock_t start_time = clock();

    for (size_t i = 0; i < sz; i += step)
    {
        arr[i] *= i;
    }

    double work_time_us = (clock() - start_time) * (1000. / CLOCKS_PER_SEC);
    printf("%4zd (%4zd): %7.3lfus\n", step, sizeof(my_int_t) * step, work_time_us);
}

int main()
{
    const size_t sz = 128 * 1024 * 1024;

    my_int_t *arr = (my_int_t *)malloc(sizeof(arr[0]) * sz);
    assert(arr);

    memset(arr, 1, sizeof(arr[0]) * sz);

    size_t i = 1;
    for (; i < 8; i += 1)
    {
        mesureArrayMult(arr, sz, i);
    }
    // for ( ; i<16; i+= 2) { mesureArrayMult( arr, sz, i ); }
    for (; i <= 1024; i *= 2)
    {
        mesureArrayMult(arr, sz, i);
    }

    free(arr);

    return 0;
}