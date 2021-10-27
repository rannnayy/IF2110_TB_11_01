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
Word currentWord;

void ignoreBlank()
/* Mengabaikan satu atau beberapa BLANK atau NEWLINE
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar ≠ NEWLINE atau currentChar = MARK */
{
    while((currentChar == BLANK || currentChar == NEWLINE || currentChar == NULLCHAR) && currentChar != MARK_EOF)
        adv();
}
void startWord(char filename[FILE_NAME_CAP])
/* I.S. : currentChar sembarang
   F.S. : endWord = true, dan currentChar = MARK;
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
{
    start(filename);
    ignoreBlank();

    if(currentChar == MARK_EOF)
        endWord = true;
    else{
        endWord = false;
        copyWord();
    }
}
void advWord()
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.
   Proses : Akuisisi kata menggunakan procedure copyWord */
{
    ignoreBlank();
    if(currentChar == MARK_EOF)
        endWord = true;
    else{
        ignoreBlank();
        copyWord();
        ignoreBlank();
    }
}
void copyWord()
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = NEWLINE atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
{
    int i;

    i = 0;
    while(currentChar != MARK_EOF && currentChar != NEWLINE && currentChar != BLANK && currentChar != NULLCHAR && i < CAPACITY_WORD){
        currentWord.contents[i] = currentChar;
        adv();
        i += 1;
    }
    currentWord.length = i;
}

