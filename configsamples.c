//
// Created by kevin on 2019-04-25.
//

#include "configsamples.h"
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <memory.h>
#include <math.h>

#define alphaLittle "abcdefghijklmnopqrstuvwxyz"

static size_t alphaEncode(char c) { return c - 'a'; }

static void hashSha(const char *plain, unsigned char *digest) {
    SHA1((const unsigned char *) plain, sizeof(plain), digest);
}

static void hashMD5(const char *plain, unsigned char *digest) {
    MD5((const unsigned char *) plain, sizeof(plain), digest);
}

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
    rank = (uint64_t) round(pow(26, 6) * (rank / pow(256, 8))); //actual rank uniform in all plain strings
    for (int i = 0; i < 6; i++) {
        reduced[i] = rank % 26 + 'a';
        if (!rank) {
            reduced[i] = 0;
            break;
        }
        rank /= 26;
    }
    reduced[6] = 0;
}

Configuration SHA1Sample = {
        alphaLittle,
        26,
        6,
        SHA_DIGEST_LENGTH,
        alphaEncode,
        hashSha,
        reduce
};
Configuration MD5Sample = {
        alphaLittle,
        26,
        6,
        MD5_DIGEST_LENGTH,
        alphaEncode,
        hashMD5,
        reduce
};