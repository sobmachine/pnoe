// DCT.h - Orthonormal 8x8 DCT / IDCT (float)
#ifndef DCT_H
#define DCT_H

#define N 8

#ifdef __cplusplus
extern "C" {
#endif

// -------- 1D DCT / IDCT --------
void dct(const float x[N], float y[N]);
void idct(const float x[N], float y[N]);

// -------- 2D DCT / IDCT --------
void dct8x8(const float in[N][N], float out[N][N]);
void idct8x8(const float in[N][N], float out[N][N]);

#ifdef __cplusplus
}
#endif

#endif // DCT_H
