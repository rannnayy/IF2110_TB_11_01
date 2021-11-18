/* Driver ADT Stack */

#include <stdio.h>
#include "stack.h"
// #include "stack.c"

int main() {
    /* KAMUS */
    int i;
    Stack s;
    stackEl element1, element2, trash;

    /* ALGORITMA */
    /* buat stack */
    CreateStack(&s);

    /* tampilkan stack */
    displayStack(s);
    printf("\n");

    /* periksa stack empty dan stack full */
    if (isStackEmpty(s)) {
        printf("Stack kosong.\n");
    }
    else {
        printf("Stack tidak kosong.\n");
    }
    if (isStackFull(s)) {
        printf("Stack penuh.\n");
    }
    else {
        printf("Stack tidak penuh.\n");
    }
    printf("\n");

    /* inisialisasi elemen 1 dan 2*/
    element1.nTime = 1;
    element1.pickUp = 'A';
    element1.dropOff = 'B';
    element1.itemType = 'N';
    element1.perish = 0;
    element2.nTime = 2;
    element2.pickUp = 'C';
    element2.dropOff = 'D';
    element2.itemType = 'P';
    element2.perish = 10;

    /* isi stack dengan 2 elemen */
    push(&s, element1);
    push(&s, element2);

    /* tampilkan stack */
    displayStack(s);
    printf("\n");

    /* pop elemen teratas */
    pop(&s, &trash);

    /* tampilkan stack, harusnya sisa element1 */
    displayStack(s);
    printf("\n");

    /* isi element2, lalu element1 lagi */
    push(&s, element2);
    push(&s, element1);

    /* tampilkan stack, harusnya sisa 3 elemen */
    displayStack(s);
    printf("\n");

    /* pop elemen element 2 di tengah */
    popEl(&s, element2);

    /* tampilkan stack, harusnya sisa 2 elemen */
    displayStack(s);
    printf("\n");

    /* periksa stack empty dan stack full */
    if (isStackEmpty(s)) {
        printf("Stack kosong.\n");
    }
    else {
        printf("Stack tidak kosong.\n");
    }
    if (isStackFull(s)) {
        printf("Stack penuh.\n");
    }
    else {
        printf("Stack tidak penuh.\n");
    }
    printf("\n");

    /* isi 98 element1 */
    for (i = 0; i < 98; i++) {
        push(&s, element1);
    }

    /* periksa stack empty dan stack full */
    if (isStackEmpty(s)) {
        printf("Stack kosong.\n");
    }
    else {
        printf("Stack tidak kosong.\n");
    }
    if (isStackFull(s)) {
        printf("Stack penuh.\n");
    }
    else {
        printf("Stack tidak penuh.\n");
    }

    return 0;
}