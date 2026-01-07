#include "quant.h"
#include <math.h>   // lroundf

void quantize_block(
    const float dct_zz[ZZ],
    int16_t qcoeffs[ZZ],
    const uint8_t qtable[ZZ]
) {
    for (int i = 0; i < ZZ; i++) {
        qcoeffs[i] = (int16_t)lroundf(dct_zz[i] / (float)qtable[i]);
    }
}

void dequantize_block(
    const int16_t qcoeffs[ZZ],
    float dct_zz[ZZ],
    const uint8_t qtable[ZZ]
) {
    for (int i = 0; i < ZZ; i++) {
        dct_zz[i] = (float)qcoeffs[i] * (float)qtable[i];
    }
}
