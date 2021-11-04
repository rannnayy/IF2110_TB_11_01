/********* MOVE HEADER *********/
/*
    File Name   : move.h
    Author      : K01_11
    Last Update : 28/10/2021
    Description : Function to move Mobita, count time, money, and capacity.
*/

#include <stdio.h>
#include <stdlib.h>

#include "pcolor.h"
#include "boolean.h"
#include "listdin.h"
#include "matrix.h"
#include "map.h"

void move (MAP Map, char* current_loc, Matrix adjMatrix, ListDin building, POINT headQuarter);
