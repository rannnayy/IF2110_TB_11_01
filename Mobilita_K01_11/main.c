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
    int time_inc, boostCount, returnAbility;
    boolean efekVIP, efekHeavyItem, speedBoost;
    Stack bag;
    CreateStack(&bag);
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
    returnAbility = 0; 
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

    while (!isWordEqual("EXIT")) {
        updateToDoList(&toDoList, &orderedOrders, current_time, &efekVIP);
        gameOn = endGame(current_loc, current_money, toDoList, inProgress, bag);
        
        // buat tes gadget
        // current_money += 1000;

        if (!gameOn){
            printf("Selamat anda telah menyelesaikan permainan mobita dalam %d satuan waktu\n\n!", current_time);
            break;
        }
        //displayStack(bag);
        if (isWordEqual("MOVE")) {
            int deltaTime = current_time;
            move(Map, &current_loc, adjMatrix, building, headQuarter, &current_time, inProgress, false);
            if(speedBoost && boostCount <= 10){
                time_inc -= 1;
                if(boostCount == 10){
                    boostCount = 0;
                    speedBoost = false;
                }
                else
                    boostCount += 1;
            }
            deltaTime = current_time - deltaTime;
            updatePerishable(&inProgress, deltaTime);
            removePerishable(&bag, &inProgress);
        }
        else if (isWordEqual("MAP")) {
            displayColoredMap(Map, current_loc, adjMatrix, building, inProgress, toDoList);
            // displayMap(Map);
        }
        else if (isWordEqual("TO_DO")) {
            printToDoList(&toDoList);
        }
        else if (isWordEqual("IN_PROGRESS")) {
            printInProgress(&inProgress);
        }
        else if (isWordEqual("PICK_UP")) {
            pickUp(&toDoList, &inProgress, &bag, &current_loc, &current_bagcapacity, efekVIP, &efekHeavyItem);
            if(efekHeavyItem){
                speedBoost = false;
            }
        }
        else if (isWordEqual("DROP_OFF")) {
            dropOff(&toDoList, &inProgress, &bag, &current_loc, &efekVIP, &efekHeavyItem, &current_money, &current_bagcapacity, &time_inc, &speedBoost, &returnAbility);
        }
        else if (isWordEqual("BUY")) {
            buyGadget(&inventory, &current_money);
        }
        else if (isWordEqual("INVENTORY")) {
            displayInventory(&inventory, &current_bagcapacity, &time_inc, Map, &current_loc, adjMatrix, building, headQuarter, &inProgress, &bag, &current_time);
        }
        else if (isWordEqual("BAG")){
            displayStack(bag);
        }
        else if (isWordEqual("ITEM")){
            itemInfo();
        }
        else if (isWordEqual("GADGET")){
            gadgetInfo();
        }
        else if (isWordEqual("ACTIVE_ABILITY")){
            if (speedBoost){
                printf("Ability Speed Boost aktif (%d lokasi)\n", boostCount);
            } else {
                printf("Tidak ada Ability yang aktif\n");
            }
        }
        else if (isWordEqual("HELP")) {
            Help();
        }
        else if(strcmp(command, "RETURN") == 0){
            returnToSender(&toDoList, &inProgress, &bag, &returnAbility);
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
