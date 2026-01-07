// main.c - raw RGB encoder/decoder using 8x8x3 codec
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "encodec.h"
#include "helpers.h"

#define BLOCK_SIZE 8

int main(int argc, char *argv[]) {
    if (argc != 6) {
        fprintf(stderr,
            "Usage:\n"
            "  %s encode WIDTH HEIGHT input.raw encoded.bin\n"
            "  %s decode WIDTH HEIGHT encoded.bin decoded.raw\n",
            argv[0], argv[0]
        );
        return 1;
    }

    const char *mode = argv[1];
    int WIDTH  = atoi(argv[2]);
    int HEIGHT = atoi(argv[3]);
    const char *infile  = argv[4];
    const char *outfile = argv[5];

    if (WIDTH <= 0 || HEIGHT <= 0) {
        fprintf(stderr, "Invalid width or height\n");
        return 1;
    }

    if (WIDTH % BLOCK_SIZE || HEIGHT % BLOCK_SIZE) {
        fprintf(stderr, "Width and height must be multiples of %d\n", BLOCK_SIZE);
        return 1;
    }

    int blocks_x = WIDTH  / BLOCK_SIZE;
    int blocks_y = HEIGHT / BLOCK_SIZE;
    int total_blocks = blocks_x * blocks_y;

    /* ===================== ENCODE ===================== */
    if (strcmp(mode, "encode") == 0) {
        size_t img_size = (size_t)WIDTH * HEIGHT * 3;

        uint8_t *rgb = malloc(img_size);
        if (!rgb) {
            fprintf(stderr, "Failed to allocate image buffer\n");
            return 1;
        }

        FILE *f = fopen(infile, "rb");
        if (!f) { perror("fopen input"); return 1; }
        fread(rgb, 1, img_size, f);
        fclose(f);

        Block8x8_Coeffs *blocks =
            malloc(sizeof(Block8x8_Coeffs) * total_blocks);
        if (!blocks) {
            fprintf(stderr, "Failed to allocate blocks\n");
            return 1;
        }

        for (int by = 0; by < blocks_y; by++) {
            for (int bx = 0; bx < blocks_x; bx++) {
                uint8_t r[BLOCK_SIZE][BLOCK_SIZE];
                uint8_t g[BLOCK_SIZE][BLOCK_SIZE];
                uint8_t b[BLOCK_SIZE][BLOCK_SIZE];

                for (int i = 0; i < BLOCK_SIZE; i++)
                    for (int j = 0; j < BLOCK_SIZE; j++) {
                        int x = bx * BLOCK_SIZE + j;
                        int y = by * BLOCK_SIZE + i;
                        int idx = (y * WIDTH + x) * 3;
                        r[i][j] = rgb[idx + 0];
                        g[i][j] = rgb[idx + 1];
                        b[i][j] = rgb[idx + 2];
                    }

                encode_block_8x8_444(
                    r, g, b,
                    &blocks[by * blocks_x + bx]
                );
            }
        }

        f = fopen(outfile, "wb");
        if (!f) { perror("fopen output"); return 1; }
        fwrite(blocks, sizeof(Block8x8_Coeffs), total_blocks, f);
        fclose(f);

        printf("Encoded %dx%d → %s\n", WIDTH, HEIGHT, outfile);

        free(rgb);
        free(blocks);
    }

    /* ===================== DECODE ===================== */
    else if (strcmp(mode, "decode") == 0) {
        size_t img_size = (size_t)WIDTH * HEIGHT * 3;

        Block8x8_Coeffs *blocks =
            malloc(sizeof(Block8x8_Coeffs) * total_blocks);
        uint8_t *rgb_out = malloc(img_size);

        if (!blocks || !rgb_out) {
            fprintf(stderr, "Failed to allocate buffers\n");
            return 1;
        }

        FILE *f = fopen(infile, "rb");
        if (!f) { perror("fopen input"); return 1; }
        fread(blocks, sizeof(Block8x8_Coeffs), total_blocks, f);
        fclose(f);

        for (int by = 0; by < blocks_y; by++) {
            for (int bx = 0; bx < blocks_x; bx++) {
                uint8_t r[BLOCK_SIZE][BLOCK_SIZE];
                uint8_t g[BLOCK_SIZE][BLOCK_SIZE];
                uint8_t b[BLOCK_SIZE][BLOCK_SIZE];

                decode_block_8x8_444(
                    &blocks[by * blocks_x + bx],
                    r, g, b
                );

                for (int i = 0; i < BLOCK_SIZE; i++)
                    for (int j = 0; j < BLOCK_SIZE; j++) {
                        int x = bx * BLOCK_SIZE + j;
                        int y = by * BLOCK_SIZE + i;
                        int idx = (y * WIDTH + x) * 3;
                        rgb_out[idx + 0] = r[i][j];
                        rgb_out[idx + 1] = g[i][j];
                        rgb_out[idx + 2] = b[i][j];
                    }
            }
        }

        f = fopen(outfile, "wb");
        if (!f) { perror("fopen output"); return 1; }
        fwrite(rgb_out, 1, img_size, f);
        fclose(f);

        printf("Decoded %s → %dx%d raw\n", infile, WIDTH, HEIGHT);

        free(blocks);
        free(rgb_out);
    }

    else {
        fprintf(stderr, "Unknown mode: %s (use encode or decode)\n", mode);
        return 1;
    }

    return 0;
}
