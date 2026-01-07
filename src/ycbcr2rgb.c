// ycbcr2rgb.c
#include "ycbcr2rgb.h"

// Standard ITU-R BT.601 inverse conversion
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

            // integer approximation
            int R = Y + ((256 * Cr) >> 8);                   // ~Y + 1.402*Cr
            int G = Y - (( 44 * Cb +  91 * Cr) >> 8);       // ~Y - 0.34414*Cb -0.71414*Cr
            int B = Y + ((357 * Cb) >> 8);                  // ~Y + 1.772*Cb

            // clamp 0..255
            r[i][j] = (R < 0) ? 0 : (R > 255 ? 255 : R);
            g[i][j] = (G < 0) ? 0 : (G > 255 ? 255 : G);
            b[i][j] = (B < 0) ? 0 : (B > 255 ? 255 : B);
        }
    }
}
