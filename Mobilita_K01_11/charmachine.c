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
	if (eotFile){
        fclose(tapeFile);
        fflush(tapeFile);
	}
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
