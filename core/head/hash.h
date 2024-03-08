#ifndef HASH_H
#define HASH_H
#include <stdint.h>
#define MAX_VARIABLE_NAME_LENGHT 64

union MTPL_Longsigned{
    uint64_t unint;
    int64_t siint;
}; typedef union MTPL_Longsigned MTPL_Longsigned;
/*
 *
 *
 *  Some of these functions should be moved in
 *  the future. A lot of these have noting to do with hashing...
 */
unsigned int MTPL_Bhash(char name[MAX_VARIABLE_NAME_LENGHT]);
MTPL_Longsigned MTPL_Strtoint(char* string);
char* removeWhiteSpace(char* string);
#endif
