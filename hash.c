#include "project.h"
//hash func
int HashFunc(char* str){
    int hash = 0;
    while(*str != '\0'){
        hash = (hash+1) * 60013 + (int)*str;
        str++;
    }

    hash = hash % DIVISOR;

    return hash;
}
