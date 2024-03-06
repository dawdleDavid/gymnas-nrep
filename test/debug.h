#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>
#define debpi(ln, integer) fprintf(stdout, "%d: %d\n", ln, integer)
#define debps(ln, string) fprintf(stdout, "%d: %s\n", ln, string)
#define debpp(ln, pointer) fprintf(stdout, "%d:  %p\n", ln, pointer)
#define debpc(ln, character) fprintf(stdout, "%d:  %c\n", ln, character)
#define deberr(ln, err) fprintf(stderr, "\033[31;1;4mERROR LINE%d:%s\033[0m\n", ln, err)
#endif
