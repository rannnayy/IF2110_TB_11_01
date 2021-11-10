/*
    File Name   : 
    Author      : K01_11
    Last Update : 28/10/2021
    Description : contains all the procedures and functions for to do list and in progress.
*/

#include <stdio.h>
#include <stdlib.h>
#include "orderItems.h"

void queueOrder(PrioQueue *pq, List *li)
// queues order from the list of all orders (Linked list "orders") into the queue list (PrioQueue orderedOrders)
{
    Address p = *li;
    pqEls temp;
    while(p != NULL){
        temp.dropOff = INFO(p).dropOff;
        temp.itemType = INFO(p).itemType;
        temp.nTime = INFO(p).nTime;
        temp.perish = INFO(p).perish;
        temp.pickUp = INFO(p).pickUp;
        enqueue(pq, temp);
        p = NEXT(p);
    }
}

void printInProgress(List *li)
// prints the in progress linked list
// the list is a "stack" with the top of the stack as the first info from the linked list
// insert new items with insertFirst()
{   
    Address p = *li;
    int i = 1;
    printf("Pesanan yang sedang diantarkan:\n");
    while (p != NULL){
        printf("%d. ", i);
        if (INFO(p).itemType == 'N') printf("Normal  Item (Tujuan: %c)\n", INFO(p).dropOff);
        else if (INFO(p).itemType == 'H') printf("Heavy  Item (Tujuan: %c)\n", INFO(p).dropOff);
        else if (INFO(p).itemType == 'P') printf("Perishable  Item (Tujuan: %c)\n", INFO(p).dropOff);
        else if (INFO(p).itemType == 'V') printf("VIP  Item (Tujuan: %c)\n", INFO(p).dropOff);
        p = NEXT(p);
        i++;
    }
}

void printToDoList(List *li)
// prints the to do list linked list
// the to do list is a list.
// insert new items with insertLast()
{
    Address p = *li;
    int i = 1;
    printf("Pesanan pada To Do List:\n");
    while (p != NULL){
        printf("%d. ", i);
        printf("%c -> %c ", INFO(p).pickUp, INFO(p).dropOff);
        if (INFO(p).itemType == 'N') printf("(Normal Item)\n");
        else if (INFO(p).itemType == 'H') printf("(Heavy Item)\n");
        else if (INFO(p).itemType == 'P') printf("(Perishable Item, siswa waktu %d)\n", INFO(p).perish);
        else if (INFO(p).itemType == 'V') printf("(VIP Item)\n");
        p = NEXT(p);
        i++;
    }
}

void updateToDoList(List *toDoList, PrioQueue *orderedOrders, int time, boolean *efekVIP)
// updates to do list based on the current time;
{
    while(HEAD(*orderedOrders).nTime <= time){      // kalo waktunya dibawah atau sama dengan waktu yg ditetapkan
        Elements temp;
        temp.nTime = HEAD(*orderedOrders).nTime;
        temp.dropOff = HEAD(*orderedOrders).dropOff;
        temp.itemType = HEAD(*orderedOrders).itemType;
        temp.pickUp = HEAD(*orderedOrders).pickUp;
        temp.perish = HEAD(*orderedOrders).perish;

        // tambahin ke toDoList
        insertLinkedListLast(toDoList, temp);

        // set efek VIP ke true klo slh satu yg ditambahin VIP
        if (temp.itemType == 'V') *efekVIP = true;

        pqEls popped;       //buang elemennya
        dequeue(orderedOrders, &popped);
    }
}

void pickUp(List *toDoList, List *inProgress, Stack *bag, char *currentLoc, int *bagCapacity, boolean efekVIP)
// picks up a specific item if that item exists in the toDoList and moves it into the inProgress
// I.S. bebas
// F.S. item might be added to the inProgress list and to the bag stack
{
    Address p = *toDoList;
    Elements popped;
    int i = 0;
    boolean itemExists = false;
    if (lengthLinkedList(*inProgress) < *bagCapacity){      // kalo kapasitas tas cukup
        if (!efekVIP){                                               // Bila tidak ada efek VIP
            while (p != NULL && (!itemExists)){
                if (INFO(p).pickUp == *currentLoc){
                    deleteLinkedListAt(toDoList, i, &popped);
                    insertLinkedListFirst(inProgress, popped);
                    ElType temp;
                    temp.dropOff = popped.dropOff;
                    temp.itemType = popped.itemType;
                    temp.nTime = popped.nTime;
                    temp.perish = popped.perish;
                    temp.pickUp = popped.pickUp;
                    push(bag, temp);
                    itemExists = true;
                    *bagCapacity++;
                }
                else {
                    i++;
                    p = NEXT(p);
                }
            }
        }
        else {                                                                  // bila ada efek VIP
            while (p != NULL && (!itemExists)){
                if (INFO(p).pickUp == *currentLoc && INFO(p).itemType == 'V'){
                    deleteLinkedListAt(toDoList, i, &popped);
                    insertLinkedListFirst(inProgress, popped);
                    ElType temp;
                    temp.dropOff = popped.dropOff;
                    temp.itemType = popped.itemType;
                    temp.nTime = popped.nTime;
                    temp.perish = popped.perish;
                    temp.pickUp = popped.pickUp;
                    push(bag, temp);
                    itemExists = true;
                    *bagCapacity++;
                }
                else {
                    i++;
                    p = NEXT(p);
                }
            }            
        }   


        if (!itemExists){
            printf("Pesanan tidak ditemukan!\n");
        }
        else {
            printf("Pesanan berupa ");
            switch(TOP(*bag).itemType){
                case 'N' :
                    printf("Normal Item ");
                    break;
                case 'H' :
                    printf("Heavy Item ");
                    break;
                case 'P' :
                    printf("Perishable Item ");
                    break;
                case 'V' :
                    printf("VIP Item ");
                    break;
                default :
                    printf("Unkonwn Type ");
            }
            printf("berhasil diambil!\n");
        }
    }
    else {
        printf("Kapasitas tas sudah penuh!\n");
    }
}

void dropOff(List *toDoList, List *inProgress, Stack *bag, char *currentLoc, boolean *efekVIP, int* current_money, int* current_bagcapacity, int* time_inc)
// drops off an item from the top of the stack if the location of the player is the destination of the item
// I.S. bebas
// F.S top of the bag stack might be removed, as well as the item in inProgress list.
{
    if(TOP(*bag).dropOff == *currentLoc){
        // pop dari inProgress sm bag
        ElType popped;
        Elements temp;
        pop(bag, &popped);
        deleteLinkedListFirst(inProgress, &temp);
        
        // set efek VIP ke false klo gk ada item VIP lagi di toDoList sama inProgress
        if (!hasVIP(toDoList) && !hasVIP(inProgress)) *efekVIP = false;

        // trus tambahin poin (blm diimplementasi poinnya)

        /* write confirmation message and apply item effects */
        if (popped.itemType == 'N') {
            printf("Pesanan Normal Item berhasil diantarkan.\n");
            printf("Uang yang didapatkan: 200 Yen.\n");
            *current_money = *current_money + 200;
        }
        else if (popped.itemType == 'H') {
            printf("Pesanan Heavy Item berhasil diantarkan.\n");
            printf("Uang yang didapatkan: 400 Yen.\n");
            *current_money = *current_money + 400;
            /* apply speed boost */
        }
        else if (popped.itemType == 'P') {
            printf("Pesanan Perishable Item berhasil diantarkan.\n");
            printf("Uang yang didapatkan: 400 Yen.\n");
            *current_money = *current_money + 400;
            increaseBagCapacity(current_bagcapacity, 'i');
        }
        else { /* popped.itemType == 'V' */
            printf("Pesanan VIP Item berhasil diantarkan.\n");
            printf("Uang yang didapatkan: 600 Yen.\n");
            *current_money = *current_money + 600;
            /* apply return to sender */
        }
    }
    else { /* current loc isn't drop-off location */
        printf("Tidak ada pesanan yang dapat diantarkan.\n");
    }
}

boolean hasVIP(List *li)
// checks if the list has a VIP item, returns true if true
{
    Address p = *li;
    boolean does = false;
    while(p != NULL && (!does)){
        if(INFO(p).itemType = 'V') does = true;
        p = NEXT(p);
    }
    return does;
}

void increaseBagCapacity(int *bagCapacity, char type)
// increases bag capacity (?)
// type 'd' for double; type 'i' for increment 
{
    if (type == 'd'){
        *bagCapacity *= 2;
    }
    else if (type == 'i'){
        *bagCapacity++;
    }

    if (*bagCapacity > 100) *bagCapacity = 100;
    if (*bagCapacity == 100) printf("Kapasitas tas sudah maksimum!\n");
}

void removePerishable(Stack *bag, List *inProgress, int time)
// checks if the inProgress has a perishable item
//      if so, check if the time limit has exceeded
//          if so, remove it.
// check for all perishables.
{
    Address p = *inProgress;
    int i = 0;
    Elements popped;
    while(p != NULL){
        if(INFO(p).itemType = 'P' && INFO(p).perish + INFO(p).nTime <= time){
            deleteLinkedListAt(inProgress, i, &popped);
            boolean found = false;
            ElType popThis;
            popThis.dropOff = popped.dropOff; popThis.perish = popped.perish; 
            popThis.itemType = popped.itemType; popThis.nTime = popped.nTime;
            popThis.pickUp = popped.pickUp;
            popEl(bag, popThis);
            printf("Ada perishable item yang sudah melewati time limitnya!\n");
        }
        else{
            i++;
            p = NEXT(p);
        }
    }
};
