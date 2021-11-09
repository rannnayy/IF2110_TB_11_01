/* File: gadget.c */
/* Berisi prosedur dan fungsi yang digunakan untuk gadget*/

#include <stdio.h>
#include "gadget.h"

void addGadget(ListPos *inventory, int gadget){
// Menambahkan Gadget ke dalam Inventory
// I.S. inventory dan gadget terdefinisi
// F.S. inventory berisi gadget
    boolean added=false;
    int i=0;
    while(!added) {
        if (ELMT_LISTPOS(*inventory,i)==VAL_UNDEF_LISTPOS) {
            ELMT_LISTPOS(*inventory,i)=gadget;
            added=true;
        }
        else {
            i++;
        }
    }
}

void delGadget(ListPos *inventory, int idx) {
// menghapus gadget pada index idx dalam inventory
// I.S. inventory dan gadget terdefinisi
// F.S. gadget dihapus dari inventory
    ELMT_LISTPOS(*inventory,idx)=VAL_UNDEF_LISTPOS;
}

void displayInventory(ListPos inventory) {
// memperlihatkan semua gadget yang ada di dalam inventory dan dapat menggunakannya
// I.S. inventory terdefinisi
// F.S. gadget yang ada di dalam inventory diperlihatkan 
    int option, gadget,idx;
    for (idx=0;idx<CAPACITY_LISTPOS;idx++) {
        printf("%d. ", idx+1);
        if (ELMT_LISTPOS(inventory, idx)==1) {
            printf("Kain Pembungkus Waktu\n");
        }
        else if (ELMT_LISTPOS(inventory, idx)==2) {
            printf("Senter Pembesar\n");
        }
        else if (ELMT_LISTPOS(inventory, idx)==3) {
            printf("Pintu Kemana Saja\n");
        }
        else if (ELMT_LISTPOS(inventory,idx)==4) {
            printf("Mesin Waktu\n");
        }
        else if (ELMT_LISTPOS(inventory,idx)==5) {
            printf("Senter Pengecil\n");
        }
        else { //ELMT_LISTPOS(inventory, i)==VAL_UNDEF_LISTPOS
            printf("-\n");
        }
    }
    printf("Gadget mana yang ingin digunakan? (ketik 0 jika ingin kembali)\n");
    boolean exist=false; // exist true jika gadget yang dipilih ada pada inventory atau tidak jadi menggunakan gadget
    do {
        scanf("%d", &option);
        if (option>=0 && option<=5) {
            if (option==0) {
                exist=true;
            }
            else { // option>0 && option<=5
                if (ELMT_LISTPOS(inventory,option-1)==VAL_UNDEF_LISTPOS) {
                    printf("Gadget yang dipilih tidak ada\n");
                }
                else { //gadget ada di inventory
                    exist=true;
                }
            }
        }
        else { //option<0 || option>5
            printf("Masukkan anda salah, masukkan angka yang tertera pada list\n");
        }
    } while(!exist);
    if (option!=0) {
        idx=option-1;
        gadget=ELMT_LISTPOS(inventory,idx);
        useGadget(inventory, idx);
            switch(gadget){
                case 1 :
                    printf("Kain Pembungkus Waktu ");
                    break;
                case 2 :
                    printf("Senter Pembesar ");
                    break;
                case 3 :
                    printf("Pintu Kemana Saja ");
                    break;
                case 4 :
                    printf("Mesin Waktu ");
                    break;
                case 5 :
                    printf("Senter Pengecil ");
                    break;
                default :
                    printf("Unknown Gadget ");
            printf("berhasil digunakan!\n");
            }
        }
}

void buyGadget(ListPos inventory){
// membeli gadget dan memasukkannya ke dalam tas
// I.S. inventory dan gadget terdefinisi
// F.S. lsit gadget diperlihatkan dan gadget dibeli atau tidak jadi dibeli
    int option, gadget;
    printf("Gadget yang tersedia:\n");
    printf("1. Kain Pembungkus Waktu (800 Yen)\n");
    printf("2. Senter Pembesar (1200 Yen)\n");
    printf("3. Pintu Kemana Saja (1500 Yen)\n");
    printf("4. Mesin Waktu (3000 Yen)\n");
    printf("5. Senter Pengecil (800 Yen)\n");
    printf("Gadget mana yang ingin kau beli? (ketik 0 jika ingin kembali)\n");
    printf("Enter Command: ");
    scanf("%d", &option);
    while(option<0 || option>5) {
        printf("Masukkan anda salah, masukkan angka yang tertera pada list\n");
        scanf("%d", &option);
    }
    if (option!=0) {
        gadget=option;
        if (isFull_ListPos(inventory)) {
            printf("Kapasitas inventory anda penuh!\n");
        }
        else { // inventory tidak full
            addGadget(&inventory, gadget);
            switch(gadget){
                case 1 :
                    printf("Kain Pembungkus Waktu ");
                    break;
                case 2 :
                    printf("Senter Pembesar ");
                    break;
                case 3 :
                    printf("Pintu Kemana Saja ");
                    break;
                case 4 :
                    printf("Mesin Waktu ");
                    break;
                case 5 :
                    printf("Senter Pengecil ");
                    break;
                default :
                    printf("Unkonwn Gadget ");
            }
            printf("berhasil dibeli!\n");
        }
    }
}
void useGadget(ListPos inventory, int idx){
// mmenggunakan gadget pada index idx inventory dan mendapatkan kemampuan spesial dari gadget yang digunakan
// I.S. inventory dan gadget terdefinisi
// F.S. gadget digunakan kemudian hangus atau di hapus dalam inventory.
 delGadget(&inventory,idx);
}