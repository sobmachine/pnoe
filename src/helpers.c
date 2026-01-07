#include "encodec.h"
#include "rgb2ycbcr.h"
#include "ycbcr2rgb.h"
#include <stdint.h>

#define BLOCK_SIZE 8
#define ZZ 64

typedef struct {
    int16_t yq[ZZ];
    int16_t cbq[ZZ];
    int16_t crq[ZZ];
    uint8_t ymean;
    uint8_t cbmean;
    uint8_t crmean;
} Block8x8_Coeffs;

// Encode 8x8 RGB block -> DCT coefficients + means
void encode_block_8x8_444(
    const uint8_t r[BLOCK_SIZE][BLOCK_SIZE],
    const uint8_t g[BLOCK_SIZE][BLOCK_SIZE],
    const uint8_t b[BLOCK_SIZE][BLOCK_SIZE],
    Block8x8_Coeffs *out
) {
    uint8_t y[BLOCK_SIZE][BLOCK_SIZE], cb[BLOCK_SIZE][BLOCK_SIZE], cr[BLOCK_SIZE][BLOCK_SIZE];

    // Convert RGB -> YCbCr
    rgb2ycbcr_block(r, g, b, y, cb, cr);

    // Encode each channel
    encode_luma_block(y, out->yq, &out->ymean);
    encode_chroma_block(cb, out->cbq, &out->cbmean);
    encode_chroma_block(cr, out->crq, &out->crmean);
}

// Decode 8x8 DCT coefficients -> RGB block
void decode_block_8x8_444(
    const Block8x8_Coeffs *in,
    uint8_t r[BLOCK_SIZE][BLOCK_SIZE],
    uint8_t g[BLOCK_SIZE][BLOCK_SIZE],
    uint8_t b[BLOCK_SIZE][BLOCK_SIZE]
) {
    uint8_t y[BLOCK_SIZE][BLOCK_SIZE], cb[BLOCK_SIZE][BLOCK_SIZE], cr[BLOCK_SIZE][BLOCK_SIZE];

    // Decode each channel
    decode_luma_block(in->yq, y, in->ymean);
    decode_chroma_block(in->cbq, cb, in->cbmean);
    decode_chroma_block(in->crq, cr, in->crmean);

    // Convert YCbCr -> RGB
    ycbcr2rgb_block(y, cb, cr, r, g, b);
}
