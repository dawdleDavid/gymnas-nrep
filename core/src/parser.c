#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>

// debug
#include <assert.h>
#include <math.h>

// heap memory
#include "../head/heap.h"
// parser globals
#include "../head/parser.h"
// string functions
#include "../head/strings.h"
#include "../head/hash.h"

// stdstream
#include "../head/stdstream.h"


char* vardefs[11] = {
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
    "stdout "
};

// returns memory that has to be free'd
struct Tape* findKeyword(struct Tape* memwrap, char* buffer){
    char word[ROW_LIMIT]; char words_list[ROW_LIMIT][ROW_LIMIT];

    int walk = -1,words=0;

    int word_index = 0;

    for(int character = 0; character <= strlen(buffer); character++){
        walk++;
        if(buffer[character] == ' ' || buffer[character] == '\n'){
            for(int index = (character-walk); index <= character; index++){
                word[word_index] = buffer[index];
                word_index++;
            }
            strcpy(words_list[words], word);
            words++;

            // clean the array...
            for(int i = 0; i <= ROW_LIMIT; i++){
                word[i] = (char)0;
            }

            walk = 0; word_index = 0;
         }

    }
    int i = 0; // ha, didn't know that works...
    for(;i <= ROW_LIMIT; i++){
        strcpy(memwrap->words_list[i], words_list[i]);
        if(strstr(memwrap->words_list[i], "\n") != NULL){
            break;
        }
    }
    return memwrap;
}
// defacto main function of the parser!
int mtplParse(FILE* file){
    struct Tape memwrap; struct Tape* memwrap_p;

    if(file == (FILE*)NULL){
        perror("");
    }


    //puts("we ran this..");
    char buffer[ROW_LIMIT];


    uint32_t p_counter = 0;

    /* HEAP_Init() */
    MTPL_Heap* heap = HEAP_Init();

    MTPL_Variable variable;

    MTPL_Longsigned longsigned;

    bool p_run= true;
    char varn[ROW_LIMIT];
    char vart[64];
    char varv[ROW_LIMIT]; // use math o this to determine if this is resonable.
    char* print_temp;
    uint32_t tc = 0; //  temporary counter
    char tcp[ROW_LIMIT]; //  temporary char pointer

    /* Acctual parsing starts here... */
    while(p_run){
        char* row = fgets(buffer, ROW_LIMIT, file);

        // comments
        if(buffer[0] == '.'){ continue; } // https://www.youtube.com/watch?v=3YmMNpbFjp0



        p_counter++;
        //printf("PC: %d\n", p_counter);
        if(row == (char*)NULL){
            //printf("EOF\n");
            break;
        }
            // do something with the line that you just got
        memwrap_p = findKeyword(&memwrap, row);

        for( int index = 0;index <= ROW_LIMIT; index++){
            assert(memwrap_p->words_list[index] != NULL);

            if(strstr(memwrap_p->words_list[index], "\n") != NULL){
                break;
            }
            for(int vari = 0; vari <= 9; vari++){ /* assert for the win i guess!*/
                assert(vardefs[vari] != NULL);
                if(strcmp(memwrap_p->words_list[index], vardefs[vari]) == 0){ // oh, i guess that space is to my
                    if(index < ROW_LIMIT){
                        strcpy(varn, memwrap_p->words_list[index+1]);
                        strcpy(vart, memwrap_p->words_list[index]);
                        strcpy(varv, memwrap_p->words_list[index+3]);
                        break;
                    }
                }
            }
            if(strcmp(varn, "") != 0){
                switch(MTPL_Bhash(vart)){
                    case UNSIGNED_INTEGER_8_TYPE:

                        printf("%d\n", MTPL_Bhash(varn));

                        longsigned = MTPL_Strtoint(varv);
                        variable.uint8 = (uint8_t)longsigned.unint;
                        heap = HEAP_Add(heap, UNSIGNED_INTEGER_8_TYPE, &variable, MTPL_Bhash(varn));
                        heap = HEAP_Get(heap, MTPL_Bhash(varn));
                        break;
                    case UNSIGNED_INTEGER_16_TYPE:
                        longsigned = MTPL_Strtoint(varv);
                        variable.uint16 = (uint16_t)longsigned.unint;
                        heap = HEAP_Add(heap, UNSIGNED_INTEGER_16_TYPE, &variable, MTPL_Bhash(varn));
                        heap = HEAP_Get(heap, MTPL_Bhash(varn));
                        break;
                    case UNSIGNED_INTEGER_32_TYPE:
                        longsigned = MTPL_Strtoint(varv);
                        variable.uint32 = (uint32_t)longsigned.unint;
                        heap = HEAP_Add(heap, UNSIGNED_INTEGER_32_TYPE, &variable, MTPL_Bhash(varn));
                        heap = HEAP_Get(heap, MTPL_Bhash(varn));
                        break;
                    case UNSIGNED_INTEGER_64_TYPE:
                        longsigned = MTPL_Strtoint(varv);
                        variable.uint64 = (uint64_t)longsigned.unint;
                        heap = HEAP_Add(heap, UNSIGNED_INTEGER_64_TYPE, &variable, MTPL_Bhash(varn));
                        heap = HEAP_Get(heap, MTPL_Bhash(varn));
                        break;
                    case INTEGER_8_TYPE:
                        longsigned = MTPL_Strtoint(varv);
                        variable.int8 = (int8_t)longsigned.siint;
                        heap = HEAP_Add(heap, INTEGER_8_TYPE, &variable, MTPL_Bhash(varn));
                        heap = HEAP_Get(heap, MTPL_Bhash(varn));
                        break;
                    case INTEGER_16_TYPE:
                        longsigned = MTPL_Strtoint(varv);
                        variable.int16 = (int16_t)longsigned.siint;
                        heap = HEAP_Add(heap, INTEGER_16_TYPE, &variable, MTPL_Bhash(varn));
                        heap = HEAP_Get(heap, MTPL_Bhash(varn));
                        break;
                    case INTEGER_32_TYPE:
                        longsigned = MTPL_Strtoint(varv);
                        variable.int32 = (int32_t)longsigned.siint;
                        heap = HEAP_Add(heap, INTEGER_32_TYPE, &variable, MTPL_Bhash(varn));
                        heap = HEAP_Get(heap, MTPL_Bhash(varn));
                        break;
                    case INTEGER_64_TYPE:
                        longsigned = MTPL_Strtoint(varv);
                        variable.int64 = (int64_t)longsigned.siint;
                        heap = HEAP_Add(heap, INTEGER_64_TYPE, &variable, MTPL_Bhash(varn));
                        heap = HEAP_Get(heap, MTPL_Bhash(varn));
                        break;
                }
                strcpy(varn, ""); // yeet
                strcpy(vart, ""); // yeet
                strcpy(varv, ""); // yeet

            }
            // ALERT: handle stdprint 'function'
            for(int vari = 10; vari <= 10; vari++){
                    //printf("TTT:%s\n", removeWhiteSpace(memwrap_p->words_list[index]));
                    if(strcmp(removeWhiteSpace(memwrap_p->words_list[index]), vardefs[vari]) == 0){

                        if(strstr(memwrap_p->words_list[index+1], "\"") != NULL){
                            tc = 1;
                            stdprint(removeWhiteSpace(memwrap_p->words_list[index+tc]), NULL);
                            do{
                                tc++;
                                stdprint(removeWhiteSpace(memwrap_p->words_list[index+tc]), NULL);
                            }while(strstr(memwrap_p->words_list[index+tc], "\"") == NULL);

                            continue;
                        }else{
                            printf("%d\n", MTPL_Bhash(" a "));
                            heap = HEAP_Get(heap, MTPL_Bhash(" a "));
                            if(heap->last_retv == NULL){

                                assert(heap->last_retv != NULL);

                                fprintf(stderr, "error, line %d, variable not defined\n", p_counter);
                                p_run = false; // stop program execution
                            }
                            switch(heap->last_retv->type){
                                case UNSIGNED_INTEGER_8_TYPE:
                                    longsigned.unint = *((uint8_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), NULL);
                                    break;
                                case UNSIGNED_INTEGER_16_TYPE:
                                    longsigned.unint = *((uint16_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), NULL);
                                    break;
                                case UNSIGNED_INTEGER_32_TYPE:
                                    longsigned.unint = *((uint32_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), NULL);
                                    break;
                                case UNSIGNED_INTEGER_64_TYPE:
                                    longsigned.unint = *((uint64_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), NULL);
                                    break;
                                case INTEGER_8_TYPE:
                                    longsigned.unint = *((int8_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), NULL);
                                    break;
                                case INTEGER_16_TYPE:
                                    longsigned.unint = *((int16_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), NULL);
                                    break;
                                case INTEGER_32_TYPE:
                                    longsigned.unint = *((int32_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), NULL);
                                    break;
                                case INTEGER_64_TYPE:
                                    longsigned.unint = *((int64_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), NULL);
                                    break;
                        }

                        }

                    }
                }
            }
            strcpy(tcp, ""); // yeet
    }
    return HEAP_Destroy(heap);
}
