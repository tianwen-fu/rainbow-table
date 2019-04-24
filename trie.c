#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "trie.h"

#define encode(c) ((c)-'a')

void trieAdd(TrieNode *root, char *listStart, char *listEnd) {
    assert(root != NULL);
    for (; *listEnd; listEnd++) { //iterate all characters
        if (root->children[encode(*listEnd)] == NULL) {
            TrieNode *newNode = root->children[encode(*listEnd)] = malloc(sizeof(TrieNode));
            newNode->listStart = NULL;
            memset(newNode->children, 0, sizeof(newNode->children));
        }
        root = root->children[encode(*listEnd)];
        assert(root != NULL);
    }
    root->listStart = malloc(sizeof(char) * (strlen(listStart) + 1));
    strcpy(root->listStart, listStart); //duplicate the string
}

char *trieFind(TrieNode *root, char *listEnd) {
    for (; *listEnd; listEnd++) { //iterate all characters
        if (root == NULL) return NULL;
        root = root->children[encode(*listEnd)];
    }
    return root->listStart;
}

void trieDestroy(TrieNode *root) {
    if (root == NULL) return;
    for (int i = 0; i < CHARSET_SIZE; i++)
        trieDestroy(root->children[i]);
    free(root);
}
