// rgb2ycbcr.c
#include "rgb2ycbcr.h"

// Standard ITU-R BT.601 conversion
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
            uint8_t R = r[i][j];
            uint8_t G = g[i][j];
            uint8_t B = b[i][j];

            // Y channel
            int Y  = (  77 * R + 150 * G +  29 * B ) >> 8; // approx 0.299,0.587,0.114
            // Cb channel
            int Cb = ((-43 * R -  85 * G + 128 * B) >> 8) + 128; // approx -0.1687,-0.3313,0.5
            // Cr channel
            int Cr = ((128 * R - 107 * G -  21 * B) >> 8) + 128; // approx 0.5,-0.4187,-0.0813

            // clamp 0..255
            y[i][j]  = (Y  < 0) ? 0 : (Y  > 255 ? 255 : Y);
            cb[i][j] = (Cb < 0) ? 0 : (Cb > 255 ? 255 : Cb);
            cr[i][j] = (Cr < 0) ? 0 : (Cr > 255 ? 255 : Cr);
        }
    }
}
