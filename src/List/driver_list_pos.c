#include <stdio.h>
#include "listpos.h"

int main()
{
    ListPos exList1, exList2, exList3;

    CreateListPos(&exList1);
    displayList_ListPos(exList1);
    printf("\n");

    printf("%d", length_ListPos(exList1));
    printf("\n");

    printf("%d", isIdxValid_ListPos(exList1, 50));
    printf("\n");

    printf("%d", isIdxEff_ListPos(exList1, 1));
    printf("\n");

    printf("%d", isEmpty_ListPos(exList1));
    printf("\n");

    printf("%d", isFull_ListPos(exList1));
    printf("\n");

    readList_ListPos(&exList1);
    displayList_ListPos(exList1);
    printf("\n");

    readList_ListPos(&exList2);
    displayList_ListPos(exList2);
    printf("\n");

    exList3 = plusMinusTab(exList1, exList2, true);
    displayList_ListPos(exList3);
    printf("\n");

    printf("%d", isListEqual_ListPos(exList1, exList2));
    printf("\n");

    printf("%d", indexOf_ListPos(exList1, 1));
    printf("\n");

    int outMax, outMin;
    extremes_ListPos(exList1, &outMax, &outMin);
    printf("%d %d", outMax, outMin);
    printf("\n");

    printf("%d", isAllEven_ListPos(exList1));
    printf("\n");

    sort_ListPos(&exList1, true);
    displayList_ListPos(exList1);
    printf("\n");

    insertLast_ListPos(&exList1, 20);
    displayList_ListPos(exList1);
    printf("\n");

    int n = -1;
    deleteLast_ListPos(&exList1, &n);
    printf("%d\t", n);
    displayList_ListPos(exList1);
    printf("\n");

    return 0;
}

