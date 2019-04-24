//dummy file
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>
#include "random.h"

int main(){
    char str[10];
    randomInit(time(NULL));
    for(int i=0;i<100;i++){
        randomString(str,9);
        printf("%s\n",str);
    }

    return 0;
}