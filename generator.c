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
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
    int i = (int) id;
    unsigned char *digest = malloc(sizeof(char) * (digestSize + 1));
    //printf("%d: %s\n",i,listStart[i]);
    strcpy(listEnd[i], listStart[i]);
    for (int count = 0; count < redCount; count++) {
        hash(listEnd[i], digest);
        reduce(count, digest, listEnd[i]);
        //printf("%d: %s\n",i,listEnd[i]);
    }
    pthread_exit(NULL);
    return NULL;
}

void generateRainbowTable(Configuration *config, size_t listCount) {
    assert(!globalVariablesLock);
    //lock global variables
    globalVariablesLock = true;

    //initialize raw data
    digestSize = config->digestLength;
    lstCount = listCount;
    listStart = malloc(sizeof(char *) * listCount);
    listEnd = malloc(sizeof(char *) * listCount);
    for (int i = 0; i < listCount; i++) {
        listStart[i] = malloc(sizeof(char) * (config->maxPlainLength + 1));
        listEnd[i] = malloc(sizeof(char) * (config->maxPlainLength + 1));
    }

    //generate random strings
    for (int i = 0; i < listCount; i++) {
        randomString(listStart[i], config->maxPlainLength, config->charset, config->charsetSize);
    }

    //spawn threads (or kernels if use CUDA)
    redCount = config->reductionCount;
    hash = config->hash;
    reduce = config->reduce;
    pthread_t *threadID = malloc(sizeof(pthread_t) * listCount);
    for (unsigned i = 0; i < listCount; i++) {
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
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
        fputc(separator, output);
        fprintf(output, "%s", listEnd[i]);
        fputc(lineEnd, output);
    }
}

void destroyRawData() {
    assert(globalVariablesLock);
    for (int i = 0; i < lstCount; i++) {
        free(listStart[i]);
        free(listEnd[i]);
    }
    free(listStart);
    free(listEnd);
    globalVariablesLock = false;
}