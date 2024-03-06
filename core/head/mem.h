#ifndef MEM_H
#define MEM_H

union Numbers{
    int integer;
    float floatingpoint;
};
union Strings{
    char* string; // yet to be allocated
};
union Stack{    // sizeof union pointer
    union Strings* strings;
    union Numbers* numbers;
};

#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
// functiondefs
void* mem_alloc(void* data, int size);
int mem_free(void* ptr, long int size);
#endif
