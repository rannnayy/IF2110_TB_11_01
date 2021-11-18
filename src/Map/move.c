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

int readInt()
{
    int var = 0;

    startWordConsole();
    DigitsToInt(currentWord, &(var));

    return var;
}

void move (MAP Map, char* current_loc, Matrix adjMatrix, ListDin building, POINT headQuarter, int* current_time, List inProgress, boolean* speedBoost, int* boostCount, boolean efekSenterPengecil) {
/* Memindahkan Mobita ke lokasi baru yang dapat diakses sesuai adjMatrix.
   Menambahkan waktu 1 (default) atau sesuai efek gadget/ability/item. */
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
    newLoc = readInt();
    while (newLoc < 0 || newLoc > length(accessibleBuilding)) {
        printf("Posisi yang dipilih? (ketik 0 jika ingin kembali)\n\n");
        printf("ENTER COMMAND (integer): ");
        newLoc = readInt();
    }

    if (newLoc != 0) {
        *current_loc = ELMT_CHAR(accessibleBuilding, newLoc-1);
        printf("\nMobita sekarang berada di titik %c ", *current_loc);
        TulisPOINT(ELMT_POINT(accessibleBuilding, newLoc-1));
        printf("!\n");

        /* tambahkan waktu */
        if(*speedBoost && *boostCount <= 10){
            *boostCount += 1;
            if(*boostCount%2 == 0){
                *current_time += 1;
            }

            if(*boostCount == 10){
                *speedBoost = false;
                *boostCount = 0;
            }
        }
        else if (efekSenterPengecil) {
            *current_time = *current_time + 1 + countHeavyItem(inProgress) - 1;
        }  
        else {
            *current_time = *current_time + 1 + countHeavyItem(inProgress);
        }
    }
}

void teleport(char* current_loc, ListDin building) {
/* Memindahkan Mobita ke lokasi apa pun tanpa menambahkan waktu.
   Implementasi dari gadget Pintu Ke Mana Saja. */
    /* KAMUS LOKAL */
    int i, newLoc;

    /* ALGORITMA */
    printf("Posisi yang dapat dicapai:");
    printf("\n");

    printf("1. 8\n");
    for (i = 1; i <= length(building); i++) {
        printf("%d. ", i+1);
        printf("%c\n", ELMT_CHAR(building, i-1));
    }

    printf("\n");
    printf("Posisi yang dipilih?\n\n");
    printf("ENTER COMMAND (integer): ");
    newLoc = readInt();
    while (newLoc < 1 || newLoc > length(building)+1) {
        printf("\nPilihanmu tidak tersedia. Posisi yang dipilih?\n\n");
        printf("ENTER COMMAND (integer): ");
        newLoc = readInt();
    }

    if (newLoc != 0) {
        if (newLoc == 1) {
            *current_loc = '8';
        }
        else {
            *current_loc = ELMT_CHAR(building, newLoc-2);
        }
        printf("\nMobita sekarang berada di titik %c ", *current_loc);
        TulisPOINT(ELMT_POINT(building, newLoc-2));
        printf("!\n");
    }
}