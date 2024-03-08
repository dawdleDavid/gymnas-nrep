#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
/*debug*/
#include <assert.h>


#include "../head/heap.h"



/* TODO: remove clone fn def */
unsigned int HEAP_HashVaribleName(char name[MAX_VARIABLE_NAME_LENGHT]){
    unsigned int res = 0;
    for(int c = 0; c <= strlen(name); c++){
        res += ((unsigned int)name[c] * c); // reversed variable names now possible
    }
    return res;
}


void* mem_alloc(void* data, int size){


    void *ptr = mmap ( NULL, size,
      PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );

    if(ptr == (void *)-1){
        //puts("memory allocation failed");
        return (void *)NULL;
    }
    memcpy(ptr, data, size);   // KOPIERA ÖVER MINNET, ALERT: SEGFAULT! (chorus of spaceballs theme) (no longer but props soon again <--)
    return ptr;
}


int mem_free(void* ptr, long int size){
    if(munmap(ptr, size) == 0){
        //printf("dealloc %ld bytes, ptr points to adress: %p\n", size, ptr);
        return 0;
    }return 1;
}

struct MTPL_Heap* LL_Create(MTPL_Heap* heap, uint32_t size, void* pointer,unsigned int name){



    bool prev_flag = false;
    if(heap->number_of_nodes > 1){
        prev_flag = true;
    }
    if(prev_flag)
        heap->prev = heap->nodes->node;




    heap->nodes->node = (struct Node*)mem_alloc(&heap->nodes->node, sizeof(*heap->nodes->node));

    assert(heap->nodes->node != (struct Node*)NULL);


    if(prev_flag)
        heap->prev->next = heap->nodes->node;

    if(heap->number_of_nodes == 1){
        heap->start = heap->nodes->node;
    }else if(heap->number_of_nodes == 2){
        heap->start->next = heap->nodes->node;
    }

    heap->nodes->node->data = pointer;
    heap->nodes->node->name = name;
    heap->nodes->node->size = size;


    heap->nodes->node->next = heap->start;
    return heap;
}
int LL_List(int n, struct Node* start){
    // //puts("yee");
    struct Node* node = start;

    // //puts("haw");
    for(int i = 1; i <= n; i++){
        // //puts("boys");
        //printf("N:(%d) CONTAINED_POINTER:%p VARIABLE_NAME_HASHED:%x\n", i, node->data, node->name);
        if(i == 1){
            node = start->next;
            continue;
        }

        node = node->next;
    }
    if(n == 0){
        //puts("no nodes!");
    }

    return 0;
}

int LL_Remove(int n, struct Node* start, int choice){
    LL_List(n, start);

    struct Node* node = start;
    for(int i = 1; i <= n; i++){
        //printf("(%d) %p %p\n", i, &node->data, node->data);
        if(i == (choice-1)){
            //puts("ran");
            struct Node* temp = node->next;     // skapa temporär pekare till nästa nod
            node->next = temp->next;           //  flytta nuvarande nods pekare till temp
            mem_free(&temp, sizeof(*temp));   //   fria minnet för temp;
            break;
        }
        node = node->next;
    }
    n--;
    return n;
}



MTPL_Heap* HEAP_Main(MTPL_Heap* heap, uint32_t size, unsigned int opcode, void* data_ptr, unsigned int varname){
    unsigned int choice = 0;
        //puts("\n");
        switch(opcode){
            case HEAP_ADD:
                heap->number_of_nodes++; // one at a time
                heap = LL_Create(heap, size, data_ptr, varname);
                assert(heap->start != NULL);
                heap->size += size;
                break;
            case HEAP_LIST:
                LL_List(heap->number_of_nodes, heap->start);
                break;

            case HEAP_REMOVE:
                LL_List(heap->number_of_nodes, heap->start);
                //printf("Witch list would you like to remove?: ");
                scanf("%d", &choice);
                if(choice == 1){
                    heap->JariPekare = heap->start->next;
                    mem_free(heap->start, sizeof(*heap->node));
                    heap->start = (struct Node*)heap->JariPekare;
                    //printf("\n\n%p\n", heap->start);

                    heap->number_of_nodes--;
                    break;
                }
                //puts("ran LL_Remove");
                heap->number_of_nodes = LL_Remove(heap->number_of_nodes, heap->start, choice);
                break;
            case HEAP_FIND:
                choice = varname;
                struct Node* node = heap->start;
                for(int i = 1; i <= heap->number_of_nodes; i++){
                    if(choice == node->name){
                        // Edit struct and return
                        heap->last_retv = node;
                        //var
                        break;
                    }
                    if(i == 1){
                        node = heap->start->next;
                        continue;
                    }
                    node = node->next;
                }
                break;
        }
    return heap; // modified
}
/* remember that you need to mem_free this later! */
struct Node node;
struct Nodes nodes;
MTPL_Heap* HEAP_Init(){

    MTPL_Heap* heap = (MTPL_Heap*)malloc(sizeof(*heap)); /* another defeat */
    heap->nodes = &nodes;
    heap->node = &node;
    heap->number_of_nodes = 0;
    return heap;
}




MTPL_Heap* HEAP_Add(MTPL_Heap* heap, uint16_t vartype, MTPL_Variable* variable, unsigned int name){

    // ALLOC mem
    void* variable_mem;
    // Check mem
    if(variable_mem == (void *)-1){
        return (MTPL_Heap*)1;
    }
        // gigant switch statement time?

    /* Same size for unsigned and signed right? Not taking any chanses */
    uint32_t size = 0; // upper bound
    switch((uint16_t)vartype){
        case INTEGER_8_TYPE: size = INTEGER_8_SIZE;
            variable_mem = (void*)malloc(INTEGER_8_SIZE);
            memcpy(variable_mem, &variable->int8, size);
            break;
        case INTEGER_16_TYPE: size = INTEGER_16_SIZE;
            variable_mem = (void*)malloc(INTEGER_16_SIZE);
            memcpy(variable_mem, &variable->int16, size);
            break;
        case INTEGER_32_TYPE: size = INTEGER_32_SIZE;
            variable_mem = (void*)malloc(INTEGER_32_SIZE);
            memcpy(variable_mem, &variable->int32, size);
            break;
        case INTEGER_64_TYPE: size = INTEGER_64_SIZE;
            variable_mem = (void*)malloc(INTEGER_64_TYPE);
            memcpy(variable_mem, &variable->int64, size);
            break;
        case UNSIGNED_INTEGER_8_TYPE: size = UNSIGNED_INTEGER_8_SIZE;
            variable_mem = (void*)malloc(UNSIGNED_INTEGER_8_SIZE);
            memcpy(variable_mem, &variable->uint8, size);
            break;
        case UNSIGNED_INTEGER_16_TYPE: size = UNSIGNED_INTEGER_16_SIZE;
            variable_mem = (void*)malloc(UNSIGNED_INTEGER_16_SIZE);
            memcpy(variable_mem, &variable->uint16, size);
            break;
        case UNSIGNED_INTEGER_32_TYPE: size = UNSIGNED_INTEGER_32_SIZE;
            variable_mem = (void*)malloc(UNSIGNED_INTEGER_32_SIZE);
            memcpy(variable_mem, &variable->uint32, size);
            break;
        case UNSIGNED_INTEGER_64_TYPE: size = UNSIGNED_INTEGER_64_SIZE;
            variable_mem = (void*)malloc(UNSIGNED_INTEGER_64_SIZE);
            memcpy(variable_mem, &variable->uint64, size);
            break;
        case STRING_TYPE:
            /* Special case... Lets get back to this later
            variable_mem = (void*)mem_alloc(variable_mem, STRING_);
            */
            break;
        case CHARACTER_TYPE: size = CHARACTER_SIZE;
            variable_mem = (void*)malloc(CHARACTER_SIZE);
            memcpy(variable_mem, &variable->character, size);
            break;

    }
    assert(variable_mem != NULL);
    return HEAP_Main(heap, size, HEAP_ADD, variable_mem, name);
}
MTPL_Heap* HEAP_CleanContents(MTPL_Heap* heap){

    struct Node* node = heap->start;

    for(int i = 1; i <= heap->number_of_nodes; i++){
        free(node->data);
        if(i == 1){
            node = heap->start->next;
            continue;
        }

        node = node->next;
    }
    if(heap->number_of_nodes == 0){
        //puts("no nodes!");
    }

    return 0;
}

MTPL_Heap* HEAP_Get(MTPL_Heap* heap, unsigned int name){
    return HEAP_Main(heap, 0, HEAP_FIND, NULL, name);
}

int HEAP_Destroy(MTPL_Heap* heap){
    free(heap);
    return 0;
}
//(cd /home/david/Projekts/GY-EX && git add --all && git commit -m "för om gör rätt" && git push -u origi master)

