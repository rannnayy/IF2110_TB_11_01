/*
    File Name   : orderItems.c
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
        else if (INFO(p).itemType == 'P') printf("Perishable  Item (Tujuan: %c, Waktu tersisa: %d)\n", INFO(p).dropOff, INFO(p).perish);
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
    while(NTIME(HEAD(*orderedOrders)) <= time && pqLength(*orderedOrders) > 0){      // kalo waktunya dibawah atau sama dengan waktu yg ditetapkan
        Elements temp;
        NTIME(temp) = NTIME(HEAD(*orderedOrders));
        DROPOFF(temp) = DROPOFF(HEAD(*orderedOrders));
        ITEMTYPE(temp) = ITEMTYPE(HEAD(*orderedOrders));
        PICKUP(temp) = PICKUP(HEAD(*orderedOrders));
        PERISH(temp) = PERISH(HEAD(*orderedOrders));

        // tambahin ke toDoList
        insertLinkedListLast(toDoList, temp);

        // set efek VIP ke true klo slh satu yg ditambahin VIP
        if (temp.itemType == 'V') *efekVIP = true;

        pqEls popped;       //buang elemennya
        dequeue(orderedOrders, &popped);
    }
}

void pickUp(List *toDoList, List *inProgress, Stack *bag, char *currentLoc, int *bagCapacity, boolean efekVIP, boolean *efekHeavyItem, boolean* speedBoost, int* countBoost)
// picks up a specific item if that item exists in the toDoList and moves it into the inProgress
// I.S. bebas
// F.S. item might be added to the inProgress list and to the bag stack
{
    Address p = *toDoList;
    Elements popped;
    int i = 0;
    boolean itemExists = false;
    *efekHeavyItem = false;

    if (lengthLinkedList(*inProgress) < *bagCapacity){      // kalo kapasitas tas cukup
        if (!efekVIP){                                               // Bila tidak ada efek VIP
            while (p != NULL && (!itemExists)){
                if (INFO(p).pickUp == *currentLoc){
                    deleteLinkedListAt(toDoList, i, &popped);
                    insertLinkedListFirst(inProgress, popped);
                    stackEl temp;
                    temp.dropOff = popped.dropOff;
                    temp.itemType = popped.itemType;
                    temp.nTime = popped.nTime;
                    temp.perish = popped.perish;
                    temp.pickUp = popped.pickUp;
                    push(bag, temp);
                    itemExists = true;
                    *bagCapacity++;
                    if (temp.itemType == 'H'){
                        *efekHeavyItem = true;
                        if(speedBoost){
                            *speedBoost = false;
                            *countBoost = 0;
                        }
                    }
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
                    stackEl temp;
                    temp.dropOff = popped.dropOff;
                    temp.itemType = popped.itemType;
                    temp.nTime = popped.nTime;
                    temp.perish = popped.perish;
                    temp.pickUp = popped.pickUp;
                    push(bag, temp);
                    itemExists = true;
                    *bagCapacity++;
                    if (temp.itemType == 'H') *efekHeavyItem = true;
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
                    printf("Unknown Type ");
            }
            printf("berhasil diambil!\n");
        }
    }
    else {
        printf("Kapasitas tas sudah penuh!\n");
    }
}

void dropOff(List *toDoList, List *inProgress, Stack *bag, char *currentLoc, boolean *efekVIP, boolean *efekHeavyItem, int* current_money, int* current_bagcapacity, boolean* speedBoost, int* boostCount, int *returnAbility)
// drops off an item from the top of the stack if the location of the player is the destination of the item
// I.S. bebas
// F.S top of the bag stack might be removed, as well as the item in inProgress list.
{
    if(TOP(*bag).dropOff == *currentLoc){
        // pop dari inProgress sm bag
        stackEl popped;
        Elements temp;
        pop(bag, &popped);
        deleteLinkedListFirst(inProgress, &temp);

        // set efek VIP ke false klo gk ada item VIP lagi di toDoList sama inProgress
        if (!hasVIP(toDoList) && !hasVIP(inProgress)) *efekVIP = false;
        if (!hasHeavyItem(inProgress)) *efekHeavyItem = false;

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
            if(*speedBoost == true){ // masih ada efek speedBoost, reset
                *boostCount = 0;
            }
            else{
                if(!hasHeavyItemStack(*bag)){
                    *speedBoost = true;
                    *boostCount = 0;
                }
            }
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
            printf("Mendapatkan ability Return To Sender.\n");
            *current_money = *current_money + 600;
            /* apply return to sender */
            *returnAbility = *returnAbility + 1;
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
        if(INFO(p).itemType == 'V') does = true;
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
        if (*bagCapacity > 100) {
            *bagCapacity = 100;
        }
    }
    else if (type == 'i'){
        *bagCapacity++;
    }

    if (*bagCapacity > 100) *bagCapacity = 100;
    if (*bagCapacity == 100) printf("Kapasitas tas sudah maksimum!\n");
}

void removePerishable(Stack *bag, List *inProgress)
// checks if the inProgress has a perishable item
//      if so, check if the time limit has exceeded
//          if so, remove it.
// check for all perishables.
{
    Address p = FIRST(*inProgress);
    int i = 0;
    Elements popped;
    while(p != NULL){
        if(INFO(p).itemType == 'P' && INFO(p).perish < 1){
            deleteLinkedListAt(inProgress, i, &popped);
            stackEl popThis;
            popThis.dropOff = popped.dropOff; popThis.perish = popped.perish;
            popThis.itemType = popped.itemType; popThis.nTime = popped.nTime;
            popThis.pickUp = popped.pickUp;
            popEl(bag, popThis);
            printf("\nAda perishable item yang sudah melewati time limitnya!\n");
        }
        else{
            i++;
        }
        p = NEXT(p);
    }

};

boolean hasHeavyItem(List *li)
// checks if the list has a heavy item, returns true if true
// use in the linked list in progress
{
    Address p = FIRST(*li);
    boolean does = false;
    while(p != NULL && (!does)){
        if(INFO(p).itemType == 'H') does = true;
        p = NEXT(p);
    }
    return does;
}

boolean hasHeavyItemStack(Stack li)
// checks if the list has a heavy item, returns true if true
// use in the linked list in progress
{
    stackEl temp;
    boolean does = false;

    while(!isStackEmpty(li) && (!does)){
        pop(&li, &temp);
        if(temp.itemType == 'H') does = true;
    }
    return does;
}

int countHeavyItem(List li) {
    /* KAMUS LOKAL */
    Address p;
    int count;

    /* ALGORITMA */
    p = li;
    count = 0;
    while (p!= NULL) {
        if (INFO(p).itemType == 'H') {
            count++;
        }
        p = NEXT(p);
    }
    return count;
}

void updatePerishable(List *inProgress, int deltaTime){
    Address p = FIRST(*inProgress);
    while(p != NULL){
        if (INFO(p).itemType == 'P'){
            INFO(p).perish -= deltaTime;
        }
        p = NEXT(p);
    }
}

void itemInfo(){
    /* I.S Sembarang */
    /* F.S.Output info dari item */
    printf("1. Normal Item\n");
    printf("    - Item ini tidak memiliki efek samping ketika di-pick up atau reward ability\n");
    printf("      tambahan ketika di-drop off.\n");
    printf("    - Item ini bernilai 200 Yen.\n");
    printf("2. Heavy Item\n");
    printf("    - Efek  : Setiap pindah 1 lokasi maka waktu akan bertambah 1 unit (1 + 1 = 2 unit).\n");
    printf("    - Reward: Mobita akan mendapatkan ability Speed Boost jika berhasil mengantarkan item ini.\n");
    printf("    - Item ini bernilai 400 Yen.\n");
    printf("3. Perishable Item\n");
    printf("    - Efek: Item harus diantarkan ke lokasi drop off dalam waktu yang ditentukan.\n");
    printf("      Jika waktu habis, maka item akan dikeluarkan secara otomatis dari tas, dan pesanan akan dihapus\n");
    printf("      secara otomatis dari In Progress List.\n");
    printf("    - Item ini berinilai 400 Yen.\n");
    printf("4. VIP Item\n");
    printf("    - Efek  : Efek ini aktif saat pesanan masuk ke To Do List. Pesanan dengan item ini\n");
    printf("      harus segera dilayani (Pick Up dan Drop Off), sehingga Mobita tidak bisa melakukan\n");
    printf("      Pick Up untuk item lain.\n");
    printf("    - Reward: Mobita akan mendapatkan ability Return To Sender jika berhasil mengantarkan item ini.\n");
    printf("    - Item ini bernilai 600 Yen.\n");
}
