//dummy file
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>
#include "random.h"
#include "trie.h"
#include "tinymt/tinymt64.h"

size_t encode(char c) { return c - 'a'; }

const char *charset = "abcdefghijklmnopqrstuvwxyz";

char str[1000][10];

int main() {
    Trie *trie = trieNew(26, encode);
    tinymt64_t random;

    tinymt64_init(&random, 233);
    randomInit(time(NULL));

    for (int i = 0; i < 1000; i++) {
        randomString(str[i], 9, charset, 26);
        trieAdd(trie, str[i], str[i]);
        //printf("inserted %s\n",str[i]);
    }
    for (int i = 0; i < 10; i++) {
        printf("checking: %s\n", trieFind(trie, str[(int) (tinymt64_generate_double01(&random) * 90)]));
    }

    for (int i = 0; i < 10; i++) {
        randomString(str[99], 9, charset, 26);
        printf("checking: %s\n", trieFind(trie, str[99]));
    }
    trieDestroy(trie);

    return 0;
}