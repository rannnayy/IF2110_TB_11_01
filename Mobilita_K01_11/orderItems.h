/* File: orderItems.h */
/* Tanggal: 29 Okt 2021 */

#ifndef ORDER_H
#define ORDER_H

#include "prioqueue.h"
#include "list_linked.h"

void queueOrder(PrioQueue *pq, List *li);
// queues order from the list of all orders (Linked list "orders") into the queue list (PrioQueue orderedOrders)

void printToDoList(List *li);
// prints the to do list linked list

void printInProgress(List *li);
// prints the in progress linked list

void updateToDoList(List *li, int time);
// updates to do list based on the current time;


#endif