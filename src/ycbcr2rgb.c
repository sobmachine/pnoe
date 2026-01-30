// ycbcr2rgb.c
#include "ycbcr2rgb.h"
#include <stdint.h>

// BT.601 full-range inverse conversion
// Uses 16-bit fixed-point math with proper rounding
// This is VERY close to float accuracy

#define CLAMP_8(x) ((x) < 0 ? 0 : ((x) > 255 ? 255 : (x)))

void ycbcr2rgb_block(
    const uint8_t y[N][N],
    const uint8_t cb[N][N],
    const uint8_t cr[N][N],
    uint8_t r[N][N],
    uint8_t g[N][N],
    uint8_t b[N][N]
) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            int Y  = y[i][j];
            int Cb = cb[i][j] - 128;
            int Cr = cr[i][j] - 128;

            // 16-bit fixed-point coefficients (BT.601)
            // R = Y + 1.402 * Cr
            // G = Y - 0.344136 * Cb - 0.714136 * Cr
            // B = Y + 1.772 * Cb

            int R = Y + ((91881 * Cr + 32768) >> 16);
            int G = Y - ((22554 * Cb + 46802 * Cr + 32768) >> 16);
            int B = Y + ((116130 * Cb + 32768) >> 16);

            r[i][j] = CLAMP_8(R);
            g[i][j] = CLAMP_8(G);
            b[i][j] = CLAMP_8(B);
        }
    }
}
