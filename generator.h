#pragma once

#include <limits.h>

typedef struct {
    char *charset;
    size_t charsetSize;
    size_t maxPlainLength;
    size_t digestLength;

    void (*encode)(char);

    void (*hash)(const char *plain, unsigned char *digest);

    void (*reduce)(int k, const unsigned char *cipher, char *reduced); //k-th reduce function
} Configuration;

void generateRainbowTable(Configuration *config, size_t listCount, size_t reductionCount);

void exportToTrie();

void exportToFile(char separator, char lineEnd);

void destroyRawData();