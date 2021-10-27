/* File: charmachine.c */
/* Implementasi Character Engine */
/* Perubahan menyesuaikan kebutuhan Tugas Besar */

#include "charmachine.h"
#include <stdio.h>

char currentChar;
boolean eot;

static FILE * tape;
//static int retval;

void start(char filename[FILE_NAME_CAP]) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (false)
          Jika currentChar = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	// tape = stdin;
	tape = fopen(filename, "r");
	if (tape == NULL){
        printf("File %s tidak tersedia\n", filename);
        
    }
    else
        adv();
}

void adv() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama,
          currentChar mungkin = MARK
		      Jika  currentChar = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	// retval = fscanf(tape,"%c",&currentChar);
	currentChar = getc(tape);
	eot = (currentChar == EOF);
	if (eot) {
       fclose(tape);
 	}
}

