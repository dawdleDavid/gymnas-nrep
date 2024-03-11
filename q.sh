if gcc -Wall -Wpedantic -g -o mtpl frontend/main.c frontend/readfile.c core/src/strings.c core/src/parser.c core/src/hash.c core/src/heap.c core/head/strings.h core/head/hash.h core/head/heap.h frontend/readfile.h mtpl.h core/src/stdstream.c core/head/stdstream.h -lm; then
	printf "\033[11;1;4mBUILD SUCCESS\033[0m\n"
	./mtpl -r test.mtpl
else
	printf "\033[31;1;4mBUILD FAILIURE\033[0m\n"
fi
