#ifndef CODEC_CHROMA_H
#define CODEC_CHROMA_H

#include <stdint.h>

#define BLOCK_SIZE 8
#define ZZ 64

#ifdef __cplusplus
extern "C" {
#endif

void encode_chroma_block(const uint8_t y[BLOCK_SIZE][BLOCK_SIZE], int16_t qcoeffs[ZZ], uint8_t *mean);
void decode_chroma_block(const int16_t qcoeffs[ZZ], uint8_t y[BLOCK_SIZE][BLOCK_SIZE], uint8_t mean);

#ifdef __cplusplus
}
#endif

#endif // CODEC_H
