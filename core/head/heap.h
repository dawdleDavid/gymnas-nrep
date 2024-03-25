#ifndef HEAP_H
#define HEAP_H
#include <stdint.h>
/*
    We also need to check what the architecture that we are on supports!
*/

enum{
    HEAP_ADD,
    HEAP_REMOVE,
    HEAP_FIND,
    HEAP_LIST
};

union MTPL_Variable{
    // signed integer types
    int8_t int8;
    int16_t int16;
    int32_t int32;
    int64_t int64;
    // unsigned integer types
    uint8_t uint8;
    uint16_t uint16;
    uint32_t uint32;
    uint64_t uint64;

    // string type
    char* string; /* dynamic alloc */
    // char
    char character;
    // float types
    float float_t;
    double double_t;
    // bool
    unsigned char boolean;
};typedef union MTPL_Variable MTPL_Variable;

struct Node{
    void* data;
    struct Node* next;
    uint32_t name;
    uint32_t size;
    uint16_t type;
};

struct Nodes{
    struct Node* start;
    int number_of_nodes;
    struct Node* node;
};
/* This is not a good idea, but i will do it anyway because I kinda like it*/

struct MTPL_Heap{

    uint32_t size;
    int number_of_nodes;
    struct Nodes* nodes;
    struct Node* start;
    struct Node* JariPekare;
    struct Node* node;
    struct Node* prev;
    struct Node* last_retv;
};typedef struct MTPL_Heap MTPL_Heap;

#define MAX_VARIABLE_NAME_LENGHT 64

#define INTEGER_8_TYPE 638
#define INTEGER_16_TYPE 865
#define INTEGER_32_TYPE 855
#define INTEGER_64_TYPE 872
#define UNSIGNED_INTEGER_8_TYPE 897
#define UNSIGNED_INTEGER_16_TYPE 1139
#define UNSIGNED_INTEGER_32_TYPE 1127
#define UNSIGNED_INTEGER_64_TYPE 1149
#define STRING_TYPE 1245
#define CHARACTER_TYPE 1811

#define INTEGER_8_SIZE sizeof(int8_t)
#define INTEGER_16_SIZE sizeof(int16_t)
#define INTEGER_32_SIZE sizeof(int32_t)
#define INTEGER_64_SIZE sizeof(int64_t)
#define UNSIGNED_INTEGER_8_SIZE sizeof(uint8_t)
#define UNSIGNED_INTEGER_16_SIZE sizeof(uint16_t)
#define UNSIGNED_INTEGER_32_SIZE sizeof(uint32_t)
#define UNSIGNED_INTEGER_64_SIZE sizeof(uint64_t)

#define CHARACTER_SIZE sizeof(char)

extern MTPL_Heap* HEAP_Init();
extern MTPL_Heap* HEAP_Add(MTPL_Heap* heap, uint16_t vartype, MTPL_Variable* variable, unsigned int name);
extern MTPL_Heap* HEAP_CleanContents(MTPL_Heap* heap);
extern MTPL_Heap* HEAP_Get(MTPL_Heap* heap, unsigned int name);
extern int HEAP_Destroy(MTPL_Heap* heap);
#endif
