#include <stdint.h>
#include <math.h>
#include "dct.h"
#include "quant.h"
#include "tables.h"
#include "mean.h"
#include "median.h"

#define BLOCK_SIZE 8
#define ZZ 64

// Encode 8x8 chroma block
void encode_chroma_block(const uint8_t y[BLOCK_SIZE][BLOCK_SIZE], int16_t qzz[ZZ], uint8_t *mean_out) {
    float shifted[BLOCK_SIZE][BLOCK_SIZE];
    uint8_t m = mean(y);           // mean of block
    *mean_out = m;

    // Level shift
    for (int i = 0; i < BLOCK_SIZE; i++)
        for (int j = 0; j < BLOCK_SIZE; j++)
            shifted[i][j] = (float)y[i][j] - (float)m;

    // 2D DCT
    float dct_out[BLOCK_SIZE][BLOCK_SIZE];
    dct8x8(shifted, dct_out);

    // Zigzag flatten
    float dct_zz[ZZ];
    for (int i = 0; i < ZZ; i++)
        dct_zz[i] = dct_out[zigzag[i] / BLOCK_SIZE][zigzag[i] % BLOCK_SIZE];

    // Quantize using luminance table
    quantize_block(dct_zz, qzz, quant_chroma_zz);
    qzz[0] = m;
}

// Decode 8x8 chroma block
void decode_chroma_block(const int16_t qzz[ZZ], uint8_t y[BLOCK_SIZE][BLOCK_SIZE], uint8_t mean_val) {
    // Dequantize
    uint8_t mean_value = qzz[0];
    float dct_zz[ZZ];
    dequantize_block(qzz, dct_zz, quant_chroma_zz);
    dct_zz[0] = 0;
    // Unzigzag
    float dct2d[BLOCK_SIZE][BLOCK_SIZE];
    for (int i = 0; i < ZZ; i++)
        dct2d[zigzag[i] / BLOCK_SIZE][zigzag[i] % BLOCK_SIZE] = dct_zz[i];

    // 2D IDCT
    float idct_out[BLOCK_SIZE][BLOCK_SIZE];
    idct8x8(dct2d, idct_out);

    // Add mean back and clamp
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            int val = (int)lroundf(idct_out[i][j] + (float)mean_value);
            if (val < 0) val = 0;
            if (val > 255) val = 255;
            y[i][j] = (uint8_t)val;
        }
    }
}
