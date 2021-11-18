#include <stdio.h>
#include <stdlib.h>
#include "listdin.h"

int main()
{
    ListDin exLD1, exLD2, exLD3;
    ElType max, min, valdel;

    CreateListDin(&exLD1, 10);
    displayList(exLD1);
    printf("\n");
    dealocate(&exLD1);

    CreateListDin(&exLD1, 10);
    printf("%d\n", length(exLD1));
    printf("%d\n", getLastIdx(exLD1));
    printf("%d\n", isIdxValid(exLD1, 2));
    printf("%d\n", isIdxEff(exLD1, 2));
    printf("%d\n", isEmpty(exLD1));
    printf("%d\n", isFull(exLD1));

    dealocate(&exLD1);

    CreateListDin(&exLD1, 10);
    readList(&exLD1);
    displayList(exLD1);
    printf("\n");

    CreateListDin(&exLD2, 10);
    readList(&exLD2);
    displayList(exLD2);
    printf("\n");

    CreateListDin(&exLD3, 10);
    exLD3 = plusMinusList(exLD1, exLD2, true);
    displayList(exLD3);
    printf("\n");

    printf("%d\n", isListEqual(exLD1, exLD2));
    printf("%d\n", indexOf(exLD1, 1));

    extremes(exLD1, &max, &min);
    printf("%d %d\n", max, min);

    copyList(exLD1, &exLD2);
    displayList(exLD1);
    displayList(exLD2);
    printf("\n");

    printf("%d\n", sumList(exLD1));
    printf("%d\n", countVal(exLD1, 1));
    printf("%d\n", isAllEven(exLD1));

    sort(&exLD1, true);
    displayList(exLD1);
    printf("\n");

    insertLast(&exLD1, 10);
    displayList(exLD1);
    printf("\n");

    deleteLast(&exLD1, &valdel);
    displayList(exLD1);
    printf("\n");

    printf("before growList : %d\n", CAPACITY(exLD1));
    growList(&exLD1, 50);
    printf("after growList : %d\n", CAPACITY(exLD1));

    shrinkList(&exLD1, 10);
    printf("after shrinkList : %d\n", CAPACITY(exLD1));

    compactList(&exLD1);
    printf("after compactList : %d\n", CAPACITY(exLD1));

    return 0;
}
