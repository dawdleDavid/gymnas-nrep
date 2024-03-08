#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>


#include "readfile.h"


#include "../mtpl.h"

#include "../core/head/strings.h"

void argsError(const char* msg){
    fprintf(stderr, "%s\n", msg);
}


int main(int argc, char* argv[]){

    // check
    if(argc >= 2){
        if(string_compare(argc[argv-1], "--version") == 0){
            printf("%s\n", "v0.0002");
            exit(0);
        }
        if(string_compare(argc[argv-2], "-r") == 0){
            printf("%s\n", argv[argc-1]);
            FILE* file = readFile((char*)argv[argc-1]); // for clarity


            if(file == (FILE*)1){
                argsError("failed to open file");
                return 1;
            }
            // run the interpeter


            mtplParse(file);

            return 0;
        }
        if(string_compare(argc[argv-2], "-e") == 0){
                printf("%s\n", "eval file");
        }
        if(string_compare(argc[argv-1], "-v") == 0){
                printf("%s\n", "MTPL - Memory unsafe inTerpeted Programing Language, version 1.0");
        }
    }



    // start parsing the file for stuff


    return 0;
}
