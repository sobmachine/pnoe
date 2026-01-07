// ycbcr2rgb.h
#ifndef YCBCR2RGB_H
#define YCBCR2RGB_H

#include <stdint.h>
#define N 8

#ifdef __cplusplus
extern "C" {
#endif

// Convert 8x8 YCbCr block back to RGB
// y, cb, cr: input 8x8 blocks (0-255)
// r, g, b: output 8x8 RGB blocks (0-255)
void ycbcr2rgb_block(
    const uint8_t y[N][N],
    const uint8_t cb[N][N],
    const uint8_t cr[N][N],
    uint8_t r[N][N],
    uint8_t g[N][N],
    uint8_t b[N][N]
);

#ifdef __cplusplus
}
#endif
#endif
