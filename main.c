//dummy file
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>
#include "tinymt/tinymt64.h"

int main(){
    tinymt64_t randomGenerator;
    tinymt64_init(&randomGenerator, time(NULL));
    for(int i=0;i<100;i++)
        printf("%20"PRIu64"\n",tinymt64_generate_uint64(&randomGenerator));

    return 0;
}