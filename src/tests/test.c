#include <stdio.h>
#include <stdint.h>
#include "encodec.h"
#include "rgb2ycbcr.h"
#include "ycbcr2rgb.h"
#include "helpers.h"
#define BLOCK_SIZE 8

int main() {
    // Step 1: Create a dummy RGB block
    uint8_t r[BLOCK_SIZE][BLOCK_SIZE];
    uint8_t g[BLOCK_SIZE][BLOCK_SIZE];
    uint8_t b[BLOCK_SIZE][BLOCK_SIZE];

    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            r[i][j] = (i * 32 + j * 4) % 256; // some pattern
            g[i][j] = (i * 16 + j * 8) % 256;
            b[i][j] = (i * 8  + j * 16) % 256;
        }
    }

    // Step 2: Encode
    Block8x8_Coeffs coeffs;
    encode_block_8x8_444(r, g, b, &coeffs);

    // Step 3: Decode
    uint8_t r_out[BLOCK_SIZE][BLOCK_SIZE];
    uint8_t g_out[BLOCK_SIZE][BLOCK_SIZE];
    uint8_t b_out[BLOCK_SIZE][BLOCK_SIZE];
    decode_block_8x8_444(&coeffs, r_out, g_out, b_out);

    // Step 4: Print original vs decoded
    printf("Original vs Decoded R channel:\n");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            printf("%3d/%3d ", r[i][j], r_out[i][j]);
        }
        printf("\n");
    }

    printf("\nOriginal vs Decoded G channel:\n");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            printf("%3d/%3d ", g[i][j], g_out[i][j]);
        }
        printf("\n");
    }

    printf("\nOriginal vs Decoded B channel:\n");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            printf("%3d/%3d ", b[i][j], b_out[i][j]);
        }
        printf("\n");
    }

    return 0;
}
