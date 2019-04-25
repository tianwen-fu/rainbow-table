#include "solver.h"
#include <string.h>

void reduceAndHash(const Configuration *config, const char *src, char *dest, int start, int end) {
    unsigned char digest[config->digestLength];
    strcpy(dest, src);
    for (int i = start; i < end; i++) {
        config->hash(dest, digest);
        config->reduce(i, digest, dest);
    }
}

bool solve(const Trie *rainbowTable, const Configuration *config, const unsigned char *cipher, char *plain) {
    char reducedCipher[config->maxPlainLength + 1];
    char listEnd[config->maxPlainLength + 1];
    unsigned char cipherTest[config->digestLength];
    char *listStart;
    for (int trial = config->reductionCount - 1; trial >= 0; trial--) {
        config->reduce(trial, cipher, reducedCipher);
        reduceAndHash(config, reducedCipher, listEnd, trial + 1, config->reductionCount);
        if ((listStart = trieFind(rainbowTable, listEnd)) != NULL) {
            reduceAndHash(config, listStart, plain, 0, trial);

            //check whether it is false alarm
            config->hash(plain, cipherTest);
            bool success = true;
            for (int i = 0; i < config->digestLength; i++) {
                if (cipherTest[i] != cipher[i]) {
                    success = false;
                    break;
                }
            }
            if (success) return true;
        }
    }
    return false;
}
