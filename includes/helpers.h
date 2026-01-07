// block444.h - Encode/Decode 8x8x3 RGB blocks using your codec
#ifndef BLOCK444_H
#define BLOCK444_H

#include <stdint.h>

#define BLOCK_SIZE 8
#define ZZ 64

#ifdef __cplusplus
extern "C" {
#endif

// -------------------------------
// Structure to hold encoded block
// -------------------------------
typedef struct {
    int16_t q_y[ZZ];   // Quantized Y coefficients
    int16_t q_cb[ZZ];  // Quantized Cb coefficients
    int16_t q_cr[ZZ];  // Quantized Cr coefficients
    uint8_t mean_y;    // Mean for Y
    uint8_t mean_cb;   // Mean for Cb
    uint8_t mean_cr;   // Mean for Cr
} Block8x8_Coeffs;

// -------------------------------
// Encode a 8x8x3 RGB block
// r, g, b: input RGB channels (8x8)
// block: output encoded structure
// -------------------------------
void encode_block_8x8_444(
    const uint8_t r[BLOCK_SIZE][BLOCK_SIZE],
    const uint8_t g[BLOCK_SIZE][BLOCK_SIZE],
    const uint8_t b[BLOCK_SIZE][BLOCK_SIZE],
    Block8x8_Coeffs *block
);

// -------------------------------
// Decode a 8x8x3 RGB block
// block: input encoded structure
// r, g, b: output RGB channels (8x8)
// -------------------------------
void decode_block_8x8_444(
    const Block8x8_Coeffs *block,
    uint8_t r[BLOCK_SIZE][BLOCK_SIZE],
    uint8_t g[BLOCK_SIZE][BLOCK_SIZE],
    uint8_t b[BLOCK_SIZE][BLOCK_SIZE]
);

#ifdef __cplusplus
}
#endif

#endif // BLOCK444_H
