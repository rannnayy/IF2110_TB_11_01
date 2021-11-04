/********* START GAME HEADER *********/
/*
    File Name   : start_game.h
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

void DigitsToInt(Word digits, int* var);
/*  Mengkonversi nilai pada pita kata yang berupa angka menjadi angka, bukan lagi char[]  */
/*  I.S. Word digits terinisialisasi nilai berupa array of char, variabel var sudah dideklarasikan  */
/*  F.S. Variabel var mengandung nilai numerik yang hendak direpresentasikan digits.content[] dalam bentuk char  */

void StartGame(int* N, int* M, int* nLoc, int* nOrder, POINT* headQuarter, ListDin* building, Matrix* adjMatrix, List* orders, PrioQueue *orderedOrders);
/*  Memulai permainan dengan membaca nama file berisi konfigurasi permainan, lalu membaca N (jumlah baris), M (jumlah kolom),
    POINT headQuarter (koordinat dalam Map NxM), nLoc (jumlah lokasi), nLoc baris lokasi ListDin building(terdiri atas karakter
    bangunan dan POINT koordinat bangunan), nLoc+1 baris dan nLoc+1 kolom adjMatrix (Matrix Adjacency), nOrder (jumlah pesanan),
    nOrder baris List orders (detail setiap pesanan berupa waktu, lokasi pick-up, lokasi drop-off, jenis item, dan (bila ada) waktu
    perishable). */
/*  I.S. Variabel N, M, nLoc, nOrder, headQuarter, building, adjMatrix, orders sudah didefinisikan. Sebuah file berisi konfigurasi
         permainan sudah tersedia pada root directory */
/*  F.S. Seluruh variabel terinisialisasi nilai konfigurasi awal yang dibaca dari file. */

MAP StartMapConfiguration(int* N, int* M, POINT* headQuarter, ListDin* building, Matrix* adjMatrix);
/*  Membuat konfigurasi Map setelah dibaca dari fungsi StartGame, N dan M (ukuran NxM dari peta),
    headQuarter (koordinat HQ), building (koordinat tiap bangunan), dan adjMatrix (Matrix adjacency antar bangunan)*/
/* I.S. Semua variabel terdefinisi */
/* F.S. Output Map */
