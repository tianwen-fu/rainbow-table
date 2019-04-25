#include "generator.h"
#include <pthread.h>
#include <stdlib.h>
#include "random.h"
#include <stdbool.h>
#include <assert.h>
#include <string.h>

//using global variables to save life
bool globalVariablesLock = false;
size_t lstCount;
char **listStart;
char **listEnd;
size_t redCount;
size_t digestSize;

void (*hash)(const char *plain, unsigned char *digest);

void (*reduce)(int k, const unsigned char *cipher, char *reduced);

void *generateRainbowTableKernel(void *id) {
    int i = (int) id;
    unsigned char *digest = malloc(sizeof(char) * (digestSize + 1));
    strcpy(listEnd[i], listStart[i]);
    for (int count = 0; count < redCount; count++) {
        hash(listEnd[i], digest);
        reduce(count, digest, listEnd[i]);
    }
    pthread_exit(NULL);
    return NULL;
}

void generateRainbowTable(Configuration *config, size_t listCount, size_t reductionCount) {
    assert(!globalVariablesLock);
    //lock global variables
    globalVariablesLock = true;

    //initialize raw data
    digestSize = config->digestLength;
    lstCount = listCount;
    listStart = malloc(sizeof(char *) * listCount);
    listEnd = malloc(sizeof(char *) * listCount);
    for (int i = 0; i < listCount; i++) {
        listStart[i] = malloc(sizeof(char) * config->maxPlainLength);
        listEnd[i] = malloc(sizeof(char) * config->maxPlainLength);
    }

    //generate random strings
    for (int i = 0; i < listCount; i++) {
        randomString(listStart[i], config->maxPlainLength, config->charset, config->charsetSize);
    }

    //spawn threads (or kernels if use CUDA)
    redCount = reductionCount;
    hash = config->hash;
    reduce = config->reduce;
    pthread_t *threadID = malloc(sizeof(pthread_t) * listCount);
    for (unsigned i = 0; i < listCount; i++) {
        pthread_create(threadID + i, NULL, generateRainbowTableKernel, (void *) i); //this is not good :-)
    }
    for (int i = 0; i < listCount; i++) pthread_join(threadID[i], NULL); //sync
    free(threadID);
}

void exportToTrie(Trie *trie) {
    assert(globalVariablesLock);
    for (int i = 0; i < lstCount; i++) trieAdd(trie, listStart[i], listEnd[i]);
}

void exportToFile(FILE *output, char separator, char lineEnd) {
    assert(globalVariablesLock);
    for (int i = 0; i < lstCount; i++) {
        fprintf(output, "%s", listStart[i]);
        fputchar(separator);
        fprintf(output, "%s", listEnd[i]);
        fputchar(lineEnd);
    }
}

void destroyRawData() {
    for (int i = 0; i < lstCount; i++) {
        free(listStart[i]);
        free(listEnd[i]);
    }
    free(listStart);
    free(listEnd);
    globalVariablesLock = false;
}