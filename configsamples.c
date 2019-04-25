//
// Created by kevin on 2019-04-25.
//

#include "configsamples.h"
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <memory.h>
#include <math.h>
#include <string.h>

#define alphaLittle "abcdefghijklmnopqrstuvwxyz"
#define SAMPLE_PLAIN_SIZE 6

static size_t alphaEncode(char c) { return c - 'a'; }

static void hashSha(const char *plain, unsigned char *digest) {
    SHA1((const unsigned char *) plain, strlen(plain), digest);
}

static void hashMD5(const char *plain, unsigned char *digest) {
    MD5((const unsigned char *) plain, strlen(plain), digest);
}

//for plain size less than or equal to 6
static void reduce(int k, const unsigned char *cipher, char *reduced) {
    unsigned char modifiedPlain[8];
    unsigned char digest[SHA_DIGEST_LENGTH];
    uint64_t rank = 0;

    modifiedPlain[0] = k + 33;
    memcpy(modifiedPlain + 1, cipher, sizeof(unsigned char) * 7);
    SHA1(modifiedPlain, sizeof(modifiedPlain), digest);
    for (int i = 0; i < 8; i++) {
        rank *= 256;
        rank += digest[i];
    }
    rank = (uint64_t) round(
            pow(26, SAMPLE_PLAIN_SIZE) * (rank / pow(256, 8))); //actual rank uniform in all plain strings
    for (int i = 0; i < SAMPLE_PLAIN_SIZE; i++) {
        reduced[i] = rank % 26 + 'a';
        if (!rank) {
            reduced[i] = 0;
            break;
        }
        rank /= 26;
    }
    reduced[SAMPLE_PLAIN_SIZE] = 0;
}

Configuration SHA1Sample = {
        alphaLittle,
        26,
        SAMPLE_PLAIN_SIZE,
        SHA_DIGEST_LENGTH,
        1000,
        alphaEncode,
        hashSha,
        reduce
};
Configuration MD5Sample = {
        alphaLittle,
        26,
        SAMPLE_PLAIN_SIZE,
        MD5_DIGEST_LENGTH,
        1000,
        alphaEncode,
        hashMD5,
        reduce
};