/* File: node.c */
/* Implementasi Node */

#include "node.h"
#include <stdlib.h>

Address newNode(Elements val) {
    Address p = (Address) malloc(sizeof(Node));
    if (p!=NULL) {
        NTIME(INFO(p)) = NTIME(val);
        PICKUP(INFO(p)) = PICKUP(val);
        DROPOFF(INFO(p)) = DROPOFF(val);
        ITEMTYPE(INFO(p)) = ITEMTYPE(val);
        PERISH(INFO(p)) = PERISH(val);
        NEXT(p) = NULL;
    }
    return p;
}

