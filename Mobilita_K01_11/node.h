#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

typedef struct elements{
    int nTime;
    char pickUp;
    char dropOff;
    char itemType;
    int perish;
} Elements;
typedef struct node* Address;
typedef struct node {
    Elements info;
    Address next;
} Node;

#define INFO(p) (p)->info
#define NTIME(e) (e).nTime
#define PICKUP(e) (e).pickUp
#define DROPOFF(e) (e).dropOff
#define ITEMTYPE(e) (e).itemType
#define PERISH(e) (e).perish
#define NEXT(p) (p)->next

Address newNode(Elements val);


#endif
