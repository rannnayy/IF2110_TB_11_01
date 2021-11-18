#include "stack.h"
#include <stdio.h>

/* *** Konstruktor/Kreator *** */
void CreateStack(Stack *s){
    IDX_TOP(*s) = IDX_UNDEF;
};
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S kosong dengan kondisi sbb: */
/* - Index top bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah s kosong */

/* ************ Prototype ************ */
boolean isStackEmpty(Stack s){
    return IDX_TOP(s) == IDX_UNDEF;
};
/* Mengirim true jika s kosong: lihat definisi di atas */
boolean isStackFull(Stack s){
    return IDX_TOP(s) == (CAPACITY - 1);
};
/* Mengirim true jika tabel penampung nilai s stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void push(Stack *s, stackEl val){
    IDX_TOP(*s)++;
    TOP(*s) = val;
};
/* Menambahkan val sebagai elemen Stack s */
/* I.S. s mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. val menjadi TOP yang baru,IDX_TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void pop(Stack *s, stackEl *val){
    *val = TOP(*s);
    IDX_TOP(*s)--;
};
/* Menghapus val dari Stack s */
/* I.S. s tidak mungkin kosong */
/* F.S. val adalah nilai elemen TOP yang lama, IDX_TOP berkurang 1 */

void popEl(Stack *s, stackEl val){
    Stack temp;
    CreateStack(&temp);
    stackEl popped;

    while(!isStackEmpty(*s)){
        pop(s, &popped);
        if (popped.itemType != val.itemType && popped.dropOff != val.dropOff && popped.pickUp != val.pickUp){
            push(&temp, popped);
        }
    }
    while(!isStackEmpty(temp)){
        pop(&temp, &popped);
        push(s, popped);
    }
};
// Menghapus elemen val dalam stack
// I.S. ada elemen val dalam stack, tidak harus di posisi top
// F.S. elemen val hilang

void displayStack(Stack s)
{
    stackEl temp;
    int i = 1;
    
    if (isStackEmpty(s)){
        printf("Bag kosong. Silahkan lanjutkan permainan!\n");
    } else {
        while(!isStackEmpty(s)){
            pop(&s, &temp);
            printf("%d. ", i);
            printf("%c -> %c ", (temp).pickUp, (temp).dropOff);
            if ((temp).itemType == 'N') printf("(Normal Item)\n");
            else if ((temp).itemType == 'H') printf("(Heavy Item)\n");
            else if ((temp).itemType == 'P') printf("(Perishable Item, siswa waktu %d)\n", (temp).perish);
            else if ((temp).itemType == 'V') printf("(VIP Item)\n");
            i++;
        }
    }
}
/* Menampilkan stack */
/* I.S. sembarang, boleh kosong */
/* F.S. tampilkan stack */