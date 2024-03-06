#include <stdio.h>

// readfile.h


/*
---------------------------------------------------
Reads a file and returns a pointer (memory address)
associated with the file.
---------------------------------------------------
*/
FILE* readFile(char* file){

    FILE* filepointer = fopen(file, "r");

    if(filepointer == NULL){
        return (FILE*)1; // error case
    }

    return filepointer;
}
