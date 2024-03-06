# Makefile for mtpl
#
#
#
edit: main.o readfile.o
	cc -o mtpl main.o readfile.o

main.o: frontend/main.c frontend/readfile.h
	cc -c frontend/main.c
readfile.o: frontend/readfile.c
	cc -c frontend/readfile.c
rmex:
	rm mtpl
.PHONY : main.o readfile.o

clean:
	rm *.o
simple: frontend/main.c frontend/readfile.c core/src/strings.c core/src/parser.c core/src/hash.c core/src/heap.c core/src/stdstream.c core/head/stdstream.h core/head/strings.h core/head/hash.h core/head/heap.h frontend/readfile.h mtpl.h
	gcc -Wall -Wpedantic -g -o mtpl frontend/main.c frontend/readfile.c core/src/strings.c core/src/parser.c core/src/hash.c core/src/heap.c core/head/strings.h core/head/hash.h core/head/heap.h frontend/readfile.h mtpl.h core/src/stdstream.c core/head/stdstream.h
