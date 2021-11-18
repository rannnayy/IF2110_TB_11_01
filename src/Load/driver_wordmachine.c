#include <stdio.h>
#include "wordmachine.h"


int main () {
    Word command;
    command.contents[0]='a';
    command.contents[1]='d';
    command.contents[2]='a';
    command.length=3;
    startWordConsole();
    if (isWordEqual(command)) { //jika input = "ada"
        printf("sama\n");
    }
    else {
        printf("tidak sama\n");
    }

    
    startWordConsole();
    while (!endWord) {
        for (int i=0;i<currentWord.length;i++) {
            printf("%c", currentWord.contents[i]);
        }
        printf("\n"); //memberi newline pada setiap kata
        advWordConsole();
    }


    return 0;
}