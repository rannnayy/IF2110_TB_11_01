/*
    NIM             : 13520019
    Nama            : Maharani Ayu Putri Irawan
    Tanggal         : 25/10/2021
    Topik praktikum : ADT Linked List
    Deskripsi       : Membuat implementasi ADT Linked List representasi Address dengan pointer
*/

#include <stdio.h>
#include <stdlib.h>
#include "list_linked.h"

/* Definisi List : */
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    FIRST(*l) = NULL;
}

/****************** TEST LIST KOSONG ******************/
boolean isLinkedListEmpty(List l)
/* Mengirim true jika list kosong */
{
    return (FIRST(l) == NULL);
}

/****************** GETTER SETTER ******************/
Elements getLinkedListElmt(List l, int idx)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
{
    int i;
    Address p;

    i = 0;
    p = FIRST(l);
    while (i < idx){
        p = NEXT(p);
        i += 1;
    }

    return INFO(p);
}
void setLinkedListElmt(List *l, int idx, Elements val)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
{
    int i;
    Address p;

    i = 0;
    p = FIRST(*l);
    while (i < idx){
        p = NEXT(p);
        i += 1;
    }
    INFO(p) = val;
}
int indexOfLinkedList(List l, Elements val)
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */
{
    int i, ret;
    Address p;

    p = FIRST(l);
    ret = IDX_UNDEF;
    if(!isLinkedListEmpty(l)){
        i = 0;
        while(NTIME(INFO(p)) != NTIME(val)
              && PICKUP(INFO(p)) != PICKUP(val)
              && DROPOFF(INFO(p)) != DROPOFF(val)
              && ITEMTYPE(INFO(p)) != ITEMTYPE(val)
              && PERISH(INFO(p)) != PERISH(val)
              && NEXT(p) != NULL){
            i += 1;
            p = NEXT(p);
        }
        if(NTIME(INFO(p)) == NTIME(val)
              && PICKUP(INFO(p)) == PICKUP(val)
              && DROPOFF(INFO(p)) == DROPOFF(val)
              && ITEMTYPE(INFO(p)) == ITEMTYPE(val)
              && PERISH(INFO(p)) == PERISH(val))
            ret = i;
    }

    return ret;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertLinkedListFirst(List *l, Elements val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
{
    Address el;

    el = newNode(val);

    if(el != NULL){
        if(!isLinkedListEmpty(*l))
            NEXT(el) = FIRST(*l);
        FIRST(*l) = el;
    }
}
void insertLinkedListLast(List *l, Elements val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if(isLinkedListEmpty(*l))
        insertLinkedListFirst(&(*l), val);
    else{
        Address el;
        Address p;

        el = newNode(val);
        if(el != NULL){
            p = FIRST(*l);
            while(NEXT(p) != NULL){
                p = NEXT(p);
            }
            NEXT(p) = el;
        }
    }
}
void insertLinkedListAt(List *l, Elements val, int idx)
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if(idx == 0)
        insertLinkedListFirst(&(*l), val);
    else{
        int i;
        Address p, el;

        el = newNode(val);
        if(el != NULL){
            i = 0;
            p = FIRST(*l);
            while(i < idx-1){
                i += 1;
                p = NEXT(p);
            }
            NEXT(el) = NEXT(p);
            NEXT(p) = el;
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteLinkedListFirst(List *l, Elements *val)
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
{
    Address p;

    p = FIRST(*l);
    *val = INFO(p);
    if(NEXT(p) == NULL) // elemennya cuma 1
        FIRST(*l) = NULL;
    else
        FIRST(*l) = NEXT(p);
    free(p);
}
void deleteLinkedListLast(List *l, Elements *val)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */
{
    Address p, el;

    p = FIRST(*l);
    if(NEXT(p) == NULL) // elemennya cuma 1
        deleteLinkedListFirst(&(*l), &(*val));
    else{
        el = NULL;
        while(NEXT(p) != NULL){
            el = p;
            p = NEXT(p);
        }
        NEXT(el) = NULL;
        *val = INFO(p);
        free(p);
    }
}
void deleteLinkedListAt(List *l, int idx, Elements *val)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
{
    if(idx == 0)
        deleteLinkedListFirst(&(*l), &(*val));
    else{
        Address p, el;
        int i;

        i = 0;
        el = FIRST(*l);
        while(i < idx-1){
            i += 1;
            el = NEXT(el);
        }
        p = NEXT(el);
        *val = INFO(p);
        NEXT(el) = NEXT(p);
        free(p);
    }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayLinkedList(List l)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    if(FIRST(l) == NULL)
        printf("[]");
    else{
        Address p;

        p = FIRST(l);
        printf("[");
        while(NEXT(p) != NULL){
            printf("%d>%c>%c>%c>%d, ", NTIME(INFO(p)), PICKUP(INFO(p)), DROPOFF(INFO(p)), ITEMTYPE(INFO(p)), PERISH(INFO(p)));
            p = NEXT(p);
        }
        printf("%d>%c>%c>%c>%d]", NTIME(INFO(p)), PICKUP(INFO(p)), DROPOFF(INFO(p)), ITEMTYPE(INFO(p)), PERISH(INFO(p)));
    }
}
int lengthLinkedList(List l)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    if(isEmpty(l))
        return 0;
    else{
        int i;
        Address p;

        i = 0;
        p = FIRST(l);
        while(NEXT(p) != NULL){
            i += 1;
            p = NEXT(p);
        }
        return (i+1);
    }
}

/****************** PROSES TERHADAP LIST ******************/
List concatLinkedList(List l1, List l2)
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
    List l3;
    Address p;

    CreateList(&l3);
    p = FIRST(l1);
    while(p != NULL){
        insertLinkedListLast(&l3, INFO(p));
        p = NEXT(p);
    }
    p = FIRST(l2);
    while(p != NULL){
        insertLast(&l3, INFO(p));
        p = NEXT(p);
    }

    return l3;
}
