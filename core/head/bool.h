#ifndef BOOL_H
#define BOOL_H
#include <stdbool.h>
#include "hash.h"


struct Expression_s{
    MTPL_Longsigned a;
    MTPL_Longsigned b;
    char op[4];
};typedef struct Expression_s Expression;


bool boolEval(Expression e);
#endif
