#pragma once

#include <limits.h>
#include <stdbool.h>

//let's assume that everything is made by [a-z]
#define CHARSET_SIZE 26

//trie indexed by the end of the list
typedef struct trieNode{
    struct trieNode *children[CHARSET_SIZE];
    char *listStart; //null if it is an intermediate node
}TrieNode;

void trieAdd(char *listStart, char *listEnd);
char* trieFind(char *listEnd); //null if not found
