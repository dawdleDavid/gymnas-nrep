#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


char* test_data[20] = {
  "test",
  " test",
  "   test",
  "     test"
};


char* removeWhiteSpace(char* string){
    return strpbrk(string, "abcdefghijklmnopqrstuvwxyz123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}


int main(void){
    for(int i = 0; i <= 3; i++){
        printf("%s\n", removeWhiteSpace(test_data[i]));
    }
    return 0;
}
