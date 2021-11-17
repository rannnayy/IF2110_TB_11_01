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

void move (MAP Map, char* current_loc, Matrix adjMatrix, ListDin building, POINT headQuarter, int* current_time, List inProgress, boolean teleport, boolean* speedBoost, int* boostCount);

int readInt();