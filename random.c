#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include "random.h"
#include "tinymt/tinymt64.h"

const char CHARSET[] = "abcdefghijklmnopqrstuvwxyz";
const size_t CHARSET_SIZE = sizeof(CHARSET) / sizeof(CHARSET[0]) - 1;

tinymt64_t random;
bool initialized = false;

void randomInit(uint64_t seed) {
    tinymt64_init(&random, seed);
    initialized=true;
}

//currently only handle string less than 13 characters
void randomString(char *str, size_t maxSize) {
    assert(initialized);
    uint64_t result = tinymt64_generate_uint64(&random);
    for (int i = 0; i < maxSize; i++) {
        if (!result) {
            str[i] = 0;
            break;
        }
        str[i] = CHARSET[result % CHARSET_SIZE];
        result /= CHARSET_SIZE;
    }
    str[maxSize] = 0;
}
