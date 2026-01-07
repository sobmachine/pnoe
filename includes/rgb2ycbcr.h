// rgb2ycbcr.h
#ifndef RGB2YCBCR_H
#define RGB2YCBCR_H

#include <stdint.h>
#define N 8

#ifdef __cplusplus
extern "C" {
#endif

// Convert 8x8 RGB block to Y, Cb, Cr blocks
// r,g,b: input 8x8 RGB arrays (0-255)
// y, cb, cr: output 8x8 Y, Cb, Cr arrays (0-255)
void rgb2ycbcr_block(
    const uint8_t r[N][N],
    const uint8_t g[N][N],
    const uint8_t b[N][N],
    uint8_t y[N][N],
    uint8_t cb[N][N],
    uint8_t cr[N][N]
);

#ifdef __cplusplus
}
#endif
#endif
