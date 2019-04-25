#pragma once

#include <limits.h>
#include <stdbool.h>

//let's assume that everything is made by [a-z]
#define CHARSET_SIZE 26

//trie indexed by the end of the list
typedef struct trieNode {
    struct trieNode *children[CHARSET_SIZE];
    char *listStart; //null if it is an intermediate node
} TrieNode;

//metadata for a trie
typedef struct {
    const size_t charsetSize;

    size_t (*encode)(char); //encode a char in charset to [0,charsetSize)
    TrieNode *root;
} Trie;

/*all chars are allowed to be freed after calling the functions*/

Trie *trieNew(size_t charsetSize, size_t (*encode)(char));

void trieAdd(Trie *trie, char *listStart, char *listEnd);

char *trieFind(Trie *trie, char *listEnd); //null if not found

void trieDestroy(Trie *trie);
