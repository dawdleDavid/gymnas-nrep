#include <stdio.h>
#include <assert.h>

#include <string.h>
#include <assert.h>
#define ROW_LIMIT 256
/*
    function to test goes here
*/
int debug = 0;

#define STRING 1
#define INT 2
#define CHAR 3




void parse(){
    char* buffer = "TWO WORDS\nNEW LINE\n";


    char word[ROW_LIMIT]; char words_list[ROW_LIMIT][ROW_LIMIT];

    int walk = -1,words=0;

    int word_index = 0;

    puts("1");
    for(int character = 0; character <= strlen(buffer); character++){
        walk++;
        if(buffer[character] == ' ' || buffer[character] == '\n'){
            printf("%d %d\n", character, walk);
            for(int index = (character-walk); index <= character; index++){
                word[word_index] = buffer[index];
                word_index++;
            }
            // de BUG
            printf("words(n): %d\n", words);
            printf("word_list[0]: %s\n", words_list[0]);
            for(int i = 0; i <= 256; i++){
                printf("word[%d]: %c\n", i, word[i]);
            }
            // de BUG
            strcpy(words_list[words], word);
            words++;

            // clean the array...

            for(int i = 0; i <= ROW_LIMIT; i++){
                word[i] = (char)0;
            }

            walk = 0; word_index = 0;
        }

    }
    // de BUG
    for(int i = 0; i <= 20; i++){
        printf("words_list[%d]%s\n", i, words_list[i]);
    }
    printf("\n\n\n________\n%s", words_list[1]);
    // de BUG
}

int main(){
    // comment and uncommnet to test diffrent things
    parse();
    //findKeyword(test_data);



}
