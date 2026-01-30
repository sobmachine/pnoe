// rgb2ycbcr.c
#include "rgb2ycbcr.h"
#include <stdint.h>

#define CLAMP_8(x) ((x) < 0 ? 0 : ((x) > 255 ? 255 : (x)))

void rgb2ycbcr_block(
    const uint8_t r[N][N],
    const uint8_t g[N][N],
    const uint8_t b[N][N],
    uint8_t y[N][N],
    uint8_t cb[N][N],
    uint8_t cr[N][N]
) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            int R = r[i][j];
            int G = g[i][j];
            int B = b[i][j];

            // BT.601 full-range forward conversion
            //
            // Y  =  0.299000 R + 0.587000 G + 0.114000 B
            // Cb = -0.168736 R - 0.331264 G + 0.500000 B + 128
            // Cr =  0.500000 R - 0.418688 G - 0.081312 B + 128

            int Y  = (19595 * R + 38470 * G +  7471 * B + 32768) >> 16;
            int Cb = (-11056 * R - 21712 * G + 32768 * B + 32768) >> 16;
            int Cr = (32768 * R - 27440 * G -  5328 * B + 32768) >> 16;

            y[i][j]  = CLAMP_8(Y);
            cb[i][j] = CLAMP_8(Cb + 128);
            cr[i][j] = CLAMP_8(Cr + 128);
        }
    }
}
