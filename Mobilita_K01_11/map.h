/* ********** Definisi TYPE MAP dengan Index dan elemen integer ********** */

#ifndef MAP_H
#define MAP_H

#include "boolean.h"
#include "list_linked.h"
#include "pcolor.h"
#include "boolean.h"
#include "listdin.h"
#include "matrix.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define MAP_ROW_CAP 100
#define MAP_COL_CAP 100

typedef int Index; /* Index baris, kolom */
typedef char ElTypeMap;
typedef struct
{
   ElTypeMap contentsMap[MAP_ROW_CAP][MAP_COL_CAP];
   int rowEffMap; /* banyaknya/ukuran baris yg terdefinisi */
   int colEffMap; /* banyaknya/ukuran kolom yg terdefinisi */
} MAP;
/* rowEffMap >= 1 dan colEffMap >= 1 */
/* Indeks matriks yang digunakan: [0..ROW_CAP-1][0..COL_CAP-1] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MAP *** */
void CreateMap(int nRow, int nCol, MAP *m);
/* Membentuk sebuah APp "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */

/* *** Selektor *** */
#define ROWS_MAP(M) (M).rowEffMap
#define COLS_MAP(M) (M).colEffMap
#define ELMT_MAP(M, i, j) (M).contentsMap[(i)][(j)]

/* *** Selektor "DUNIA MAP" *** */
boolean isIdxMapValid(int i, int j);
/* Mengirimkan true jika i, j adalah Index yang valid untuk matriks apa pun */


/* ********** Assignment  MAP ********** */
void copyMap(MAP mIn, MAP *mRes);
/* Melakukan assignment MRes = MIn */

/* ********** KELOMPOK BACA/TULIS ********** */
void readMap(MAP *m, int nRow, int nCol);
/* I.S. isIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMAP(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/

void displayMap(MAP m);
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: Menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/

int getLocationCode(char locationChar, ListDin building);

boolean isAccessible(char buildingChar1, char buildingChar2, Matrix adjMatrix, ListDin building);

boolean isPickUp(List toDoList, char buildingChar);

boolean isDropOff(List inProgress, char buildingChar);

void displayColoredLoc(MAP Map, char current_loc, Matrix adjMatrix, ListDin building, int i, int j, List inProgress, List toDoList);

void displayColoredMap(MAP Map, char current_loc, Matrix adjMatrix, ListDin building, List inProgress, List toDoList);

#endif
