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
#include "../head/err.h"

// boolen expressions
#include "../head/bool.h"

#define COMPARE_SWITCH(longs) \
switch(heap->last_retv->type){\
    case UNSIGNED_INTEGER_8_TYPE:\
        longsigned.unint = *((uint8_t*)heap->last_retv->data);\
        longs = longsigned;\
        break;\
    case UNSIGNED_INTEGER_16_TYPE:\
        variable.uint16 = *((uint16_t*)heap->last_retv->data);\
        longsigned.unint = variable.uint16;\
        longs = longsigned;\
        break;\
    case UNSIGNED_INTEGER_32_TYPE:\
        longsigned.unint = *((uint32_t*)heap->last_retv->data);\
        longs = longsigned;\
        break;\
    case UNSIGNED_INTEGER_64_TYPE:\
        longsigned.unint = *((uint64_t*)heap->last_retv->data);\
        longs = longsigned;\
        break;\
    case INTEGER_8_TYPE:\
        longsigned.siint = *((int8_t*)heap->last_retv->data);\
        longs = longsigned;\
        break;\
    case INTEGER_16_TYPE:\
        longsigned.siint = *((int16_t*)heap->last_retv->data);\
        longs = longsigned;\
        break;\
    case INTEGER_32_TYPE:\
        longsigned.siint = *((int32_t*)heap->last_retv->data);\
        longs = longsigned;\
        break;\
    case INTEGER_64_TYPE:\
        longsigned.siint = *((int64_t*)heap->last_retv->data);\
        longs = longsigned;\
        break;\
    default:\
        genericError("corrupted type information", p_counter);\
        break;\
}



char* vardefs[13] = {
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
    "stdout ",
    "cmp ",
    "goto "
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
    char buffer[ROW_LIMIT];
    uint32_t p_counter = 0;
    MTPL_Heap* heap = HEAP_Init();
    MTPL_Variable variable;
    MTPL_Longsigned longsigned;
    bool p_run= true;
    char varn[ROW_LIMIT];
    char ex[64];
    char vart[64];
    char varv[ROW_LIMIT]; // use math o this to determine if this is resonable.
    char* print_temp;
    uint32_t tc = 0; //  temporary counter
    char tcp[ROW_LIMIT]; //  temporary char pointer
    char charvals[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    heap->last_retv = NULL;

    /* for comparisons */
    MTPL_Longsigned longs[2];
    Expression expression;
    /* Acctual parsing starts here... */

    bool Trueflag = false; // the bool used for evaluating boolen expressions

    while(p_run){
    ROW:
        tc = 0;
        char* row = fgets(buffer, ROW_LIMIT, file);
        p_counter++;
        puts("----------------------");
        printf("raw input row->%s\n", row);
        puts("----------------------");
        if(row == (char*)NULL){
            //printf("EOF\n");
            break;
        }

        if(buffer[0] == '.'){ continue; } // https://www.youtube.com/watch?v=3YmMNpbFjp0
            // do something with the line that you just got
        memwrap_p = findKeyword(&memwrap, row);

        for( int index = 0;index <= ROW_LIMIT; index++){
           // printf("%s(%d)\n", memwrap_p->words_list[index], p_counter);
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

                    }
                    if(strcmp(memwrap_p->words_list[index+2], " = ") != 0){
                        genericError("expected \"=\" before value assignment", p_counter);
                        p_run = false;
                    }
                    if (strpbrk(varv, "123456789") == NULL) {
                        genericError("invalid integer value", p_counter);
                    }

                    // reassigning varaibles

                    if(strcmp(memwrap_p->words_list[index+2], " = ") != 0){
                        genericError("expected \"=\" before value assignment", p_counter);
                        p_run = false;
                    }

                    puts(".............");
                    printf("varn:%sENDvart:%sENDvarv:%sEND\n", varn, vart, varv);
                    puts(".............");
            }


            if(strcmp(varn, "") != 0){
                switch(MTPL_Bhash(vart)){
                    case UNSIGNED_INTEGER_8_TYPE:
                        printf("UI8BH: %d\n", MTPL_Bhash(varn));
                        longsigned = MTPL_Strtoint(varv);
                        variable.uint8 = (uint8_t)longsigned.unint;
                        heap = HEAP_Add(heap, UNSIGNED_INTEGER_8_TYPE, &variable, MTPL_Bhash(varn));
                        break;
                    case UNSIGNED_INTEGER_16_TYPE:

                        printf("HR:%d\n", MTPL_Bhash(varn));


                        printf("BABSTI:%s\n", varv);

                        longsigned = MTPL_Strtoint(varv);

                        printf("BAASTI:%lu\n", longsigned.unint);

                        variable.uint16 = (uint16_t)longsigned.unint;


                        printf("BAU16AL: %d\n", variable.uint16);



                        heap = HEAP_Add(heap, UNSIGNED_INTEGER_16_TYPE, &variable, MTPL_Bhash(varn));

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
                strcpy(varn, "");
                strcpy(vart, "");
                strcpy(varv, "");

//
          for(int vari = 11; vari <= 12; vari++){
                if(index < ROW_LIMIT){
                    strcpy(varn, memwrap_p->words_list[index+1]);
                    strcpy(vart, memwrap_p->words_list[index]);
                    strcpy(varv, memwrap_p->words_list[index+2]);
                    strcpy(ex, memwrap_p->words_list[index+3]);
                }
                puts("hwat");
                if(strcmp(vart, vardefs[vari])){
                    switch(vari){
                        case 11:
                            tc = 0;
                            // check if they are numbers or not
                            if(strpbrk(varn, "1234567890") != NULL){
                                tc = 1;
                            }
                            if(strpbrk(varv, "1234567890") != NULL){
                                tc = 2;
                            }
                            if(strpbrk(varv, "1234567890") != NULL && strpbrk(varn, "1234567890") != NULL){
                                tc = 3;
                            }
                                switch(tc){
                                    case 0:
                                        heap = HEAP_Get(heap, MTPL_Bhash(varn));    // first

                                        COMPARE_SWITCH(longs[0]);
                                        heap = HEAP_Get(heap, MTPL_Bhash(ex));      // second

                                        COMPARE_SWITCH(longs[1]);

                                        expression.a = longs[0];
                                        expression.b = longs[1];
                                        strcpy(expression.op, varv);
                                        boolEval(expression);

                                    break;

                                case 1:
                                    // first
                                    break;
                                case 2:
                                    break;
                                case 3:
                                    break;
                            }
                            break;
                        case 12:
                            // if a variable is not constant
                            break;
                    }
                }
            }




                }
                    if(strcmp(removeWhiteSpace(memwrap_p->words_list[index]), vardefs[10]) == 0){
                        if(strstr(memwrap_p->words_list[index+1], "\"") != NULL){
                            tc = 1;
                            stdprint(removeWhiteSpace(memwrap_p->words_list[index+tc]), NULL);
                            do{
                                tc++;
                                stdprint(removeWhiteSpace(memwrap_p->words_list[index+tc]), NULL);
                            }while(strstr(memwrap_p->words_list[index+tc], "\"") == NULL);
                            goto ROW; // holy bananas thats scuffed
                            continue;
                        }else{

                            printf("HG: %d\n", MTPL_Bhash(memwrap_p->words_list[index+1]));
                            printf("UHRDI:%sEND\n", memwrap_p->words_list[index+1]);
                            printf("HT: %d\n", MTPL_Bhash("   \n\nyeet\n"));

                            heap = HEAP_Get(heap, (MTPL_Bhash(memwrap_p->words_list[index+1])));

                            assert(heap->last_retv->data != NULL);
                            //printf("%16u\n", *((uint16_t*)heap->last_retv->data));

                            /*
                            if(heap->last_retv->name != MTPL_Bhash(memwrap_p->words_list[index+1]) + 44){
                                genericError("undefined variable", p_counter);
                                return (HEAP_Destroy(heap));
                            }*/
                            switch(heap->last_retv->type){
                                case UNSIGNED_INTEGER_8_TYPE:
                                    printf("heap->last_retv->data: %ld\n", *((uint64_t*)heap->last_retv->data));
                                    longsigned.unint = *((uint8_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), 0);
                                    goto ROW;
                                case UNSIGNED_INTEGER_16_TYPE:
                                    puts("CT: UNSIGNED_INTEGER_16_TYPE");
                                    variable.uint16 = *((uint16_t*)heap->last_retv->data);
                                    longsigned.unint = variable.uint16;
                                    printf("before int to str>%u\n", variable.uint16);
                                    printf("after int to str>%s\n", MTPL_Inttostr(varn, longsigned, false));
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), 0);
                                    goto ROW;
                                case UNSIGNED_INTEGER_32_TYPE:
                                    longsigned.unint = *((uint32_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), 0);
                                    goto ROW;
                                case UNSIGNED_INTEGER_64_TYPE:
                                    //printf("%ld\n", *((uint64_t*)heap->last_retv->data));
                                    longsigned.unint = *((uint64_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), 0);
                                    goto ROW;
                                case INTEGER_8_TYPE:
                                    longsigned.siint = *((int8_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), 0);
                                    goto ROW;
                                case INTEGER_16_TYPE:
                                    longsigned.unint = *((int16_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), 0);
                                    goto ROW;
                                case INTEGER_32_TYPE:
                                    longsigned.unint = *((int32_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), 0);
                                    goto ROW;
                                case INTEGER_64_TYPE:
                                    longsigned.unint = *((int64_t*)heap->last_retv->data);
                                    stdprint(MTPL_Inttostr(varn, longsigned, false), 0);
                                    goto ROW;
                                default:
                                    genericError("corrupted type information", p_counter);
                                    goto ROW;
                                continue;
                            }
                        }
                    }
                }
            }
            strcpy(tcp, ""); // yeet
            strcpy(varn, "");
            strcpy(vart, "");
            strcpy(varv, "");
            heap->last_retv = NULL;
        }

    return HEAP_Destroy(heap);
}
