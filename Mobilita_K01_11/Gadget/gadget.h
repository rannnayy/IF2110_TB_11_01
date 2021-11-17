/* File: gadget.h */
/* gadget didefinisikan dalam angka yaitu 1 -> Kain Pembungkus Waktu, 2 -> Senter Pembesar, 3 - >Pintu Kemana Saja, 4 -> Mesin Waktu, 5 -> Senter Pengecil */

#ifndef GADGET_H
#define GADGET_H

#include "../boolean.h"
#include "../Item/stack.h"
#include "../Item/orderItems.h"
#include "../List/listpos.h"
#include "../List/listdin.h"
#include "../Load/wordmachine.h"
#include "../Load/start_game.h"
#include "../Map/map.h"
#include "../Map/matrix.h"
#include "../Map/point.h"
#include "../Map/move.h"

void addGadget(ListPos *inventory, int gadget);
// Menambahkan Gadget ke dalam Inventory
// I.S. inventory dan gadget terdefinisi
// F.S. inventory berisi gadget

void delGadget(ListPos *inventory, int idx);
// menghapus gadget dalam inventory
// I.S. inventory dan gadget terdefinisi
// F.S. gadget dihapus dari inventory

void displayInventory(ListPos *inventory, int *current_bagcapacity, char* current_loc, ListDin building, POINT headQuarter, List *inProgress, Stack *bag, int* current_time, boolean *efekSenterPengecil);
// memperlihatkan semua gadget yang ada di dalam inventory
// I.S. inventory terdefinisi
// F.S. gadget yang ada di dalam inventory diperlihatkan

void buyGadget(ListPos *inventory, int *current_money);
// memperlihatkan semua list gadget yang dapat dibeli
// I.S. inventory dan gadget terdefinisi
// F.S. lsit gadget diperlihatkan dan gadget dibeli atau tidak jadi dibeli

void useGadget(ListPos *inventory, int idx, int *current_bagcapacity, char* current_loc, ListDin building, POINT headQuarter, List *inProgress, Stack *bag, int* current_time, boolean *efekSenterPengecil);
// mmenggunakan gadget dan mendapatkan kemampuan spesial dari gadget
// I.S. gadget terdefinisi
// F.S. gadget digunakan kemudian hangus atau di hapus dalam inventory.

void gadgetInfo();
/* I.S. Sembarang */
/* F.S. Output berupa info dari gadget */

void returnToSender(List *toDoList, List *inProgress, Stack *bag, int *returnAbility);
// provides the effect "Return to Sender"
// does not check if the user has the gadget necessary to use it.
// returnAbility is the amount of return to sender the player has
// I.S. bebas
// F.S. item teratas di tas akan dikembalikan apabila ada ability return to sender dan item bukan item VIP

void kainPembungkusWaktu(List *inProgress, Stack *bag);
// gadget kainPembungkusWaktu
// memakai info dari bag, reset time perish
// I.S. bebas
// F.S. apabila gadget teratas tas merupakan perishable, reset timer perishable di in progress

#endif
