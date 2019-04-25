//dummy file
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>
#include "random.h"
#include "trie.h"
#include "tinymt/tinymt64.h"
#include "generator.h"
#include "configsamples.h"

size_t encode(char c) { return c - 'a'; }

const char *charset = "abcdefghijklmnopqrstuvwxyz";

char str[1000][10];

int main() {
    randomInit(time(NULL));
    generateRainbowTable(&SHA1Sample, 10, 10);
    exportToFile(stdout, ',', '\n');
    destroyRawData();

    return 0;
}