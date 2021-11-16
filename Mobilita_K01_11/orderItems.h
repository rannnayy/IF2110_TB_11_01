/* File: orderItems.h */
/* Tanggal: 29 Okt 2021 */

#ifndef ORDER_H
#define ORDER_H

#include "prioqueue.h"
#include "list_linked.h"
#include "stack.h"
#include "boolean.h"

void queueOrder(PrioQueue *pq, List *li);
// queues order from the list of all orders (Linked list "orders") into the queue list (PrioQueue orderedOrders)
// I.S. prioQueue empty
// F.S. prioQueue filled with orders

void printToDoList(List *li);
// prints the to do list linked list
// I.S. bebas
// F.S. To do list gets printed

void printInProgress(List *li);
// prints the in progress linked list
// I.S. bebas
// F.S. In Progress gets printed

void updateToDoList(List *toDoList, PrioQueue *orderedOrders, int time, boolean *hasVIP);
// updates to do list based on the current time;
// I.S. to do list bebas
// F.S. to do list gets added with certain amount of tasks based on the queue and given time.

void pickUp(List *toDoList, List *inProgress, Stack *bag, char *currentLoc, int *bagCapacity, boolean efekVIP, boolean *efekHeavyItem);
// picks up a specific item if that item exists in the toDoList and moves it into the inProgress
// I.S. bebas
// F.S. item might be added to the inProgress list and to the bag stack

void dropOff(List *toDoList, List *inProgress, Stack *bag, char *currentLoc, boolean *efekVIP, boolean *efekHeavy, int* current_money, int* current_bagcapacity, int* time_inc, boolean* speedBoost, int *returnAbility);
// drops off an item from the top of the stack if the location of the player is the destination of the item
// I.S. bebas
// F.S top of the bag stack might be removed, as well as the item in inProgress list.

boolean hasVIP(List *li);
// checks if the list has a VIP item, returns true if true

void increaseBagCapacity(int *bagCapacity, char type);
// increases bag capacity (?)
// type 'd' for double; type 'i' for increment
// I.S. kapasitas bag ada
// F.S. kapasitas bag ditambahkan (dengan cara ditentukan)

void removePerishable(Stack *bag, List *inProgress, int time);
// checks if the inProgress has a perishable item
//      if so, check if the time limit has exceeded
//          if so, remove it.
// check for all perishables.
// I.S mungkin punya perishable
// F.S. perishable dgn waktu perish <= waktu skrg, bakal dihilangkan.

boolean hasHeavyItem(List *li);
// checks if the list has a heavy item, returns true if true

int countHeavyItem(List li);

void returnToSender(List *toDoList, List *inProgress, Stack *bag, int *returnAbility);
// provides the effect "Return to Sender"
// does not check if the user has the gadget necessary to use it.
// returnAbility is the amount of return to sender the player has
// I.S. bebas
// F.S. item teratas di tas akan dikembalikan apabila ada ability return to sender dan item bukan item VIP

void updatePerishable(List *inProgress);
// updates the perishable in the inProgress list by 1 (needs to be caled everytime MOVE is called)
// karena yg diupdate cuman di in progress list, yg di bag info perish akan tetap, apabila perlu diset ulang pakai info dari bag.
// I.S. bebas
// F.S. semua item perishable dalam in progress list akan berkurang waktu perish sebesar 1

void kainPembungkusWaktu(List *inProgress, Stack *bag, int *kainPembungkusWaktuGadget);
// gadget kainPembungkusWaktu
// memakai info dari bag, reset time perish
// I.S. bebas
// F.S. apabila gadget teratas tas merupakan perishable, reset timer perishable di in progress

void itemInfo();
#endif
