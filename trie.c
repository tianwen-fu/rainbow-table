#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "trie.h"

#define encode(c) ((c)-'a')

void trieAdd(TrieNode *root, char *listStart, char *listEnd){
    assert(root!=NULL);
    for(;*listEnd;listEnd++){ //iterate all characters
        if(root->children[encode(*listEnd)]==NULL) root->children[encode(*listEnd)] = malloc(sizeof(TrieNode));
        root=root->children[encode(*listEnd)];
    }
    root->listStart = malloc(sizeof(char)*(strlen(listStart)+1));
    strcpy(root->listStart,listStart); //duplicate the string
}

char *trieFind(TrieNode *root, char *listEnd){
    for(;*listEnd;listEnd++){ //iterate all characters
        if(root==NULL) return NULL;
        root=root->children[encode(*listEnd)];
    }
    return root->listStart;
}

void trieDestroy(TrieNode *root){
    if(root==NULL) return;
    for(int i=0;i<CHARSET_SIZE;i++)
        trieDestroy(root->children[i]);
    free(root);
}
