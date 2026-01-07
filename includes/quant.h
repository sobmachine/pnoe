#ifndef QUANT_H
#define QUANT_H

#include <stdint.h>

#define N 8
#define ZZ 64

#ifdef __cplusplus
extern "C" {
#endif

// Quantize zigzag-ordered DCT coefficients
void quantize_block(
    const float dct_zz[ZZ],
    int16_t qcoeffs[ZZ],
    const uint8_t qtable[ZZ]
);

// Dequantize zigzag-ordered coefficients
void dequantize_block(
    const int16_t qcoeffs[ZZ],
    float dct_zz[ZZ],
    const uint8_t qtable[ZZ]
);

#ifdef __cplusplus
}
#endif

#endif // QUANT_H
