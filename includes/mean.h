// MDCT.h - Quick 8-value unrolled mean
#ifndef MEAN_H
#define MEAN_H

#include <stdint.h>

#define N 8

#ifdef __cplusplus
extern "C" {
#endif

uint8_t mean(const uint8_t in[N][N]);

#ifdef __cplusplus
}
#endif

#endif
