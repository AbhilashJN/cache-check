#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KB 1024
#define MB 1024 * 1024

int gen_random_int()
{
    int randomnumber = rand() % 256;
    randomnumber += 128;

    return randomnumber;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("provide arg");
        exit(-1);
    }
    srand(time(NULL));

    int k = atoi(argv[1]);
    printf("k=%d\n", k);

    int arr_len = 64 * 1024 * 1024;
    int *arr = malloc(arr_len * sizeof(int));

    // for (int i = 0; i < arr_len; i += k)
    // {
    //     arr[i] *= 3;
    // }

    int i = 0, count = 0;
    clock_t tic = clock();
    while (count < 100000)
    {
        arr[i] *= 3;
        arr[i + k] *= 3;

        i += gen_random_int();
        count++;
    }
    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
}