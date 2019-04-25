#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include "random.h"
#include "tinymt/tinymt64.h"

tinymt64_t random;
bool initialized = false;

void randomInit(uint64_t seed) {
    tinymt64_init(&random, seed);
    initialized = true;
}

//currently only handle string less than 13 characters
void randomString(char *str, size_t maxSize, const char *charset, size_t charsetSize) {
    assert(initialized);
    const double stringMax = pow(charsetSize, maxSize);
    uint64_t result = (uint64_t) round(stringMax * tinymt64_generate_double01(&random));
    for (int i = 0; i < maxSize; i++) {
        if (!result) {
            str[i] = 0;
            break;
        }
        str[i] = charset[result % charsetSize];
        result /= charsetSize;
    }
    str[maxSize] = 0;
}
