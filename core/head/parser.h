#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdbool.h>
// how mnay chars a row may be (256 bits)
#define ROW_LIMIT 256
int mtplParse(FILE* file);
enum{
    STOP,
    START
};
enum{
    MTPL_INTEGER,
    MTPL_STRING,
    MTPL_FLOAT
};
struct MtplState_s{
    unsigned int used_stacksize;
    unsigned int used_heapsize;
    unsigned int allocated_stacksize;
    unsigned int allocated_heapsize;
    bool error;
    char errormsg[64];
};
struct Tape{
    char words_list[ROW_LIMIT][ROW_LIMIT];
};
#endif
