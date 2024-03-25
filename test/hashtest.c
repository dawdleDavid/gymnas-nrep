/*

Redefining the macros to mach what the hash funciton
outputs. Allows me to use switch instead of if nad speed up the
program quite considerably.

*/
#include <stdio.h>
#include <string.h>



/* bad practice */

const char* vardefs[10] = {
    "int8 ",
    "int16 ",
    "int32 ",
    "int64 ",
    "uint8 ",
    "uint16 ",
    "uint32 ",
    "uint64 ",
    "float ",
    "lfloat ",
};


#define MAX_VARIABLE_NAME_LENGHT 64
unsigned int MTPL_Bhash_old(char name[MAX_VARIABLE_NAME_LENGHT]){
    unsigned int res = 0;
    for(int c = 0; c <= strlen(name); c++){
        res += ((unsigned int)name[c] * c); // reversed variable names now possible
    }
    return res;
}

#define MAX_VARIABLE_NAME_LENGHT 64
unsigned int MTPL_Bhash(char name[MAX_VARIABLE_NAME_LENGHT]){
    unsigned int res = 0;
    //printf("STRLEN: %lu\n", strlen(name));
    name = strpbrk(name, "-abcdefghijklmnopqrstuvwxyz123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    printf("NAME:%s\n", name);
    int c = 0;
    while(name[c] != '\0'){
        if(name[c] == '\n' || name[c] == ' '){c++; continue;}
        res += ((unsigned int)name[c] * c); // reversed variable names now possible
        c++;
    }
    return res;
}

int main(int argc, char* argv[]){


    for(unsigned int i = 0; i <= 10-1; i++){
        printf("%d\n", MTPL_Bhash((char*)vardefs[i]));
    }

    return 0;
}
