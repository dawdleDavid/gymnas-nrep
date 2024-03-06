#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h> // remove later
#include <string.h>
void* mem_alloc(void* data, int size){


    void *ptr = mmap ( NULL, size,
      PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );

    if(ptr == (void *)-1){
        puts("memory allocation failed");
        return (void*)-1;
    }
    memcpy(ptr, data, size);   // KOPIERA ÖVER MINNET, ALERT: SEGFAULT! (chorus of spaceballs theme) (no longer but props soon again <--)


    return ptr;
}


int mem_free(void* ptr, long int size){
    if(munmap(ptr, size) == 0){
        printf("dealloc %ld bytes, ptr points to adress: %p\n", size, ptr);
        return 0;
    }return 1;
}
