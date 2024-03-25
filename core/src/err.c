
#include <stdio.h>
#include <stdint.h>


void genericError(char* message, uint32_t line){
    fprintf(stderr, "\033[31;1;4merror\033[0m, line %d: %s\n", line, message);
}
