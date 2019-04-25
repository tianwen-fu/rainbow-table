#pragma once

#include <limits.h>

typedef struct {
    char *charset;
    size_t charsetSize;
    size_t maxPlainLength;
    size_t digestLength;
    size_t reductionCount;

    size_t (*encode)(char);

    void (*hash)(const char *plain, unsigned char *digest);

    void (*reduce)(int k, const unsigned char *cipher, char *reduced); //k-th reduce function
} Configuration;