/********* MAIN PROGRAMME *********/
/*
    File Name   : main.c
    Author      : K01_11
    Last Update : 27/10/2021
    Description : Main Programme of Mobilita (Tubes Alstrukdat K01 Kelompok 11).
*/

#include <stdio.h>
#include <stdlib.h>
#include "wordmachine.h"
#include "point.h"
#include "listdin.h"
#include "matrix.h"
#include "list_linked.h"
#include "pcolor.h"
#include "start_game.c"

// FUNCTIONS AND PROCEDURES
void DigitsToInt(Word digits, int* var);
void StartGame(int* N, int* M, int* nLoc, int* nOrder, POINT* headQuarter, ListDin* building, Matrix* adjMatrix, List* orders);

// MAIN FUNCTION
int main()
{
    int N, M, nLoc, nOrder;
    POINT headQuarter;
    ListDin building;
    Matrix adjMatrix;
    List orders;

    StartGame(&N, &M, &nLoc, &nOrder, &headQuarter, &building, &adjMatrix, &orders);

    return 0;
}
