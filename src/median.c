// MEDIAN.c - Median of 8x8 block
#include <stdint.h>
#include <stdlib.h> // for qsort
#define N 8

// Comparison function for qsort
static int cmp_uint8(const void *a, const void *b) {
    return (*(uint8_t*)a) - (*(uint8_t*)b);
}

// Compute median
uint8_t median(const uint8_t blk[N][N]) {
    uint8_t tmp[N*N];
    int idx = 0;

    // Flatten 8x8 to 64-element array
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tmp[idx++] = blk[i][j];

    // Sort the array
    qsort(tmp, N*N, sizeof(uint8_t), cmp_uint8);

    // Return middle value (for 64 elements, average of 31 & 32)
    return (tmp[31] + tmp[32]) >> 1;
}
