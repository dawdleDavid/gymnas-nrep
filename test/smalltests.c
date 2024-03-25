#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

char* test_data[20] = {
  "atesta",
  " atest a",
  "   atest  a",
  "   a   test   a"
};

/*
char* removeWhiteSpace(char* string){

    string = strpbrk(string, "-abcdefghijklmnopqrstuvwxyz123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    //printf("FIR:%sEND\n", string);

    int i = 0,p=0;
    char* t = strchr(string, ' ');

    if(t != NULL){
        char* res = malloc(strlen(string)+1);
        while(i <= strlen(string)){

            if(string[i] == *t){
                for(int p = i; p <= strlen(string); p++){
                    if(string[p] != ' '){
                        break;
                    }
                    string[]
                }
                string[i] = string[p];
            }


            i++;
        }
    }
    return string;
}
*/
/*
 * Måndag
 *
 *
 * Skriv klart strlen funktionen
 * Få variabler att fungera
 * Få if statements att fungera
 *
 */


union MTPL_Longsigned{
    uint64_t unint;
    int64_t siint;
}; typedef union MTPL_Longsigned MTPL_Longsigned;
/*Sanety check needed*/
MTPL_Longsigned MTPL_Strtoint(char* string){

    /* remove white spaces */
    //string = removeWhiteSpace(string);

    /* remove newline */


    if(strstr(string, "\n") != NULL){
        string[ strlen(string) - 1 ] = '\0';
    }
    printf("ISTI:START%sEND\n", string);
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
            if(string[index] == ' '){ continue; }
            res.siint = res.siint * 10 + string[index] - '0';
        }
        res.siint = (-1 * res.siint);
        return res;
   }

    for (; string[index] != '\0'; index++){
        if(string[index] == ' '){ continue; }
        res.unint = res.unint * 10 + string[index] - '0';
    }
    // --
    printf("ISTIAC: %lu\n", res.unint);
    return res;
}

char* MTPL_Inttostr(char* string, MTPL_Longsigned longsigned, bool issigned){

    if(issigned){
        sprintf(string, "%ld", longsigned.siint);
        return string;
    }

    sprintf(string, "%lu", longsigned.unint);
    return string;
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



int main(void){
    for(int i = 0; i <= 3; i++){
        //printf("%s\n", removeWhiteSpace(test_data[i]));
    }

    char string[256];


    char temp[256] = " 250  \n";

    printf("%c\n", temp[0]);
    MTPL_Longsigned longs = MTPL_Strtoint(temp);


    printf("INTOSTR: %s\n", MTPL_Inttostr(string, longs, false));


    printf("%ld\n", longs.siint);

    printf("BHASH:%d\n", MTPL_Bhash("  yeet\n  \n  \n\n\n      "));


    return 0;
}
