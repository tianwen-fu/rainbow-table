//dummy file
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>
#include "random.h"
#include "trie.h"
#include "tinymt/tinymt64.h"

char str[100][10];
int main(){
    TrieNode root;
    tinymt64_t random;

    root.listStart=NULL;
    memset(root.children,0, sizeof(root.children));
    tinymt64_init(&random,233);
    randomInit(time(NULL));

    for(int i=0;i<100;i++){
        randomString(str[i],9);
        trieAdd(&root,str[i],str[i]);
        //printf("inserted %s\n",str[i]);
    }
    for(int i=0;i<10;i++){
        printf("checking: %s\n" ,trieFind(&root,str[(int)(tinymt64_generate_double01(&random)*90)]));
    }

    for(int i=0;i<10;i++){
        randomString(str[99],9);
        printf("checking: %s\n" ,trieFind(&root,str[99]));
    }

    return 0;
}