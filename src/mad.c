// MAD.c - Mean Absolute Deviation
#include <stdint.h>
#include <stdlib.h> // abs

#define N 8

uint8_t mad(const uint8_t blk[N][N], uint8_t mean) {
    int sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sum += abs((int)blk[i][j] - mean);
    return sum >> 6; // divide by 64
}
