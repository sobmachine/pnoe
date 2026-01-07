// MAD.h - Mean Absolute Deviation
#ifndef MAD_H
#define MAD_H

#define N 8

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t mad(const uint8_t blk[N][N], uint8_t mean);

#ifdef __cplusplus
}
#endif

#endif
