/********* START GAME *********/
/*
    File Name   : start_game.c
    Author      : K01_11
    Last Update : 27/10/2021
    Description : Function to start Mobilita game implementations, including load and read file as well as store in variables
                  and various data structures.
*/

#include <stdio.h>
#include <stdlib.h>
#include "wordmachine.h"
#include "point.h"
#include "listdin.h"
#include "matrix.h"
#include "list_linked.h"
#include "pcolor.h"
#include "map.h"
#include "orderItems.h"

void DigitsToInt(Word digits, int* var)
/*  Mengkonversi nilai pada pita kata yang berupa angka menjadi angka, bukan lagi char[]  */
/*  I.S. Word digits terinisialisasi nilai berupa array of char, variabel var sudah dideklarasikan  */
/*  F.S. Variabel var mengandung nilai numerik yang hendak direpresentasikan digits.content[] dalam bentuk char  */
{
    int i;

    for(i = 0; i < digits.length; i++){
        if((int)digits.contents[i] != 0){ // KALAU BUKAN NULL
            *var *= 10;
            *var += (int)(digits.contents[i] - 48);
        }
    }
}

void StartGame(int* N, int* M, int* nLoc, int* nOrder, POINT* headQuarter, ListDin* building, Matrix* adjMatrix, List* orders, PrioQueue *orderedOrders)
/*  Memulai permainan dengan membaca nama file berisi konfigurasi permainan, lalu membaca N (jumlah baris), M (jumlah kolom),
    POINT headQuarter (koordinat dalam Map NxM), nLoc (jumlah lokasi), nLoc baris lokasi ListDin building(terdiri atas karakter
    bangunan dan POINT koordinat bangunan), nLoc+1 baris dan nLoc+1 kolom adjMatrix (Matrix Adjacency), nOrder (jumlah pesanan),
    nOrder baris List orders (detail setiap pesanan berupa waktu, lokasi pick-up, lokasi drop-off, jenis item, dan (bila ada) waktu
    perishable). */
/*  I.S. Variabel N, M, nLoc, nOrder, headQuarter, building, adjMatrix, orders sudah didefinisikan. Sebuah file berisi konfigurasi
         permainan sudah tersedia pada root directory */
/*  F.S. Seluruh variabel terinisialisasi nilai konfigurasi awal yang dibaca dari file. */
{
    // Load File
    char filename[255];
    printf("Masukkan nama file: ");
    scanf("%s", filename);

    // Start file reading
    startWord(filename);
    ignoreBlank();

    //printf("\n");
    *N = 0;
    *M = 0;
    // Assign N (number of rows)
    DigitsToInt(currentWord, &(*N));

    advWord();
    // Assign M (number of columns)
    DigitsToInt(currentWord, &(*M));

    // printf("%d %d\n", *N, *M);

    int x, y;
    x = 0;
    y = 0;
    // Assign POINT headQuarter
    advWord();
    // Assign x of POINT headQuarter
    DigitsToInt(currentWord, &x);

    advWord();
    // Assign y of POINT headQuarter
    DigitsToInt(currentWord, &y);

    // Make POINT headQuarter
    *headQuarter = MakePOINT(x, y);

    // TulisPOINT(*headQuarter);
    // printf("\n");

    *nLoc = 0;
    advWord();
    // Assign nLoc (number of locations)
    DigitsToInt(currentWord, &(*nLoc));

    // printf("%d\n", *nLoc);

    int i;
    CreateListDin(&(*building), *nLoc);
    NEFF(*building) = *nLoc;
    for(i = 0; i < *nLoc; i++){
        x = 0;
        y = 0;
        // Store Building Character (Assumption: number of buildings max 26)
        advWord();
        ELMT_CHAR(*building, i) = currentWord.contents[0];

        // Store Building Point, each for x and y
        advWord();
        DigitsToInt(currentWord, &x);
        advWord();
        DigitsToInt(currentWord, &y);

        ELMT_POINT(*building, i) = MakePOINT(x, y);

    }
    // displayList(*building);
    // printf("\n");

    int j;
    // Store Adjacency Matrix
    CreateMatrix((*nLoc)+1, (*nLoc)+1, &(*adjMatrix));
    for(i = 0; i < (*nLoc)+1; i++){
        for(j = 0; j < (*nLoc)+1; j++){
            advWord();
            ELMT_MATRIX(*adjMatrix, i, j) = (int)(currentWord.contents[0] - 48);
        }
    }
    // displayMatrix(*adjMatrix);
    // printf("\n");

    *nOrder = 0;
    advWord();
    // Assign nOrder (number of Orders)
    DigitsToInt(currentWord, &(*nOrder));

    // printf("%d\n", *nOrder);

    CreateList(&(*orders));
    Elements ordEl;
    for(i = 0; i < (*nOrder); i++){
        // Store ordEl.nTime
        advWord();
        NTIME(ordEl) = 0;
        DigitsToInt(currentWord, &NTIME(ordEl));
        // Store ordEl.pickUp
        advWord();
        PICKUP(ordEl) = (char)currentWord.contents[0];
        // Store ordEl.dropOff
        advWord();
        DROPOFF(ordEl) = (char)currentWord.contents[0];
        // Store ordEl.itemType
        advWord();
        ITEMTYPE(ordEl) = (char)currentWord.contents[0];
        // Store ordEl.perish
        if (ITEMTYPE(ordEl) == 'P'){
            advWord();
            PERISH(ordEl) = 0;
            DigitsToInt(currentWord, &PERISH(ordEl));
        }
        else
            PERISH(ordEl) = -1;

        // Store Elements in Linked List
        insertLinkedListLast(&(*orders), ordEl);
    }
    // displayLinkedList(*orders);
    // printf("\n");

    // sorts the orders
    CreatePrioQueue(orderedOrders);
    queueOrder(orderedOrders, &(*orders));

    // buat ngecek bentar udh aman blm queuenya
    // printf("trying to print\n");
    // while(!pqIsEmpty(*orderedOrders)){
    //     pqEls temp;
    //     dequeue(orderedOrders, &temp);
    //     printf("%c %c %c\n", temp.pickUp, temp.dropOff, temp.itemType);
    // }
}

MAP StartMapConfiguration(int* N, int* M, POINT* headQuarter, ListDin* building, Matrix* adjMatrix)
/*  Membuat konfigurasi Map setelah dibaca dari fungsi StartGame, N dan M (ukuran NxM dari peta), 
    headQuarter (koordinat HQ), building (koordinat tiap bangunan), dan adjMatrix (Matrix adjacency antar bangunan)*/
/* I.S. Semua variabel terdefinisi */
/* F.S. Output Map */ 
{
    MAP Map;
    int i, j, Row, Col;
    Row = *N+2;
    Col = *M+2;
    CreateMap(Row, Col, &Map);

    // Initialize every element with *
    for (i=0; i<Row; i++){
        for (j=0; j<Col; j++){
            if ((i == 0 || i == Row-1) ||(j == 0 || j == Col-1)){
                ELMT_MAP(Map, i, j) = '*';
            } else {
                ELMT_MAP(Map, i, j) = ' ';
            }
        }
    }

    // Set Headquarter
    ELMT_MAP(Map, Absis(*headQuarter), Ordinat(*headQuarter)) = '8';

    // Set Other building
    for (i=0; i<length(*building); i++){
        ELMT_MAP(Map, Absis(ELMT_POINT(*building, i)), Ordinat(ELMT_POINT(*building, i))) = ELMT_CHAR(*building, i);
    }

    // displayMap(Map);
    return Map;
}