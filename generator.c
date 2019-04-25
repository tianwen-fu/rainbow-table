#include "generator.h"
#include <pthread.h>
#include <stdlib.h>
#include "random.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

//using global variables to save life
bool globalVariablesLock = false;
size_t lstCount;
char **listStart;
char **listEnd;
size_t redCount;

void (*hash)(const char *plain, unsigned char *digest);

void (*reduce)(int k, const unsigned char *cipher, char *reduced);

void *generateRainbowTableKernel(void *id) {
    printf("Hello from thread %d\n", (int) id);
    pthread_exit(NULL);
    return NULL;
}

void generateRainbowTable(Configuration *config, size_t listCount, size_t reductionCount) {
    /*assert(!globalVariablesLock);
    //lock global variables
    globalVariablesLock = true;

    //initialize raw data
    lstCount = listCount;
    listStart = malloc(sizeof(char *) * listCount);
    listEnd = malloc(sizeof(char *) * listCount);
    for (int i = 0; i < listCount; i++) {
        listStart[i] = malloc(sizeof(char) * config->maxPlainLength);
        listEnd[i] = malloc(sizeof(char) * config->digestLength);
    }

    //generate random strings
    for (int i = 0; i < listCount; i++) {
        randomString(listStart[i], config->maxPlainLength, config->charset, config->charsetSize);
    }

    //spawn threads (or kernels if use CUDA)
    redCount = reductionCount;
    hash = config->hash;
    reduce = config->reduce;*/
    pthread_t *threadID = malloc(sizeof(pthread_t) * listCount);
    for (unsigned i = 0; i < listCount; i++) {
        pthread_create(threadID + i, NULL, generateRainbowTableKernel, (void *) i); //this is not good :-)
    }
    for (int i = 0; i < listCount; i++) pthread_join(threadID[i], NULL);
}
