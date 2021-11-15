/********* MOVE *********/
/*
    File Name   : move.c
    Author      : K01_11
    Last Update : 28/10/2021
    Description : Function to move Mobita, count time, money, and capacity.
*/

#include <stdio.h>
#include <stdlib.h>

#include "move.h"

void move (MAP Map, char* current_loc, Matrix adjMatrix, ListDin building, POINT headQuarter, int* current_time, List inProgress) {
    /* KAMUS LOKAL */
    int countAccessible, i, newLoc;
    ListDin accessibleBuilding;

    /* ALGORITMA */
    printf("Posisi yang dapat dicapai:");
    printf("\n");
    countAccessible = 0;
    CreateListDin(&accessibleBuilding, 27);

    /* hitung banyak accessible */
    if ((isAccessible('8', *current_loc, adjMatrix, building)) && ('8' != *current_loc)) {
        NEFF(accessibleBuilding)++;
        ELMT_CHAR(accessibleBuilding, countAccessible) = '8';
        ELMT_POINT(accessibleBuilding, countAccessible) = headQuarter;
        countAccessible++;
    }
    i = 0;
    while (i < length(building)) {
        if ((isAccessible(ELMT_CHAR(building, i), *current_loc, adjMatrix, building)) && (ELMT_CHAR(building, i) != *current_loc)) {
            NEFF(accessibleBuilding)++;
            ELMT_CHAR(accessibleBuilding, countAccessible) = ELMT_CHAR(building, i);
            ELMT_POINT(accessibleBuilding, countAccessible) = ELMT_POINT(building, i);
            countAccessible++;
        }
        i++;
    }

    i = 0;
    while (i < NEFF(accessibleBuilding)) {
        printf("%d. %c ", i+1, ELMT_CHAR(accessibleBuilding, i));
        TulisPOINT(ELMT_POINT(accessibleBuilding, i));
        printf("\n");
        i++;
    }

    printf("Posisi yang dipilih? (ketik 0 jika ingin kembali)\n\n");
    printf("ENTER COMMAND (integer): ");
    newLoc = 0;
    startWordConsole();
    DigitsToInt(currentWord, &(newLoc));
    while (newLoc < 0 || newLoc > length(accessibleBuilding)) {
        printf("Posisi yang dipilih? (ketik 0 jika ingin kembali)\n\n");
        printf("ENTER COMMAND (integer): ");
        startWordConsole();
        newLoc = 0;
        DigitsToInt(currentWord, &(newLoc));
    }

    if (newLoc != 0) {
        *current_loc = ELMT_CHAR(accessibleBuilding, newLoc-1);
        printf("\nMobita sekarang berada di titik %c ", *current_loc);
        TulisPOINT(ELMT_POINT(accessibleBuilding, newLoc-1));
        printf("!\n");

        /* tambahkan waktu dengan 1 */
        *current_time = *current_time + 1 + countHeavyItem(inProgress);
    }
}
