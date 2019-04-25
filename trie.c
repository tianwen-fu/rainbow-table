#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "trie.h"

Trie *trieNew(size_t charsetSize, size_t (*encode)(char)) {
    TrieNode *root = malloc(sizeof(TrieNode));
    memset(root->children, 0, sizeof(root->children));
    root->listStart = NULL;
    Trie rawData = {charsetSize, encode, root};
    Trie *trie = malloc(sizeof(Trie));
    memcpy(trie, &rawData, sizeof(rawData));
    return trie;
}

void trieAdd(Trie *trie, char *listStart, char *listEnd) {
    TrieNode *root = trie->root;
    assert(root != NULL);
    for (; *listEnd; listEnd++) { //iterate all characters
        if (root->children[trie->encode(*listEnd)] == NULL) {
            TrieNode *newNode = root->children[trie->encode(*listEnd)] = malloc(sizeof(TrieNode));
            newNode->listStart = NULL;
            memset(newNode->children, 0, sizeof(newNode->children));
        }
        root = root->children[trie->encode(*listEnd)];
        assert(root != NULL);
    }
    root->listStart = malloc(sizeof(char) * (strlen(listStart) + 1));
    strcpy(root->listStart, listStart); //duplicate the string
}

char *trieFind(Trie *trie, char *listEnd) {
    TrieNode *root = trie->root;
    for (; *listEnd; listEnd++) { //iterate all characters
        if (root == NULL) return NULL;
        root = root->children[trie->encode(*listEnd)];
    }
    return root->listStart;
}

void trieDestroyNode(TrieNode *root) {
    if (root == NULL) return;
    for (int i = 0; i < CHARSET_SIZE; i++)
        trieDestroyNode(root->children[i]);
    free(root);
}

void trieDestroy(Trie *trie) {
    if (trie == NULL) return;
    trieDestroyNode(trie->root);
    free(trie);
}
