#pragma once

#include <stdbool.h>
#include "config.h"
#include "trie.h"

bool solve(const Trie *rainbowTable, const Configuration *config, const unsigned char *cipher, char *plain);
