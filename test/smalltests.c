#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

char* test_data[20] = {
  "test",
  " test",
  "   test",
  "     test"
};


char* removeWhiteSpace(char* string){
    return strpbrk(string, "-abcdefghijklmnopqrstuvwxyz123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}


char* MTPL_Inttostr(char* string, uint64_t integer){


   sprintf(string, "%ld", integer);



    return string;
}
union MTPL_Longsigned{
    uint64_t unint;
    int64_t siint;
}; typedef union MTPL_Longsigned MTPL_Longsigned;
/*Sanety check needed*/
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


int main(void){
    for(int i = 0; i <= 3; i++){
        printf("%s\n", removeWhiteSpace(test_data[i]));
    }

    char string[256];
    printf("%s\n", MTPL_Inttostr(string, 2342342342344));

    char temp[256] = " 250\n";

    printf("%c\n", temp[0]);
    MTPL_Longsigned longs = MTPL_Strtoint(temp);

    printf("%ld\n", longs.siint);


    return 0;


}
