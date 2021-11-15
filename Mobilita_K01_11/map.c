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

int getLocationCode(char locationChar, ListDin building) {
    /* KAMUS LOKAL */
    int i, code;
    boolean found;
    /* Code merupakan indeks Matrix */

    /* ALGORITMA */
    if (locationChar == '8') {
        code = 0;
    }
    else {
        i = 0;
        found = false;
        while (i < length(building) && !found) {
            if (locationChar == ELMT_CHAR(building, i)) {
                code = i+1;
                found = true;
            }
            else {
                i++;
            }
        }
    }
    return code;
}

boolean isAccessible(char buildingChar1, char buildingChar2, Matrix adjMatrix, ListDin building) {
    /* KAMUS LOKAL */
    int buildingCode1, buildingCode2;

    /* ALGORITMA */
    buildingCode1 = getLocationCode(buildingChar1, building);
    buildingCode2 = getLocationCode(buildingChar2, building);
    if (ELMT_MATRIX(adjMatrix, buildingCode1, buildingCode2) == 1) {
        return true;
    }
    else {
        return false;
    }
}

boolean isPickUp(List toDoList, char buildingChar) {
    /* KAMUS LOKAL */
    Address p;
    boolean exist;

    /* ALGORITMA */
    p = toDoList;
    exist = false;
    while (p != NULL && !exist) {
        if (INFO(p).pickUp == buildingChar) {
            exist = true;
        }
        else {
            p = NEXT(p);
        }
    }
    return exist;
}

boolean isDropOff(List inProgress, char buildingChar) {
    /* KAMUS LOKAL */
    Address p;
    boolean exist;

    /* ALGORITMA */
    p = inProgress;
    return (INFO(p).dropOff == buildingChar);
    }
    /*
    exist = false;
    while (p != NULL && !exist) {
        if (INFO(p).dropOff == buildingChar) {
            exist = true;
        }
        else {
            p = NEXT(p);
        }
    }
    return exist;
    */

void displayColoredLoc(MAP Map, char current_loc, Matrix adjMatrix, ListDin building, int i, int j, List inProgress, List toDoList) {
    /* KAMUS LOKAL */

    /* ALGORITMA */
    /* posisi Mobita */
    if(ELMT_MAP(Map, i, j) == current_loc) {
        print_yellow(ELMT_MAP(Map, i, j));
    }
    /* lokasi drop off */
    else if (isDropOff(inProgress, ELMT_MAP(Map, i, j))) {
        print_blue(ELMT_MAP(Map, i, j));
    }
    /* lokasi pick up */
    else if (isPickUp(toDoList, ELMT_MAP(Map, i, j))) {
        print_red(ELMT_MAP(Map, i, j));
    }
    /* location to building */
    else if ((isAccessible(ELMT_MAP(Map, i, j), current_loc, adjMatrix, building)) && (ELMT_MAP(Map, i, j) != current_loc) && (ELMT_MAP(Map, i, j) != '*')) {
        print_green(ELMT_MAP(Map, i, j));
    }
    else {
        printf("%c", ELMT_MAP(Map, i, j));
    }
    /*
    location to headQuarter
    if ((isAccessible('8', current_loc, adjMatrix, building)) && (ELMT_MAP(Map, i, j) != current_loc)) {
        print_green(ELMT_MAP(Map, i, j));
    }
    */
}

void displayColoredMap(MAP Map, char current_loc, Matrix adjMatrix, ListDin building, List inProgress, List toDoList) {
    /* KAMUS LOKAL */
    Index i, j;

    // ALGORITMA
    for(i=0; i<ROWS_MAP(Map); i++){
        for(j=0; j<COLS_MAP(Map); j++){
            displayColoredLoc(Map, current_loc, adjMatrix, building, i, j, inProgress, toDoList);
            if(j < COLS_MAP(Map)){
                printf(" ");
            }
        }
        if(i < ROWS_MAP(Map)){
            printf("\n");
        }
    }
}
