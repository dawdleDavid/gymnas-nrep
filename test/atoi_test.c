#include <stdint.h>
#include <stdio.h>
union MTPL_Longsigned{
    uint64_t unint;
    int64_t siint;
}; typedef union MTPL_Longsigned MTPL_Longsigned;


#define CHOICE 0



int geeksAtoi(char* str){
    // Initialize result
    int res = 0;

    // Initialize sign as positive
    int sign = 1;

    // Initialize index of first digit
    int i = 0;

    // If number is negative,
    // then update sign
    if (str[0] == '-') {
        sign = -1;

        // Also update index of first digit
        i++;
    }

    // Iterate through all digits
    // and update the result
    for (; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';

    // Return result with sign
    return sign * res;
}


MTPL_Longsigned MTPL_Strtoint(/*MTPL_Longsigned res,*/ char* string){
    uint32_t index = 0; // does not have to be this big
    MTPL_Longsigned res;
    // make sure that its not CHOICE
    res.siint = 0;    // (same mem)

    if(string[0] == '-'){
        index++;
        for (; string[index] != '\0'; index++){
            res.siint = res.siint * 10 + string[index] - '0';
        }

        printf("\n%ld\n", res.siint);

        res.siint = (-1 * res.siint);

        printf("\n%ld\n", res.siint);

        return res;
   }

    for (; string[index] != '\0'; index++){
        res.unint = res.unint * 10 + string[index] - '0';
    }
    return res;
}
#define INPUT "1234\n"
int main(){
    MTPL_Longsigned longs;
    int etst = geeksAtoi(INPUT);

    longs = MTPL_Strtoint(/*longs,*/ INPUT);

    printf("\ngeeksAtoi:%d\nMTPL_Strtoint(unsigned): %lu\nMTPL_Strtoint(signed):%ld\n", etst, longs.unint, longs.siint);


    return 0;
}
