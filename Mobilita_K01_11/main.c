/********* MAIN PROGRAM *********/
/*
    File Name   : main.c
    Author      : K01_11
    Last Update : 27/10/2021
    Description : Main Programme of Mobilita (Tubes Alstrukdat K01 Kelompok 11).
*/

#include <stdio.h>
#include <stdlib.h>

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
#include "move.c"
#include "prioqueue.c"
#include "orderItems.c"
#include "stack.c"
#include "listpos.c"
#include "gadget.c"

// FUNCTIONS AND PROCEDURES
void DigitsToInt(Word digits, int* var);
void StartGame(int* N, int* M, int* nLoc, int* nOrder, POINT* headQuarter, ListDin* building, Matrix* adjMatrix, List* orders, PrioQueue *orderedOrders);
MAP StartMapConfiguration(int* N, int* M, POINT* headQuarter, ListDin* building, Matrix* adjMatrix);

// MAIN FUNCTION
int main()
{
    int N, M, nLoc, nOrder;
    /* int  bagCapacity = 3; ganti jadi current_bagcapacity */
    POINT headQuarter;
    ListDin building;
    Matrix adjMatrix;
    List orders, toDoList, inProgress;
    CreateList(&toDoList); CreateList(&inProgress);
    MAP Map;
    char current_loc;
    int current_money, current_time, current_bagcapacity;
    int time_inc;
    PrioQueue orderedOrders;
    ListPos inventory;
    CreateListPos(&inventory);
    char command[20];

    StartGame(&N, &M, &nLoc, &nOrder, &headQuarter, &building, &adjMatrix, &orders, &orderedOrders);
    Map = StartMapConfiguration(&N, &M, &headQuarter, &building, &adjMatrix);

    /* start config */
    current_time = 0;
    current_money = 0;
    current_bagcapacity = 3;
    time_inc = 1;
    current_loc = '8'; /* always start at headQuarter */
    /* use char instead of POINT to ease referencing */

    /* cek identitas Mobita */
    printf("\nWaktu: %d\n", current_time);

    /* attempt of making insert command, use strcmp for now */
    printf("\nENTER COMMAND: ");
    scanf("%s", &command);
    while (strcmp(command, "EXIT") != 0) {
        if (strcmp(command, "MOVE") == 0) {
            move(Map, &current_loc, adjMatrix, building, headQuarter, &current_time, &time_inc);
        }
        else if (strcmp(command, "MAP") == 0) {
            displayColoredMap(Map, current_loc, adjMatrix, building);
        }
        else if (strcmp(command, "TO_DO") == 0) {
            printToDoList(&orders);
        }
        else if (strcmp(command, "IN_PROGRESS") == 0) {
            printInProgress(&inProgress);
        }
        else if (strcmp(command, "BUY") == 0) {
            buyGadget(&inventory);
        }
        else if (strcmp(command, "INVENTORY") == 0) {
            displayInventory(&inventory);
        }

        /* cek identitas Mobita */
        printf("\nWaktu: %d\n", current_time);

        printf("\nENTER COMMAND: ");
        scanf("%s", &command);
    }

    return 0;
}
