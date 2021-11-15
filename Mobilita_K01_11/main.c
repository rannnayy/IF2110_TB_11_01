/********* MAIN PROGRAM *********/
/*
    File Name   : main.c
    Author      : K01_11
    Last Update : 27/10/2021
    Description : Main Programme of Mobilita (Tubes Alstrukdat K01 Kelompok 11).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wordmachine.h"
#include "point.h"
#include "listdin.h"
#include "matrix.h"
#include "list_linked.h"
#include "pcolor.h"
#include "node.h"
#include "charmachine.h"
#include "map.h"
#include "prioqueue.h"
#include "orderItems.h"
#include "stack.h"
#include "start_game.h"
#include "move.h"
#include "listpos.h"
#include "gadget.h"
/*
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
*/

// FUNCTIONS AND PROCEDURES
//void DigitsToInt(Word digits, int* var);
//void StartGame(int* N, int* M, int* nLoc, int* nOrder, POINT* headQuarter, ListDin* building, Matrix* adjMatrix, List* orders, PrioQueue *orderedOrders);
//MAP StartMapConfiguration(int* N, int* M, POINT* headQuarter, ListDin* building, Matrix* adjMatrix);

// MAIN FUNCTION
int main()
{
    int N, M, nLoc, nOrder, nToDoList, nInProgress, nInventory;
    /* int  bagCapacity = 3; ganti jadi current_bagcapacity */
    POINT headQuarter;
    ListDin building;
    Matrix adjMatrix;
    List orders, toDoList, inProgress;
    CreateList(&toDoList); CreateList(&inProgress);
    MAP Map;
    char current_loc;
    int current_money, current_time, current_bagcapacity;
    int time_inc, boostCount, returnAbility, kainPembungkusWaktuGadget;
    boolean efekVIP, efekHeavyItem, speedBoost;
    Stack bag;
    PrioQueue orderedOrders;
    ListPos inventory;
    CreateListPos(&inventory);
    char command[20];
    boolean gameOn;

    printf("\n");
    printf("\t\t _|      _|    _|_|    _|_|_|    _|_|_|  _|        _|_|_|  _|_|_|_|_|    _|_|    \n");
    printf("\t\t _|_|  _|_|  _|    _|  _|    _|    _|    _|          _|        _|      _|    _|  \n");
    printf("\t\t _|  _|  _|  _|    _|  _|_|_|      _|    _|          _|        _|      _|_|_|_|  \n");
    printf("\t\t _|      _|  _|    _|  _|    _|    _|    _|          _|        _|      _|    _|  \n");
    printf("\t\t _|      _|    _|_|    _|_|_|    _|_|_|  _|_|_|_|  _|_|_|      _|      _|    _|  \n\n");

    /*
    LoadGame(&N, &M, &nLoc, &nOrder, &headQuarter, &building, &adjMatrix, &orders,
              &orderedOrders, &current_loc, &current_time, &current_money, &current_bagcapacity,
              &nToDoList, &toDoList, &nInProgress, &inProgress, &nInventory, &inventory);
    */
    StartGame(&N, &M, &nLoc, &nOrder, &headQuarter, &building, &adjMatrix, &orders, &orderedOrders);
    Map = StartMapConfiguration(&N, &M, &headQuarter, &building, &adjMatrix);

    /* start config */
    current_time = 0;
    current_money = 0;
    current_bagcapacity = 10;
    time_inc = 1;
    boostCount = 0;
    speedBoost = false;
    efekVIP = false;
    current_loc = '8'; /* always start at headQuarter */
    /* use char instead of POINT to ease referencing */
    gameOn = true;

    /* cek identitas Mobita */
    printf("\nWaktu: %d\n", current_time);

    /* attempt of making insert command, use strcmp for now */
    printf("\nENTER COMMAND: ");
    startWordConsole();
    memset(&command, '\0', sizeof(command));
    memcpy(command, currentWord.contents, currentWord.length);

    while (strcmp(command, "EXIT") != 0) {
        updateToDoList(&toDoList, &orderedOrders, current_time, &efekVIP);
        gameOn = endGame(current_loc, current_money, toDoList, inProgress, bag);
        if (!gameOn){
            printf("Selamat anda telah menyelesaikan permainan mobita dalam %d satuan waktu\n\n!", current_time);
            break;
        }
        //displayStack(bag);
        if (strcmp(command, "MOVE") == 0) {
            move(Map, &current_loc, adjMatrix, building, headQuarter, &current_time, &time_inc);
            if(speedBoost && boostCount <= 10){
                time_inc -= 1;
                if(boostCount == 10){
                    boostCount = 0;
                    speedBoost = false;
                }
                else
                    boostCount += 1;
            }
        }
        else if (strcmp(command, "MAP") == 0) {
            displayColoredMap(Map, current_loc, adjMatrix, building, inProgress, toDoList);
            // displayMap(Map);
        }
        else if (strcmp(command, "TO_DO") == 0) {
            printToDoList(&toDoList);
        }
        else if (strcmp(command, "IN_PROGRESS") == 0) {
            printInProgress(&inProgress);
        }
        else if (strcmp(command, "PICK_UP") == 0) {
            pickUp(&toDoList, &inProgress, &bag, &current_loc, &current_bagcapacity, efekVIP, &efekHeavyItem);
            if(efekHeavyItem){
                speedBoost = false;
            }
        }
        else if (strcmp(command, "DROP_OFF") == 0) {
            dropOff(&toDoList, &inProgress, &bag, &current_loc, &efekVIP, &efekHeavyItem, &current_money, &current_bagcapacity, &time_inc, &speedBoost, &returnAbility);
        }
        else if (strcmp(command, "BUY") == 0) {
            buyGadget(&inventory, &current_money);
        }
        else if (strcmp(command, "INVENTORY") == 0) {
            displayInventory(&inventory, &current_bagcapacity, &time_inc, Map, &current_loc, adjMatrix, building, headQuarter, &current_time);
        }
        else if (strcmp(command, "HELP") == 0) {
            Help();
        }
        else {
            printf("COMMAND salah. Ketik 'HELP' untuk bantuan atau ketik ulang COMMAND.\n");
        }

        /* cek identitas Mobita */
        printf("\nWaktu: %d\n", current_time);

        printf("\nENTER COMMAND: ");
        startWordConsole();
        memset(&command, '\0', sizeof(command));
        memcpy(command, currentWord.contents, currentWord.length);
    }
    SaveGame(N, M, nLoc, nOrder, headQuarter, building, adjMatrix, orders, orderedOrders, current_loc, current_time, current_money,
             current_bagcapacity, nToDoList, toDoList, nInProgress, inProgress, nInventory, inventory);

    return 0;
}
