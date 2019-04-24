#pragma once

#include <limits.h>

const char charset[] = "abcdefghijklmnopqrstuvwxyz";
const size_t charsetSize = sizeof(charset) / sizeof(charset[0]);

//random helper functions
void randomString(char *str, size_t maxSize); //please make sure that str has enough space
