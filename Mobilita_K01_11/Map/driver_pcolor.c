#include <stdio.h>
#include "pcolor.h"
#include "pcolor.c"

int main() {

    printf("String ini tidak berwarna A\n");
    printf("String ini berwarna cyan ");
    print_cyan('A');
    printf("\nString ini berwarna biru ");
    print_blue('A');
    printf("\nString ini berwarna hijau ");
    print_green('A');
    printf("\nString ini berwarna magenta ");
    print_magenta('A');
    printf("\nString ini berwarna merah ");
    print_red('A');
    printf("\nString ini berwarna kuning ");
    print_yellow('A');

    return 0;
}