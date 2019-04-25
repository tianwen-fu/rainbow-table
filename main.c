//dummy file
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>
#include <assert.h>
#include "random.h"
#include "trie.h"
#include "tinymt/tinymt64.h"
#include "generator.h"
#include "configsamples.h"
#include "solver.h"

size_t encode(char c) { return c - 'a'; }

const char *charset = "abcdefghijklmnopqrstuvwxyz";

char str[1000][10];

int main() {
    randomInit(time(NULL));

    FILE *rainbowLog = fopen("rainbow.log", "w");

    char *plain = "succes";
    unsigned char cipher[SHA_DIGEST_LENGTH];
    unsigned char cipherTest[SHA_DIGEST_LENGTH];
    SHA1((unsigned char *) plain, strlen(plain), cipher);
    SHA1Sample.hash(plain, cipherTest);
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) assert(cipher[i] == cipherTest[i]);
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) printf("%02x ", cipher[i]);
    putchar('\n');

    Trie *trie = trieNew(26, encode);
    generateRainbowTable(&SHA1Sample, 400000);
    exportToFile(rainbowLog, ',', '\n');
    exportToTrie(trie);
    destroyRawData();

    char solved[8];
    if (solve(trie, &SHA1Sample, cipher, solved)) {
        printf("Successfully Solved: %s\n", solved);
    } else printf("Solve Not Successful\n");

    fclose(rainbowLog);

    return 0;
}