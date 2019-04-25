#pragma once

#include <limits.h>
#include <stdint.h>

//random helper functions

void randomInit(uint64_t seed);

//please make sure that str has maxSize+1 spaces
void randomString(char *str, size_t maxSize, const char *charset, size_t charsetSize);
