/*
    NIM             : 13520019
    Nama            : Maharani Ayu Putri Irawan
    Tanggal         : 26/9/2021
    Topik praktikum : WordMachine
    Deskripsi       : Membuat implementasi Word Machine.
*/
/* Perubahan menyesuaikan kebutuhan Tugas Besar */

#include <stdio.h>
#include <stdlib.h>
#include "wordmachine.h"

boolean endWord;
boolean endWordFile;
Word currentWord;
Word currentWordFile;

void ignoreBlankFile()
/* Mengabaikan satu atau beberapa BLANK atau NEWLINE
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar ≠ NEWLINE atau currentChar = MARK */
{
    while((currentCharFile == BLANK || currentCharFile == NEWLINE || currentCharFile == NULLCHAR) && currentCharFile != MARK_EOF)
        advFile();
}

void processFileRead()
{
    ignoreBlankFile();
    if(currentCharFile == MARK_EOF){
        endWordFile = true;
    }
    else{
        endWordFile = false;
        copyWordFile();
    }
}

void startWordFile(char filename[FILE_NAME_CAP], boolean *started)
/* I.S. : currentChar sembarang
   F.S. : endWord = true, dan currentChar = MARK;
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
{
    startFile(filename, &(*started));
}
void advWordFile()
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.
   Proses : Akuisisi kata menggunakan procedure copyWord */
{
    ignoreBlankFile();
    if(currentCharFile == MARK_EOF)
        endWordFile = true;
    else{
        ignoreBlankFile();
        copyWordFile();
        ignoreBlankFile();
    }
}
void copyWordFile()
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = NEWLINE atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
{
    int i;

    i = 0;
    while(currentCharFile != MARK_EOF && currentCharFile != NEWLINE && currentCharFile != BLANK && currentCharFile != NULLCHAR && i < CAPACITY_WORD){
        currentWordFile.contents[i] = currentCharFile;
        advFile();
        i += 1;
    }
    currentWordFile.length = i;
}

void ignoreBlankConsole()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar = NEWLINE */
{
    while(currentChar == BLANK)
        advConsole();
}
void startWordConsole()
/* I.S. : currentChar sembarang
   F.S. : endWord = true, dan currentChar = MARK;
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
{
    startConsole();
    ignoreBlankConsole();
    endWord = false;
    copyWordConsole();
}
void advWordConsole()
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.
   Proses : Akuisisi kata menggunakan procedure copyWord */
{
    ignoreBlankConsole();
    if(currentChar == NEWLINE)
        endWord = true;
    else{
        copyWordConsole();
        ignoreBlankConsole();
    }
}
void copyWordConsole()
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
{
    int i;

    i = 0;
    while(currentChar != NEWLINE && currentChar != BLANK && i < CAPACITY_WORD){
        currentWord.contents[i] = currentChar;
        advConsole();
        i += 1;
    }
    currentWord.length = i;
}
