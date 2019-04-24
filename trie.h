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

/*all chars are allowed to be freed after calling the function*/

void trieAdd(TrieNode *root, char *listStart, char *listEnd);

char *trieFind(TrieNode *root, char *listEnd); //null if not found

void trieDestroy(TrieNode *root);
