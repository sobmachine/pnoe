#include <stdint.h>
#include "mean.h"

uint8_t mean(const uint8_t in[8][8]) {
    uint32_t sum = 0;

    for (int i = 0; i < 8; i++) {
        sum += in[i][0] + in[i][1] + in[i][2] + in[i][3]
             + in[i][4] + in[i][5] + in[i][6] + in[i][7];
    }

    return (sum + 32) >> 6;
}
