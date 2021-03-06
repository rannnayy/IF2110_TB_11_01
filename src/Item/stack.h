/* File : stack.h */
/* Definisi ADT Stack dengan representasi array secara eksplisit dan alokasi statik */
/* TOP adalah alamat elemen puncak */

#ifndef STACK_H
#define STACK_H

#include "../boolean.h"

#define IDX_UNDEF -1
#define CAPACITY 100

typedef struct {
    int nTime;
    char pickUp;
    char dropOff;
    char itemType;
    int perish;
}  stackEl;

typedef struct {
  stackEl buffer[CAPACITY]; /* tabel penyimpan elemen */
  int idxTop;              /* alamat TOP: elemen puncak */
} Stack;

/* ********* AKSES (Selektor) ********* */
/* Jika s adalah Stack, maka akses elemen : */
#define IDX_TOP(s) (s).idxTop
#define     TOP(s) (s).buffer[(s).idxTop]

#define NTIME(e) (e).nTime
#define PICKUP(e) (e).pickUp
#define DROPOFF(e) (e).dropOff
#define ITEMTYPE(e) (e).itemType
#define PERISH(e) (e).perish

/* *** Konstruktor/Kreator *** */
void CreateStack(Stack *s);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S kosong dengan kondisi sbb: */
/* - Index top bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah s kosong */

/* ************ Prototype ************ */
boolean isStackEmpty(Stack s);
/* Mengirim true jika s kosong: lihat definisi di atas */
boolean isStackFull(Stack s);
/* Mengirim true jika tabel penampung nilai s stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void push(Stack *s, stackEl val);
/* Menambahkan val sebagai elemen Stack s */
/* I.S. s mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. val menjadi TOP yang baru,IDX_TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void pop(Stack *s, stackEl *val);
/* Menghapus val dari Stack s */
/* I.S. s tidak mungkin kosong */
/* F.S. val adalah nilai elemen TOP yang lama, IDX_TOP berkurang 1 */

/* Menghapus elemen spesifik dalam stack */
void popEl(Stack *s, stackEl val);
// Menghapus elemen val dalam stack
// I.S. ada elemen val dalam stack, tidak harus di posisi top
// F.S. elemen val hilang

void displayStack(Stack s);
/* Menampilkan stack */
/* I.S. sembarang, boleh kosong */
/* F.S. tampilkan stack */

#endif
