/* File: wordmachine.h */
/* Definisi Word Engine */
/* Perubahan menyesuaikan kebutuhan Tugas Besar */
// Last Update : 10/11/2021

#ifndef WORD_ENGINE_H
#define WORD_ENGINE_H

#include "../boolean.h"
#include "charmachine.h"

#define CAPACITY_WORD 50
#define BLANK ' '
#define NEWLINE '\n'
#define NULLCHAR '\0'

typedef struct {
   char contents[CAPACITY_WORD]; /* container penyimpan kata, indeks yang dipakai [0..CAPACITY-1] */
   int length;
} Word;

/* Word Engine State */
extern boolean endWord;
extern boolean endWordFile;
extern Word currentWord;
extern Word currentWordFile;

void ignoreBlankFile();
/* Mengabaikan satu atau beberapa BLANK atau NEWLINE
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar ≠ NEWLINE atau currentChar = MARK */

void processFileRead();

void startWordFile(char filename[FILE_NAME_CAP], boolean *started);
/* I.S. : currentChar sembarang
   F.S. : endWord = true, dan currentChar = MARK;
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */

void advWordFile();
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.
   Proses : Akuisisi kata menggunakan procedure copyWord */

void copyWordFile();
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = NEWLINE atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */

void ignoreBlankConsole();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar = MARK */

void startWordConsole();
/* I.S. : currentChar sembarang
   F.S. : endWord = true, dan currentChar = MARK;
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */

void advWordConsole();
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.
   Proses : Akuisisi kata menggunakan procedure copyWord */

void copyWordConsole();
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */

boolean isWordEqual(Word command);
/* Return true if currentWord is equal to command */

// int readInt();

#endif
