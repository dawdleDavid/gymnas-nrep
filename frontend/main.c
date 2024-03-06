#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>


#include "readfile.h"


#include "../mtpl.h"

#include "../core/head/strings.h"

int main(int argc, char* argv[]){

    // check
    if(argc > 2){
        if(string_compare(argc[argv-1], "--version") == 0){
            printf("%s\n", "v0.0002");
            exit(0);
        }
        if(string_compare(argc[argv-2], "-r") == 0){
            printf("%s\n", argv[argc-1]);
            FILE* file = readFile((char*)argv[argc-1]); // for clarity

            if(file == (FILE*)1){
                fprintf(stderr, "could not open file\n");
                return 1;
            }
            // run the interpeter


            mtplParse(file);

            return 0;
        }
    }else{
        fprintf(stderr, "to few arguments\n");
    }
    // start parsing the file


    return 0;
}
