#ifndef HASH_H
#define HASH_H
#include <stdint.h>
#define MAX_VARIABLE_NAME_LENGHT 64

union MTPL_Longsigned{
    uint64_t unint;
    int64_t siint;
}; typedef union MTPL_Longsigned MTPL_Longsigned;

unsigned int MTPL_Bhash(char name[MAX_VARIABLE_NAME_LENGHT]);
MTPL_Longsigned MTPL_Strtoint(char* string);
#endif
