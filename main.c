//dummy file
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main(){
    char *str = "some data here";
    unsigned char digest[SHA_DIGEST_LENGTH];
    SHA1(str,strlen(str),digest);

    for(int i=0;i<SHA_DIGEST_LENGTH;i++) printf("%02x ",digest[i]);
    putchar('\n');

    return 0;
}