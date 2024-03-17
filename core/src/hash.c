#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
/* bad practice */

#include "../head/hash.h"

//temp
#include <stdio.h>
#define MAX_VARIABLE_NAME_LENGHT 64
unsigned int MTPL_Bhash(char name[MAX_VARIABLE_NAME_LENGHT]){
    unsigned int res = 0;
    //printf("STRLEN: %lu\n", strlen(name));
    for(int c = 0; c <= strlen(name); c++){
        res += ((unsigned int)name[c] * c); // reversed variable names now possible
    }
    return res;
}
// own version of atoi that returnsa int64 (given that that is supported)

char* removeWhiteSpace(char* string){
    return strpbrk(string, "-abcdefghijklmnopqrstuvwxyz123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ=åäöÅÄÖ "); /* VARJE karaktär måste vara här!!! */
}

MTPL_Longsigned MTPL_Strtoint(char* string){

    /* remove white spaces */
    string = removeWhiteSpace(string);
    puts(string);
    /* remove newline */
    string[ strlen(string) - 1 ] = '\0';

    //printf("%s\n", string);
//
    uint32_t index = 0; // does not have to be this big
    MTPL_Longsigned res;
    // make sure that its not CHOICE
    res.siint = 0;    // (same mem)

    if(string[0] == '-'){
        puts("signed int case");
        index++;
        for (; string[index] != '\0'; index++){
            res.siint = res.siint * 10 + string[index] - '0';
        }
        res.siint = (-1 * res.siint);
        return res;
   }

    for (; string[index] != '\0'; index++){
        res.unint = res.unint * 10 + string[index] - '0';
    }
    // --
    return res;
}

// (strlen(string) = ROW_LIMIT)
char* MTPL_Inttostr(char* string, MTPL_Longsigned longsigned, bool issigned){

    if(issigned){
        sprintf(string, "%ld", longsigned.siint);

        return string;
    }

    sprintf(string, "%lu", longsigned.unint);

    return string;
}
