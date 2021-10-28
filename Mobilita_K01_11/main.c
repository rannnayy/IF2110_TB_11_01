/********* MAIN PROGRAMME *********/
/*
    File Name   : main.c
    Author      : K01_11
    Last Update : 27/10/2021
    Description : Main Programme of Mobilita (Tubes Alstrukdat K01 Kelompok 11).
*/

#include <stdio.h>
#include <stdlib.h>
/*
#include "wordmachine.h"
#include "point.h"
#include "listdin.h"
#include "matrix.h"
#include "list_linked.h"
#include "pcolor.h"
#include "node.h"
#include "charmachine.h"
#include "map.h"
*/

#include "wordmachine.c"
#include "point.c"
#include "listdin.c"
#include "matrix.c"
#include "list_linked.c"
#include "pcolor.c"
#include "node.c"
#include "charmachine.c"
#include "start_game.c"
#include "map.c"

// FUNCTIONS AND PROCEDURES
void DigitsToInt(Word digits, int* var);
void StartGame(int* N, int* M, int* nLoc, int* nOrder, POINT* headQuarter, ListDin* building, Matrix* adjMatrix, List* orders);
MAP StartMapConfiguration(int* N, int* M, POINT* headQuarter, ListDin* building, Matrix* adjMatrix);

// MAIN FUNCTION
int main()
{
    int N, M, nLoc, nOrder;
    POINT headQuarter;
    ListDin building;
    Matrix adjMatrix;
    List orders;
    MAP Map;
    char current_loc;

    StartGame(&N, &M, &nLoc, &nOrder, &headQuarter, &building, &adjMatrix, &orders);
    Map = StartMapConfiguration(&N, &M, &headQuarter, &building, &adjMatrix);

    current_loc = '8'; /* always start at headQuarter */
    /* use char instead of POINT to ease referencing */

    displayMap(Map);
    displayColoredMap(Map, current_loc, adjMatrix, building);

    return 0;
}
