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

#include "Gadget/gadget.h"
#include "Item/prioqueue.h"
#include "Item/orderItems.h"
#include "Item/stack.h"
#include "List/listdin.h"
#include "List/list_linked.h"
#include "List/listpos.h"
#include "List/node.h"
#include "Load/wordmachine.h"
#include "Load/charmachine.h"
#include "Load/start_game.h"
#include "Map/point.h"
#include "Map/matrix.h"
#include "Map/pcolor.h"
#include "Map/map.h"
#include "Map/move.h"

/*
#include "Gadget/gadget.c"
#include "Item/prioqueue.c"
#include "Item/orderItems.c"
#include "Item/stack.c"
#include "List/listdin.c"
#include "List/list_linked.c"
#include "List/listpos.c"
#include "List/node.c"
#include "Load/wordmachine.c"
#include "Load/charmachine.c"
#include "Load/start_game.c"
#include "Map/point.c"
#include "Map/matrix.c"
#include "Map/pcolor.c"
#include "Map/map.c"
#include "Map/move.c"
*/

// Word definition
Word newGameWord = {"NEW_GAME", 8};
Word loadGameWord = {"LOAD_GAME", 9};
Word exitWord = {"EXIT", 4};
Word moveWord = {"MOVE", 4};
Word mapWord = {"MAP", 3};
Word toDoWord = {"TO_DO", 5};
Word inProgressWord = {"IN_PROGRESS", 11};
Word pickUpWord = {"PICK_UP", 7};
Word dropOffWord = {"DROP_OFF", 8};
Word buyWord = {"BUY", 3};
Word inventoryWord = {"INVENTORY", 9};
Word bagWord = {"BAG", 3};
Word gadgetWord = {"GADGET", 6};
Word itemWord = {"ITEM", 4};
Word activeAbilityWord = {"ACTIVE_ABILITY", 14};
Word helpWord = {"HELP", 4};
Word returnWord = {"RETURN", 6};
Word yWord = {"Y", 1};
Word YWord = {"y", 1};
Word nWord = {"n", 1};
Word NWord = {"N", 1};
Word cheatCode = {"CHEAT", 5};

// FUNCTIONS AND PROCEDURES
//void DigitsToInt(Word digits, int* var);
//void StartGame(int* N, int* M, int* nLoc, int* nOrder, POINT* headQuarter, ListDin* building, Matrix* adjMatrix, List* orders, PrioQueue *orderedOrders);
//MAP StartMapConfiguration(int* N, int* M, POINT* headQuarter, ListDin* building, Matrix* adjMatrix);

// MAIN FUNCTION
int main()
{
    int N, M, nLoc, nOrder, nOrderedOrders, nToDoList, nInProgress, nInventory;
    /* int  bagCapacity = 3; ganti jadi current_bagcapacity */
    POINT headQuarter;
    ListDin building;
    Matrix adjMatrix;
    List orders, toDoList, inProgress;
    CreateList(&toDoList); CreateList(&inProgress);
    MAP Map;
    char current_loc;
    int current_money, current_time, current_bagcapacity, ordersCount;
    int boostCount, returnAbility;
    boolean efekVIP, efekHeavyItem, speedBoost, efekSenterPengecil;
    Stack bag;
    CreateStack(&bag);
    PrioQueue orderedOrders;
    ListPos inventory;
    CreateListPos(&inventory);
    boolean gameOn;
    boolean gameStart;
    boolean gameSave;
    int lenBefore;
    char command[20];
    for(int i = 0; i < 20; i++){
        command[i] = '\0';
    }

    /*Inisialisasi nilai variabel game in general*/
    gameOn = true;
    boostCount = 0;
    speedBoost = false;
    efekVIP = false;
    lenBefore = 0;
    ordersCount = 0;
    efekSenterPengecil = false;

    printf("\n");
    printf("\t\t _|      _|    _|_|    _|_|_|    _|_|_|  _|        _|_|_|  _|_|_|_|_|    _|_|    \n");
    printf("\t\t _|_|  _|_|  _|    _|  _|    _|    _|    _|          _|        _|      _|    _|  \n");
    printf("\t\t _|  _|  _|  _|    _|  _|_|_|      _|    _|          _|        _|      _|_|_|_|  \n");
    printf("\t\t _|      _|  _|    _|  _|    _|    _|    _|          _|        _|      _|    _|  \n");
    printf("\t\t _|      _|    _|_|    _|_|_|    _|_|_|  _|_|_|_|  _|_|_|      _|      _|    _|  \n\n");

    printf("COMMAND yang tersedia: \n");
    printf("NEW_GAME, LOAD_GAME, dan EXIT \n\n");
    printf("\nENTER COMMAND: ");
    startWordConsole();
    for(int i = 0; i < currentWord.length; i++)
        command[i] = currentWord.contents[i];
    lenBefore = currentWord.length;
    gameStart = false;

    while (!gameStart){
        if (isWordEqual(newGameWord)){
            gameStart = true;
            StartGame(&N, &M, &nLoc, &nOrder, &headQuarter, &building, &adjMatrix, &orders, &orderedOrders);
            nOrderedOrders = nOrder;
            /* start config */
            returnAbility = 1; //mau ngecek return
            current_time = 0;
            current_money = 0;
            current_bagcapacity = 10;
            current_loc = '8'; /* always start at headQuarter */
            /* use char instead of POINT to ease referencing */
        }
        else if (isWordEqual(loadGameWord)){
            gameStart = true;
            LoadGame(&N, &M, &nLoc, &nOrder, &headQuarter, &building, &adjMatrix, &orders, &nOrderedOrders,
                    &orderedOrders, &current_loc, &current_time, &current_money, &current_bagcapacity,
                    &nToDoList, &toDoList, &nInProgress, &inProgress, &nInventory, &inventory,
                    &boostCount, &speedBoost, &bag, &efekVIP, &efekHeavyItem, &efekSenterPengecil);
        }
        else if (isWordEqual(exitWord)){
            return 0;
        }
        else {
            printf("Command Tidak VALID!\n\n");
            printf("COMMAND yang tersedia: \n");
            printf("NEW_GAME, LOAD_GAME, dan EXIT \n\n");
            printf("\nENTER COMMAND: ");
            startWordConsole();
            if(lenBefore > currentWord.length){
                for(int i = 0; i < lenBefore; i++){
                    if(i < currentWord.length){
                        command[i] = currentWord.contents[i];
                    }
                    else{
                        command[i] = '\0';
                    }
                }
            }
            else {
                for(int i = 0; i < currentWord.length; i++) {
                    command[i] = currentWord.contents[i];
                }
            }
            lenBefore = currentWord.length;
        }
    }
    Map = StartMapConfiguration(&N, &M, &headQuarter, &building, &adjMatrix);

    /* cek identitas Mobita */
    printf("\nJumlah order yang harus dikerjakan: %d\n", pqLength(orderedOrders));
    printf("Waktu: %d\n", current_time);

    /* attempt of making insert command, use strcmp for now */
    printf("\nENTER COMMAND: ");
    startWordConsole();
    if(lenBefore > currentWord.length)
        for(int i = 0; i < lenBefore; i++)
            if(i < currentWord.length)
                command[i] = currentWord.contents[i];
            else
                command[i] = '\0';
    else
        for(int i = 0; i < currentWord.length; i++)
            command[i] = currentWord.contents[i];
    lenBefore = currentWord.length;

    while (!isWordEqual(exitWord)) {
        updateToDoList(&toDoList, &orderedOrders, current_time, &efekVIP);
        //displayStack(bag);
        if (isWordEqual(moveWord)) {
            int deltaTime = current_time;
            move(Map, &current_loc, adjMatrix, building, headQuarter, &current_time, inProgress, &speedBoost, &boostCount, efekSenterPengecil);

            deltaTime = current_time - deltaTime;
            updatePerishable(&inProgress, deltaTime);
            removePerishable(&bag, &inProgress);
        }
        else if (isWordEqual(mapWord)) {
            displayColoredMap(Map, current_loc, adjMatrix, building, inProgress, toDoList);
        }
        else if (isWordEqual(toDoWord)) {
            printToDoList(&toDoList);
        }
        else if (isWordEqual(inProgressWord)) {
            printInProgress(&inProgress);
        }
        else if (isWordEqual(pickUpWord)) {
            pickUp(&toDoList, &inProgress, &bag, &current_loc, &current_bagcapacity, efekVIP, &efekHeavyItem, &speedBoost, &boostCount);
            if(efekHeavyItem){
                speedBoost = false;
            }
        }
        else if (isWordEqual(dropOffWord)) {
            dropOff(&toDoList, &inProgress, &bag, &current_loc, &efekVIP, &efekHeavyItem, &current_money, &current_bagcapacity, &speedBoost, &boostCount, &returnAbility, &ordersCount, &efekSenterPengecil);
        }
        else if (isWordEqual(buyWord)) {
            if (current_loc =='8') {
                buyGadget(&inventory, &current_money);
            }
            else {
                printf("Gadget hanya bisa dibeli saat berada di Headquarters");
            }
        }
        else if (isWordEqual(inventoryWord)) {
            displayInventory(&inventory, &current_bagcapacity, &current_loc, building, headQuarter, &inProgress, &bag, &current_time, &efekSenterPengecil);
        }
        else if (isWordEqual(bagWord)){
            displayStack(bag);
        }
        else if (isWordEqual(itemWord)){
            itemInfo();
        }
        else if (isWordEqual(gadgetWord)){
            gadgetInfo();
        }
        else if (isWordEqual(activeAbilityWord)){
            if (speedBoost){
                printf("Ability Speed Boost aktif (%d lokasi)\n", boostCount);
            } else {
                printf("Tidak ada Ability yang aktif\n");
            }
        }
        else if (isWordEqual(helpWord)) {
            Help();
        }
        else if (isWordEqual(returnWord)){
            returnToSender(&toDoList, &inProgress, &bag, &returnAbility, &efekSenterPengecil);
        }
        else if (isWordEqual(cheatCode)){
            printf("you.. cheater..\n");
            current_money += 99999;
            returnAbility += 99;
        }
        else {
            printf("COMMAND salah. Ketik 'HELP' untuk bantuan atau ketik ulang COMMAND.\n");
        }

        gameOn = endGame(current_loc, current_time, toDoList, inProgress, bag, orderedOrders);

        if (!gameOn){
            printf("Selamat anda telah menyelesaikan permainan mobita dengan mengantarkan %d jumlah pesanan dalam %d satuan waktu!\n\n", ordersCount, current_time);
            break;
        }

        /* cek identitas Mobita */
        printf("\nWaktu: %d\n", current_time);

        printf("\nENTER COMMAND: ");
        startWordConsole();
        if(lenBefore > currentWord.length)
            for(int i = 0; i < lenBefore; i++)
                if(i < currentWord.length)
                    command[i] = currentWord.contents[i];
                else
                    command[i] = '\0';
        else
            for(int i = 0; i < currentWord.length; i++)
                command[i] = currentWord.contents[i];
        lenBefore = currentWord.length;
    }

    gameSave = false;
    printf("\nApakah game ingin disave (Y atau N)?");
    startWordConsole();
    if(lenBefore > currentWord.length)
        for(int i = 0; i < lenBefore; i++)
            if(i < currentWord.length)
                command[i] = currentWord.contents[i];
            else
                command[i] = '\0';
    else
        for(int i = 0; i < currentWord.length; i++)
            command[i] = currentWord.contents[i];
    lenBefore = currentWord.length;
    while(!gameSave){
        if (isWordEqual(YWord) || isWordEqual(yWord)){
            gameSave=true;
            nOrder = lengthLinkedList(orders);
            nOrderedOrders = pqLength(orderedOrders);
            nToDoList = lengthLinkedList(toDoList);
            nInProgress = lengthLinkedList(inProgress);
            nInventory = length_ListPos(inventory);
            /*
            printf("%d %d\n", N, M);
            printf("%d\n", nLoc);
            printf("%d\n", nOrder);
            TulisPOINT(headQuarter);
            printf("\n");
            displayList(building);
            printf("\n");
            displayMatrix(adjMatrix);
            printf("\n");
            displayLinkedList(orders);
            printf("\n");
            //prioqueue orderedorders
            printf("%c\n", current_loc);
            printf("%d\n", current_time);
            printf("%d\n", current_money);
            printf("%d\n", current_bagcapacity);
            printf("%d\n", nToDoList);
            displayLinkedList(toDoList);
            printf("\n");
            printf("%d\n", nInProgress);
            displayLinkedList(inProgress);
            printf("\n");
            printf("%d\n", nInventory);
            displayList_ListPos(inventory);
            printf("%d\n", boostCount);
            printf("%c\n", speedBoost);
            displayStack(bag);
            printf("%c\n", efekVIP);
            printf("%c\n", efekHeavyItem);
            */
            SaveGame(N, M, nLoc, nOrder, headQuarter, building, adjMatrix, orders, nOrderedOrders, orderedOrders, current_loc, current_time, current_money,
                    current_bagcapacity, nToDoList, toDoList, nInProgress, inProgress, nInventory, inventory,
                    boostCount, speedBoost, bag, efekVIP, efekHeavyItem, efekSenterPengecil);
        } else if (isWordEqual(NWord) || isWordEqual(nWord)){
            gameSave = true;
            printf("\nTerima kasih telah bermain ^_^)b\n");
        } else {
            printf("Command tidak VALID!\n");
            printf("\nApakah game ingin disave (Y atau N)?");
            startWordConsole();
            if(lenBefore > currentWord.length)
                for(int i = 0; i < lenBefore; i++)
                    if(i < currentWord.length)
                        command[i] = currentWord.contents[i];
                    else
                        command[i] = '\0';
            else
                for(int i = 0; i < currentWord.length; i++)
                    command[i] = currentWord.contents[i];
            lenBefore = currentWord.length;
        }

    }
    closeTape();

    return 0;
}
