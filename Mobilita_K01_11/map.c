/*
    NIM             : 13520019
    Nama            : Maharani Ayu Putri Irawan
    Tanggal         : 19/9/2021
    Topik praktikum : MAP
    Deskripsi       : Membuat implementasi ADT MAP
*/

#include <stdio.h>
#include <stdlib.h>
#include "map.h"

/* rowEff >= 1 dan colEff >= 1 */
/* Indeks matriks yang digunakan: [0..ROW_CAP-1][0..COL_CAP-1] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MAP *** */
void CreateMap(int nRow, int nCol, MAP *m)
/* Membentuk sebuah MAP "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
{
    // KAMUS
    // ALGORITMA
    ROWS_MAP(*m) = nRow;
    COLS_MAP(*m) = nCol;
}

/* *** Selektor "DUNIA MAP" *** */
boolean isMapIdxValid(int i, int j)
/* Mengirimkan true jika i, j adalah Index yang valid untuk matriks apa pun */
{
    // KAMUS
    // ALGORITMA
    return ((i>=0 && i<MAP_ROW_CAP) && (j>=0 && j<MAP_COL_CAP));
}


/* ********** Assignment  MAP ********** */
void copyMap(MAP mIn, MAP *mRes)
/* Melakukan assignment MRes = MIn */
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    Index i, j;

    // ALGORITMA
    ROWS_MAP(*mRes) = ROWS_MAP(mIn);
    COLS_MAP(*mRes) = COLS_MAP(mIn);

    for(i=0; i<ROWS_MAP(mIn); i++){
        for(j=0; j<COLS_MAP(mIn); j++){
            ELMT_MAP(*mRes, i, j) = ELMT_MAP(mIn, i, j);
        }
    }
}

/* ********** KELOMPOK BACA/TULIS ********** */
void readMap(MAP *m, int nRow, int nCol)
/* I.S. isIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMAP(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    Index i, j;

    // ALGORITMA
    CreateMap(nRow, nCol, &(*m));

    for(i=0; i<ROWS_MAP(*m); i++){
        for(j=0; j<COLS_MAP(*m); j++){
            scanf("%c", &ELMT_MAP(*m, i, j));
        }
    }
}

void displayMap(MAP m)
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: Menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    Index i, j;

    // ALGORITMA
    for(i=0; i<ROWS_MAP(m); i++){
        for(j=0; j<COLS_MAP(m); j++){
            printf("%c", ELMT_MAP(m, i, j));
            if(j < COLS_MAP(m)){
                printf(" ");
            }
        }
        if(i < ROWS_MAP(m)){
            printf("\n");
        }
    }
}

