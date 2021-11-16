/* File: gadget.c */
/* Berisi prosedur dan fungsi yang digunakan untuk gadget*/

#include <stdio.h>
#include "gadget.h"

void addGadget(ListPos *inventory, int gadget){
// Menambahkan Gadget ke dalam Inventory
// I.S. inventory dan gadget terdefinisi
// F.S. gadget ditambahkan ke inventory
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

void displayInventory(ListPos *inventory, int *current_bagcapacity, MAP Map, char* current_loc, Matrix adjMatrix, ListDin building, POINT headQuarter, List *inProgress, Stack *bag, int* current_time, boolean *efekHeavyItem, boolean* speedBoost, int* boostCount) {
// memperlihatkan semua gadget yang ada di dalam inventory dan dapat menggunakannya
// I.S. inventory terdefinisi
// F.S. gadget yang ada di dalam inventory diperlihatkan
    int option, gadget,idx;

    for (idx=0;idx<CAPACITY_LISTPOS;idx++) {
        printf("%d. ", idx+1);
        if (ELMT_LISTPOS(*inventory, idx)==1) {
            printf("Kain Pembungkus Waktu\n");
        }
        else if (ELMT_LISTPOS(*inventory, idx)==2) {
            printf("Senter Pembesar\n");
        }
        else if (ELMT_LISTPOS(*inventory, idx)==3) {
            printf("Pintu Kemana Saja\n");
        }
        else if (ELMT_LISTPOS(*inventory,idx)==4) {
            printf("Mesin Waktu\n");
        }
        else if (ELMT_LISTPOS(*inventory,idx)==5) {
            printf("Senter Pengecil\n");
        }
        else { //ELMT_LISTPOS(inventory, i)==VAL_UNDEF_LISTPOS
            printf("-\n");
        }
    }
    printf("Gadget mana yang ingin digunakan? (ketik 0 jika ingin kembali)\n");
    boolean exist=false; // exist true jika gadget yang dipilih ada pada inventory atau tidak jadi menggunakan gadget
    do {
        option=0;
        startWordConsole();
        DigitsToInt(currentWord, &option);
        if (option>=0 && option<=5) {
            if (option==0) {
                exist=true;
            }
            else { // option>0 && option<=5
                if (ELMT_LISTPOS(*inventory,option-1)==VAL_UNDEF_LISTPOS) {
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
        gadget=ELMT_LISTPOS(*inventory,idx);
        useGadget(inventory, idx, current_bagcapacity, Map, current_loc, adjMatrix, building, headQuarter, inProgress, bag, current_time, efekHeavyItem, speedBoost, boostCount);
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
            }
            printf("berhasil digunakan!\n");
        }
}

void buyGadget(ListPos *inventory, int *current_money){
// membeli gadget dan memasukkannya ke dalam tas
// I.S. inventory dan gadget terdefinisi
// F.S. lsit gadget diperlihatkan dan gadget dibeli atau tidak jadi dibeli
    int option, gadget;

    boolean succeed = false;
    printf("Uang Anda sekarang: %d\n", *current_money);
    printf("Gadget yang tersedia:\n");
    printf("1. Kain Pembungkus Waktu (800 Yen)\n");
    printf("2. Senter Pembesar (1200 Yen)\n");
    printf("3. Pintu Kemana Saja (1500 Yen)\n");
    printf("4. Mesin Waktu (3000 Yen)\n");
    printf("5. Senter Pengecil (800 Yen)\n");
    printf("Gadget mana yang ingin kau beli? (ketik 0 jika ingin kembali)\n");
    printf("Enter Command: ");
    scanf("%d", &option);
    do {
        option=0;
        startWordConsole();
        DigitsToInt(currentWord, &option);
        if (option<0 || option>5) {
            printf("Masukkan anda salah, masukkan angka yang tertera pada list\n");
        }
    }while(option<0 || option>5);
    if (option!=0) {
        gadget=option;
        if (isFull_ListPos(*inventory)) {
            printf("Kapasitas inventory Anda penuh!\n");
        }
        else { // inventory tidak full
            switch(gadget){
                case 1 :
                    if (*current_money >= 800) {
                        printf("Kain Pembungkus Waktu berhasil dibeli.\n");
                        *current_money = *current_money - 800;
                        succeed = true;
                    }
                    break;
                case 2 :
                    if (*current_money >= 1200) {
                        printf("Senter Pembesar berhasil dibeli.\n");
                        *current_money = *current_money - 1200;
                        succeed = true;
                    }
                    break;
                case 3 :
                    if (*current_money >= 1500) {
                        printf("Pintu Kemana Saja berhasil dibeli.\n");
                        *current_money = *current_money - 1500;
                        succeed = true;
                    }
                    break;
                case 4 :
                    if (*current_money >= 3000) {
                        printf("Mesin Waktu berhasil dibeli.\n");
                        *current_money = *current_money - 3000;
                        succeed = true;
                    }
                    break;
                case 5 :
                    if (*current_money >= 800) {
                        printf("Senter Pengecil berhasil dibeli.\n");
                        *current_money = *current_money - 800;
                        succeed = true;
                    }
                    break;
                default : /* unreachable state */
                    printf("Unknown Gadget berhasil dibeli.\n");
            }
            if (succeed == false) {
                printf("Uang tidak cukup untuk membeli gadget. Nguli lagi yuk :')\n");
            }
            else {
                addGadget(inventory, gadget);
            }
        }
    }
}
void useGadget(ListPos *inventory, int idx, int *current_bagcapacity, MAP Map, char* current_loc, Matrix adjMatrix, ListDin building, POINT headQuarter, List *inProgress, Stack *bag, int* current_time, boolean *efekHeavyItem, boolean* speedBoost, int* boostCount){
// mmenggunakan gadget pada index idx inventory dan mendapatkan kemampuan spesial dari gadget yang digunakan
// I.S. inventory dan gadget terdefinisi
// F.S. gadget digunakan kemudian hangus atau di hapus dalam inventory.
    int gadget;
    gadget=ELMT_LISTPOS(*inventory,idx);
    switch(gadget){
        case 1 :
            kainPembungkusWaktu(inProgress, bag);
            break;
        case 2 :
            increaseBagCapacity(current_bagcapacity, 'd');
            break;
        case 3 :
            move(Map, current_loc, adjMatrix, building, headQuarter, current_time, *inProgress, true, speedBoost, boostCount);
            break;
        case 4 :
            if (*current_time<=50) {
                *current_time=0;
            }
            else {
                *current_time-=50;
            }
            break;
        case 5 :
            if (*efekHeavyItem) {
                *efekHeavyItem=false;
            }
            break;
        default : /* unreachable state */
            printf("Unknown Gadget berhasil dibeli.\n");
    }
    delGadget(inventory,idx);
}

void gadgetInfo(){
    /* I.S. Sembarang */
    /* F.S. Output berupa info dari gadget */
    printf("1. Kain Pembungkus Waktu\n");
    printf("    Harga: 800 Yen\n");
    printf("    Setiap kain pembungkus waktu dapat dipakai sekali untuk perishable item\n");
    printf("    teratas pada tas agar kembali ke durasi semula\n");
    printf("2. Senter Pembesar\n");
    printf("    Senter pembesar dapat digunakan untuk meningkatkan kapasitas tas sebesar\n");
    printf("    dua kali lipat, namun tidak melebihi batas kapasitas maksimum\n");
    printf("3. Pintu Kemana Saja\n");
    printf("    Harga: 1500 Yen\n");
    printf("    Pintu Kemana Saja dapat digunakan sekali untuk berpindah lokasi yang diinginkan\n");
    printf("    tanpa menambah unit waktu.\n");
    printf("4. Mesin Waktu\n");
    printf("    Harga: 3000 Yen\n");
    printf("    Mesin waktu dapat digunakan untuk mengurangi waktu sebanyak 50 unit (jika waktu\n");
    printf("    kurang dari 50 unit, maka waktu menjadi 0 unit). Pesanan yang masuk dalam jangka\n");
    printf("    waktu 50 unit tersebut tidak akan hilang/kembali ke To Do List, dan tidak akan \n");
    printf("    muncul kembali ke To Do List ketika waktu masuknya dilampaui lagi.\n");
    printf("5. Senter Pengecil\n");
    printf("    Harga: 800 Yen\n");
    printf("    Senter pengecil dapat digunakan untuk menghilangkan efek dari satu heavy item\n");
    printf("    jika terdapat pada tumpukan teratas tas. Efek dari senter pengecil ini akan\n");
    printf("    berlangsung sampai melakukan Drop Off/Return pertama kali setelah penggunaan\n");
    printf("    gadget ini.\n");
}

void returnToSender(List *toDoList, List *inProgress, Stack *bag, int *returnAbility)
// provides the effect "Return to Sender"
// does not check if the user has the gadget necessary to use it.
{
    Elements temp; stackEl popped;
    if (!isLinkedListEmpty(*inProgress)){
        deleteLinkedListFirst(inProgress, &temp);
        // printf("%c, %d\n", temp.itemType, *returnAbility); buat ngetes
        if (temp.itemType != 'V' && *returnAbility > 0){ // fungsinya gbs di item VIP soalnya
            pop(bag, &popped);

            insertLinkedListFirst(toDoList, temp);
            switch (temp.itemType){
                case 'N': printf("Normal"); break;
                case 'H': printf("Heavy"); break;
                case 'P': printf("Perishable"); break;
            }
            printf(" item berhasil dikembalikan ke Pick Up Point %c\n", temp.pickUp);
            *returnAbility =- 1;
        }
        else {
            printf("Ability tidak dipakai karena item VIP atau tidak punya ability Return To Sender\n");
            insertLinkedListFirst(inProgress, temp);
        }
    }
    else {
        printf("Tidak ada item di bag.\n");
    }
}

void kainPembungkusWaktu(List *inProgress, Stack *bag){
    if(TOP(*bag).itemType == 'P'){
        Elements temp;
        deleteLinkedListFirst(inProgress, &temp);
        temp.perish = TOP(*bag).perish;
        insertLinkedListFirst(inProgress, temp);
    }
    printf("Kain Pembungkus Waktu berhasil digunakan!\n");
}
