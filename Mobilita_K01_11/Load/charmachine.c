/* File: charmachine.c */
/* Implementasi Character Engine */
/* Perubahan menyesuaikan kebutuhan Tugas Besar */
// Last Update : 10/11/2021

#include "charmachine.h"
#include <stdio.h>
#include <stdlib.h>

char currentChar;
char currentCharFile;
boolean eot;
boolean eotFile;

static FILE * tape;
static FILE * tapeFile;
static FILE * writeFile;
static int retval;

void startFile(char filename[FILE_NAME_CAP], boolean *started) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (false)
          Jika currentChar = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	tapeFile = fopen(filename, "r");
	if (tapeFile == NULL)
        *started = false;
    else
        *started = true;
}

void advFile() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama,
          currentChar mungkin = MARK
		      Jika  currentChar = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	currentCharFile = getc(tapeFile);
	eotFile = (currentCharFile == MARK_EOF);
	/*
	if (eotFile){
        fflush(tapeFile);
        fclose(tapeFile);
	}
	*/
}

void startConsole() {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (false)
          Jika currentChar = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	tape = stdin;
	advConsole();
}

void advConsole() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama,
          currentChar mungkin = MARK
		      Jika  currentChar = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	retval = fscanf(tape, "%c", &currentChar);
	eot = (currentChar == '\n');
}

void closeTape()
{
    fclose(tape);
}

void processWrite(char out_filename[FILE_NAME_CAP], int N, int M, int nLoc, int nOrder, POINT headQuarter, ListDin building, Matrix adjMatrix, List orders,
              int nOrderedOrders, PrioQueue orderedOrders, char current_loc, int current_time, int current_money, int current_bagcapacity,
              int nToDoList, List toDoList, int nInProgress, List inProgress, int nInventory, ListPos inventory,
              int boostCount, boolean speedBoost, Stack bag, boolean efekVIP, boolean efekHeavyItem)
{
    writeFile = fopen(out_filename, "w");
    if(writeFile != NULL){
        printf("Disimpan dalam file %s\n", out_filename);
        writeFile = fopen(out_filename, "w");

        fprintf(writeFile, "%d %d\n", N, M);
        fprintf(writeFile, "%d %d\n", Absis(headQuarter), Ordinat(headQuarter));
        fprintf(writeFile, "%d\n", nLoc);
        if(!isEmpty(building)){
            for(int i = 0; i < nLoc; i++){
                fprintf(writeFile, "%c %d %d\n", ELMT_CHAR(building, i), Absis(ELMT_POINT(building, i)), Ordinat(ELMT_POINT(building, i)));
            }
        }

        for(int i = 0; i < nLoc+1; i++){
            for(int j = 0; j < nLoc+1; j++){
                fprintf(writeFile, "%d", ELMT_MATRIX(adjMatrix, i, j));
                if(j < nLoc)
                    fprintf(writeFile, " ");
            }
            fprintf(writeFile, "\n");
        }

        Address p = FIRST(orders);
        fprintf(writeFile, "%d\n", nOrder);
        for(int i = 0; i < nOrder; i++){
            fprintf(writeFile, "%d %c %c %c %d\n", NTIME(INFO(p)), PICKUP(INFO(p)), DROPOFF(INFO(p)), ITEMTYPE(INFO(p)), PERISH(INFO(p)));
            p = NEXT(p);
        }

        fprintf(writeFile, "%d\n", nOrderedOrders);

        pqEls tempPQ;
        for(int i = 0; i < nOrderedOrders; i++){
            dequeue(&orderedOrders, &tempPQ);
            fprintf(writeFile, "%d %c %c %c %d\n", NTIME(tempPQ), PICKUP(tempPQ), DROPOFF(tempPQ), ITEMTYPE(tempPQ), PERISH(tempPQ));
        }
        // Baca array orderedOrders.buffer[IDX_HEAD] -- orderedOrders.buffer[IDX_TAIL]

        fprintf(writeFile, "%c\n", current_loc);
        fprintf(writeFile, "%d\n", current_time);
        fprintf(writeFile, "%d\n", current_money);
        fprintf(writeFile, "%d\n", current_bagcapacity);
        fprintf(writeFile, "%d\n", nToDoList);

        p = FIRST(toDoList);
        for(int i = 0; i < nToDoList; i++){
            fprintf(writeFile, "%d %c %c %c %d\n", NTIME(INFO(p)), PICKUP(INFO(p)), DROPOFF(INFO(p)), ITEMTYPE(INFO(p)), PERISH(INFO(p)));
            p = NEXT(p);
        }

        fprintf(writeFile, "%d\n", nInProgress);

        p = FIRST(inProgress);
        for(int i = 0; i < nInProgress; i++){
            fprintf(writeFile, "%d %c %c %c %d\n", NTIME(INFO(p)), PICKUP(INFO(p)), DROPOFF(INFO(p)), ITEMTYPE(INFO(p)), PERISH(INFO(p)));
            p = NEXT(p);
        }

        fprintf(writeFile, "%d\n", nInventory);
        for(int i = 0; i < nInventory; i++){
            fprintf(writeFile, "%d\n", ELMT_LISTPOS(inventory, i));
        }

        fprintf(writeFile, "%d\n", boostCount);
        fprintf(writeFile, "%d\n", speedBoost);

        stackEl stEl;
        for(int i = 0; i < (nInProgress); i++){
            pop(&bag, &stEl);
            fprintf(writeFile, "%d %c %c %c %d\n", NTIME(stEl), PICKUP(stEl), DROPOFF(stEl), ITEMTYPE(stEl), PERISH(stEl));
        }

        fprintf(writeFile, "%d\n", efekVIP);
        fprintf(writeFile, "%d", efekHeavyItem);

        fclose(writeFile);
    }
    else
        printf("Tidak bisa menyimpan ke file.");
}
