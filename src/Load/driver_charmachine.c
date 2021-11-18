#include "charmachine.h"
#include <stdio.h>

int main () {
    startConsole();
    while (!eot) {
        printf("%c", currentChar);
        advConsole();
    }
    return 0;
}