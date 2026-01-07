// DCT.c - Orthonormal 8x8 DCT / IDCT (float)
#include <math.h>

#define N 8

// α(u) factor for orthonormal DCT
static inline float alpha(int u) {
    return (u == 0) ? 1.0f / sqrtf(8.0f) : 0.5f;
}

// -------- 1D DCT --------
void dct(const float x[N], float y[N]) {
    for (int u = 0; u < N; u++) {
        float sum = 0.0f;
        for (int n = 0; n < N; n++) {
            sum += x[n] * cosf((float)(M_PI / N) * (n + 0.5f) * u);
        }
        y[u] = alpha(u) * sum;
    }
}

// -------- 1D IDCT --------
void idct(const float x[N], float y[N]) {
    for (int n = 0; n < N; n++) {
        float sum = 0.0f;
        for (int u = 0; u < N; u++) {
            sum += alpha(u) * x[u] * cosf((float)(M_PI / N) * (n + 0.5f) * u);
        }
        y[n] = sum;
    }
}

// -------- 2D DCT --------
void dct8x8(const float in[N][N], float out[N][N]) {
    float tmp[N][N];

    // DCT on rows
    for (int i = 0; i < N; i++)
        dct(in[i], tmp[i]);

    // DCT on columns
    for (int j = 0; j < N; j++) {
        float col_in[N], col_out[N];
        for (int i = 0; i < N; i++) col_in[i] = tmp[i][j];
        dct(col_in, col_out);
        for (int i = 0; i < N; i++) out[i][j] = col_out[i];
    }
}

// -------- 2D IDCT --------
void idct8x8(const float in[N][N], float out[N][N]) {
    float tmp[N][N];

    // IDCT on columns
    for (int j = 0; j < N; j++) {
        float col_in[N], col_out[N];
        for (int i = 0; i < N; i++) col_in[i] = in[i][j];
        idct(col_in, col_out);
        for (int i = 0; i < N; i++) tmp[i][j] = col_out[i];
    }

    // IDCT on rows
    for (int i = 0; i < N; i++)
        idct(tmp[i], out[i]);
}
