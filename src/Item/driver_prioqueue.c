#include <stdio.h>
#include "prioqueue.h"
// #include "prioqueue.c"

int main() {
    PrioQueue pq;
    pqEls pqEls1, pqEls2, tempEls;

    // Inisialisasi PrioQueue
    CreatePrioQueue(&pq);

    // pq Seharusnya empty saat diinisialisasi
    if (pqIsEmpty(pq)){
        printf("pq kosong\n");
    } else {
        printf("pq tidak kosong\n");
    }

    // Buat elemen pq
    NTIME(pqEls1) = 2;
    PICKUP(pqEls1) = '8';
    DROPOFF(pqEls1) = 'Z';
    ITEMTYPE(pqEls1) = 'H';
    PERISH(pqEls1) = -1;

    // masukkan ke pq
    enqueue(&pq, pqEls1);

    // Cek length dari pq seharunsnya 1
    printf("Panjang dari pq adalah %d\n", pqLength(pq));

    // Cek apakah pq kapasitas maksimum
    if (pqIsFull(pq)){
        printf("Kapasitas dari pq sudah maksimum\n");
    } else {
        printf("Kapasitas pq belum maksimum\n");
    }

    // Buat elemen pq yang lain
    NTIME(pqEls2) = 1;
    PICKUP(pqEls2) = 'A';
    DROPOFF(pqEls2) = 'B';
    ITEMTYPE(pqEls2) = 'N';
    PERISH(pqEls2) = -1;
    
    // Enqueue pq, seharusnya pqEls2 akan menjadi indeks pertama
    enqueue(&pq, pqEls2);
    dequeue(&pq, &tempEls);

    printf("NTIME:%d\nPICKUP:%c\nDROPOFF:%c\nITEMTYPE:%c\nPERISH:%d\n", NTIME(tempEls), PICKUP(tempEls), DROPOFF(tempEls), ITEMTYPE(tempEls), PERISH(tempEls));

    // Cek length, seharusnya 1
    printf("Panjang dari pq sekarang adalah %d\n", pqLength(pq));

    return 0;
}

