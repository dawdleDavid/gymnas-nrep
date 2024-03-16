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
    return strpbrk(string, "abcdefghijklmnopqrstuvwxyz123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}


char* MTPL_Inttostr(char* string, uint64_t integer){


   sprintf(string, "%ld", integer);



    return string;
}

int main(void){
    for(int i = 0; i <= 3; i++){
        printf("%s\n", removeWhiteSpace(test_data[i]));
    }

    char string[256];
    printf("%s\n", MTPL_Inttostr(string, 2342342342344));
    return 0;
}
