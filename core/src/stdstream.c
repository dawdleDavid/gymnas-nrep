

#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdint.h>


#include "../head/stdstream.h"
/* simply prints to the term,inal with a syscall... */
void stdprint(void* message, uint8_t type){
    syscall(SYS_WRITE, STDOUT_FILENO, message, strlen((char*)message));
}
