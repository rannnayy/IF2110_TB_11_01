/* Driver ADT List Linked */

#include <stdio.h>
#include "list_linked.h"
// #include "list_linked.c"

int main() {
    /* KAMUS */
    List l1, l2, l3;
    Elements element1, element2, element3, element, trash;
    //Address el1, el2;

    /* ALGORITMA */
    /* buat list linked */
    CreateList(&l1);

    /* periksa empty */
    if (isLinkedListEmpty(l1)) {
        printf("Linked list kosong.\n");
    }
    else {
        printf("Linked list tidak kosong.\n");
    }
    
    /* periksa length, harusnya 0 */
    printf("%d\n", lengthLinkedList(l1));

    /* inisialisasi elemen 1 dan 2*/
    element1.nTime = 1;
    element1.pickUp = 'A';
    element1.dropOff = 'B';
    element1.itemType = 'N';
    element1.perish = 0;
    //el1 = newNode(element1);
    element2.nTime = 2;
    element2.pickUp = 'C';
    element2.dropOff = 'D';
    element2.itemType = 'P';
    element2.perish = 10;
    //el2 = newNode(element2);
    element3.nTime = 3;
    element3.pickUp = 'E';
    element3.dropOff = 'F';
    element3.itemType = 'H';
    element3.perish = 0;
    //el3 = newNode(element3);

    /* insertFirst */
    insertLinkedListFirst(&l1, element2);
    insertLinkedListFirst(&l1, element1);

    /* tampilkan linked list, sisa element1, element2 */
    displayLinkedList(l1);
    printf("\n");

    /* periksa length, harusnya 2 */
    printf("%d\n", lengthLinkedList(l1));

    /* periksa empty */
    if (isLinkedListEmpty(l1)) {
        printf("Linked list kosong.\n");
    }
    else {
        printf("Linked list tidak kosong.\n");
    }

    /* get elemen indeks 1 */
    element = getLinkedListElmt(l1, 1);

    /* display Elemen */
    printf("%d\n", element.nTime);
    printf("%c\n", element.pickUp);
    printf("%c\n", element.dropOff);
    printf("%c\n", element.itemType);
    printf("%d\n", element.perish);

    /* set elemen indeks 1 dengan element3 */
    setLinkedListElmt(&l1, 1, element3);

    /* tampilkan linked list */
    displayLinkedList(l1);
    printf("\n");

    /* cari indeks element1, harusnya 0 */
    printf("%d\n", indexOfLinkedList(l1, element1));

    /* cari indeks element2, harusnya IDX_UNDEF */
    printf("%d\n", indexOfLinkedList(l1, element2));

    /* insertLast, sisa element1, element3, element2 */
    insertLinkedListLast(&l1, element2);

    /* tampilkan linked list */
    displayLinkedList(l1);
    printf("\n");

    /* deleteAt, sisa element1, element2 */
    deleteLinkedListAt(&l1, 1, &trash);

    /* tampilkan linked list */
    displayLinkedList(l1);
    printf("\n");

    /* insertAt, sisa element1, element3, element2 */
    insertLinkedListAt(&l1, element3, 1);

    /* tampilkan linked list */
    displayLinkedList(l1);
    printf("\n");

    /* deleteLast, sisa element1, element3 */
    deleteLinkedListLast(&l1, &trash);

    /* tampilkan linked list */
    displayLinkedList(l1);
    printf("\n");

    /* deleteFirst, sisa element3 */
    deleteLinkedListFirst(&l1, &trash);

    /* tampilkan linked list */
    displayLinkedList(l1);
    printf("\n");

    /* buat list linked baru */
    CreateList(&l2);
    
    /* insertFirst 2 elemen */
    insertLinkedListLast(&l2, element2);
    insertLinkedListLast(&l2, element1);

    /* tampilkan linked list */
    displayLinkedList(l2);
    printf("\n");

    /* concat */
    l3 = concatLinkedList(l1, l2);

    /* tampilkan linked list */
    displayLinkedList(l3);
    printf("\n");

    return 0;
}