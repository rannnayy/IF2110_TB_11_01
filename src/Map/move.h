/********* MOVE HEADER *********/
/*
    File Name   : move.h
    Author      : K01_11
    Last Update : 28/10/2021
    Description : Function to move Mobita, count time, money, and capacity.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../boolean.h"
#include "pcolor.h"
#include "matrix.h"
#include "map.h"
#include "../Item/orderItems.h"
#include "../List/listdin.h"
#include "../Load/charmachine.h"
#include "../Load/wordmachine.h"
#include "../Load/start_game.h"

void move (MAP Map, char* current_loc, Matrix adjMatrix, ListDin building, POINT headQuarter, int* current_time, List inProgress, boolean* speedBoost, int* boostCount, boolean efekSenterPengecil);
/* Memindahkan Mobita ke lokasi baru yang dapat diakses sesuai adjMatrix.
   Menambahkan waktu 1 (default) atau sesuai efek gadget/ability/item. */

void teleport(char* current_loc, ListDin building);
/* Memindahkan Mobita ke lokasi apa pun tanpa menambahkan waktu.
   Implementasi dari gadget Pintu Ke Mana Saja. */

int readInt();