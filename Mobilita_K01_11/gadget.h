/* File: gadget.h */
/* gadget didefinisikan dalam angka yaitu 1 -> Kain Pembungkus Waktu, 2 -> Senter Pembesar, 3 - >Pintu Kemana Saja, 4 -> Mesin Waktu, 5 -> Senter Pengecil */

#ifndef GADGET_H
#define GADGET_H

#include "listpos.h"
#include "boolean.h"
#include "map.h"
#include "matrix.h"
#include "listdin.h"
#include "point.h"

void addGadget(ListPos *inventory, int gadget);
// Menambahkan Gadget ke dalam Inventory
// I.S. inventory dan gadget terdefinisi
// F.S. inventory berisi gadget

void delGadget(ListPos *inventory, int idx);
// menghapus gadget dalam inventory
// I.S. inventory dan gadget terdefinisi
// F.S. gadget dihapus dari inventory

void displayInventory(ListPos *inventory, int *current_bagcapacity, int *time_inc, MAP Map, char* current_loc, Matrix adjMatrix, ListDin building, POINT headQuarter, List inProgress, int* current_time);
// memperlihatkan semua gadget yang ada di dalam inventory
// I.S. inventory terdefinisi
// F.S. gadget yang ada di dalam inventory diperlihatkan

void buyGadget(ListPos *inventory, int *current_money);
// memperlihatkan semua list gadget yang dapat dibeli
// I.S. inventory dan gadget terdefinisi
// F.S. lsit gadget diperlihatkan dan gadget dibeli atau tidak jadi dibeli

void useGadget(ListPos *inventory, int idx, int *current_bagcapacity, int *time_inc, MAP Map, char* current_loc, Matrix adjMatrix, ListDin building, POINT headQuarter, List inProgress, int* current_time);
// mmenggunakan gadget dan mendapatkan kemampuan spesial dari gadget
// I.S. gadget terdefinisi
// F.S. gadget digunakan kemudian hangus atau di hapus dalam inventory.

void gadgetInfo();
/* I.S. Sembarang */
/* F.S. Output berupa info dari gadget */
#endif