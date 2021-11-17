/* File: charmachine.h */
/* Definisi Character Engine */
/* Perubahan menyesuaikan kebutuhan Tugas Besar */
// Last Update : 10/11/2021

#ifndef CHAR_ENGINE_H
#define CHAR_ENGINE_H

#include "../boolean.h"
#include "../Map/matrix.h"
#include "../Map/point.h"
#include "../List/listdin.h"
#include "../List/list_linked.h"
#include "../Item/prioqueue.h"
#include "../Item/stack.h"
#include "../List/listpos.h"

#define MARK_EOF EOF
#define FILE_NAME_CAP 255
/* Char Engine State */
extern char currentChar;
extern char currentCharFile;
extern boolean eot;
extern boolean eotFile;

void startFile(char filename[FILE_NAME_CAP], boolean *started);
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (false)
          Jika currentChar = MARK maka EOP akan menyala (true) */

void advFile();
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama,
          currentChar mungkin = MARK
          Jika  currentChar = MARK maka EOP akan menyala (true) */

void startConsole();
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (false)
          Jika currentChar = MARK maka EOP akan menyala (true) */

void advConsole();
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama,
          currentChar mungkin = MARK
		      Jika  currentChar = MARK maka EOP akan menyala (true) */

void closeTape();

void processWrite(char filename[FILE_NAME_CAP], int N, int M, int nLoc, int nOrder, POINT headQuarter, ListDin building, Matrix adjMatrix, List orders,
              int nOrderedOrders, PrioQueue orderedOrders, char current_loc, int current_time, int current_money, int current_bagcapacity,
              int nToDoList, List toDoList, int nInProgress, List inProgress, int nInventory, ListPos inventory,
              int boostCount, boolean speedBoost, Stack bag, boolean efekVIP, boolean efekHeavyItem, boolean efekSenterPengecil);

#endif
