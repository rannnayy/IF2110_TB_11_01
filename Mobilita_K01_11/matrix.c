/*
    NIM             : 13520019
    Nama            : Maharani Ayu Putri Irawan
    Tanggal         : 19/9/2021
    Topik praktikum : Matrix
    Deskripsi       : Membuat implementasi ADT Matrix
*/

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

/* rowEff >= 1 dan colEff >= 1 */
/* Indeks matriks yang digunakan: [0..ROW_CAP-1][0..COL_CAP-1] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void CreateMatrix(int nRow, int nCol, Matrix *m)
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
{
    // KAMUS
    // ALGORITMA
    ROWS(*m) = nRow;
    COLS(*m) = nCol;
}

/* *** Selektor "DUNIA Matrix" *** */
boolean isMatrixIdxValid(int i, int j)
/* Mengirimkan true jika i, j adalah Index yang valid untuk matriks apa pun */
{
    // KAMUS
    // ALGORITMA
    return ((i>=0 && i<ROW_CAP) && (j>=0 && j<COL_CAP));
}

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
Index getLastIdxRow(Matrix m)
/* Mengirimkan Index baris terbesar m */
{
    // KAMUS
    // ALGORITMA
    return (ROWS(m)-1);
}
Index getLastIdxCol(Matrix m)
/* Mengirimkan Index kolom terbesar m */
{
    // KAMUS
    // ALGORITMA
    return (COLS(m)-1);
}
boolean isMatrixIdxEff(Matrix m, Index i, Index j)
/* Mengirimkan true jika i, j adalah Index efektif bagi m */
{
    // KAMUS
    // ALGORITMA
    return ((i>=0 && i<=getLastIdxRow(m)) && (j>=0 && j<=getLastIdxCol(m)));
}
ElTypeMatrix getElmtDiagonal(Matrix m, Index i)
/* Mengirimkan elemen m(i,i) */
{
    // KAMUS
    // ALGORITMA
    return ELMT_MATRIX(m, i, i);
}

/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mRes)
/* Melakukan assignment MRes = MIn */
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    Index i, j;

    // ALGORITMA
    ROWS(*mRes) = ROWS(mIn);
    COLS(*mRes) = COLS(mIn);

    for(i=0; i<=getLastIdxRow(mIn); i++){
        for(j=0; j<=getLastIdxCol(mIn); j++){
            ELMT_MATRIX(*mRes, i, j) = ELMT_MATRIX(mIn, i, j);
        }
    }
}

/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrix(Matrix *m, int nRow, int nCol)
/* I.S. isIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
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
    CreateMatrix(nRow, nCol, &(*m));

    for(i=0; i<=getLastIdxRow(*m); i++){
        for(j=0; j<=getLastIdxCol(*m); j++){
            scanf("%d", &ELMT_MATRIX(*m, i, j));
        }
    }
}

void displayMatrix(Matrix m)
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
    for(i=0; i<=getLastIdxRow(m); i++){
        for(j=0; j<=getLastIdxCol(m); j++){
            printf("%d", ELMT_MATRIX(m, i, j));
            if(j < getLastIdxCol(m))
                printf(" ");
        }
        if(i < getLastIdxRow(m))
            printf("\n");
    }
}

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
Matrix addMatrix(Matrix m1, Matrix m2)
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil penjumlahan matriks: m1 + m2 */
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    // temp : Matrix temporary
    Index i, j;
    Matrix temp;

    // ALGORITMA
    CreateMatrix(ROWS(m1), COLS(m1), &temp);

    if(countElMatrix(temp) > 0)
        for(i=0; i<=getLastIdxRow(temp); i++)
            for(j=0; j<=getLastIdxCol(temp); j++)
                ELMT_MATRIX(temp, i, j) = ELMT_MATRIX(m1, i, j) + ELMT_MATRIX(m2, i, j);

    return temp;
}
Matrix subtractMatrix(Matrix m1, Matrix m2)
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    // temp : Matrix temporary
    Index i, j;
    Matrix temp;

    // ALGORITMA
    CreateMatrix(ROWS(m1), COLS(m1), &temp);

    if(countElMatrix(temp) > 0)
        for(i=0; i<=getLastIdxRow(temp); i++)
            for(j=0; j<=getLastIdxCol(temp); j++)
                ELMT_MATRIX(temp, i, j) = ELMT_MATRIX(m1, i, j) - ELMT_MATRIX(m2, i, j);

    return temp;
}
Matrix multiplyMatrix(Matrix m1, Matrix m2)
/* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
/* Mengirim hasil perkalian matriks: salinan m1 * m2 */
{
    // KAMUS
    // i, j, k : integer (Index) variabel pencacah looping
    // temp : Matrix temporary
    Index i, j, k;
    Matrix temp;

    // ALGORITMA
    CreateMatrix(ROWS(m1), COLS(m2), &temp);

    if(countElMatrix(temp) > 0){
        // semua isi 0 dulu
        for(i=0; i<=getLastIdxRow(temp); i++)
            for(j=0; j<=getLastIdxCol(temp); j++)
                ELMT_MATRIX(temp, i, j) = 0;

        for(i=0; i<=getLastIdxRow(m1); i++) // baris m1
            for(j=0; j<=getLastIdxCol(m2); j++) // kolom m2
                for(k=0; k<=getLastIdxRow(m2); k++) // baris m2
                    ELMT_MATRIX(temp, i, j) += ELMT_MATRIX(m1, i, k) * ELMT_MATRIX(m2, k, j);
    }

    return temp;
}
Matrix multiplyConst(Matrix m, ElTypeMatrix x)
/* Mengirim hasil perkalian setiap elemen m dengan x */
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    Index i, j;

    // ALGORITMA
    if(countElMatrix(m) > 0)
        for(i=0; i<=getLastIdxRow(m); i++)
            for(j=0; j<=getLastIdxCol(m); j++)
                ELMT_MATRIX(m, i, j) *= x;

    return m;
}
void pMultiplyConst(Matrix *m, ElTypeMatrix k)
/* I.S. m terdefinisi, k terdefinisi */
/* F.S. Mengalikan setiap elemen m dengan k */
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    Index i, j;

    // ALGORITMA
    for(i=0; i<=getLastIdxRow(*m); i++)
        for(j=0; j<=getLastIdxCol(*m); j++)
            ELMT_MATRIX(*m, i, j) *= k;
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */
boolean isMatrixEqual(Matrix m1, Matrix m2)
/* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
/* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
/* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    // eq : boolean True jika equal, False jika tidak equal
    Index i, j;
    boolean eq;

    // ALGORITMA
    eq = true;

    if((getLastIdxCol(m1) == getLastIdxCol(m2)) && (getLastIdxRow(m1) == getLastIdxRow(m2))){
        i = 0;
        while(i <= getLastIdxRow(m1) && eq){
            j = 0;
            while(j <= getLastIdxCol(m1) && eq){
                if(ELMT_MATRIX(m1, i, j) != ELMT_MATRIX(m2, i, j))
                    eq = false;
                else
                    j += 1;
            }
            i += 1;
        }
    }
    else
        eq = false;

    return eq;
}
boolean isMatrixNotEqual(Matrix m1, Matrix m2)
/* Mengirimkan true jika m1 tidak sama dengan m2 */
{
    // KAMUS
    // ALGORITMA
    return (!isMatrixEqual(m1, m2));
}
boolean isMatrixSizeEqual(Matrix m1, Matrix m2)
/* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
{
    // KAMUS
    // ALGORITMA
    //return (count(m1) == count(m2)) && (getLastIdxCol(m1) == getLastIdxCol(m2)) && (getLastIdxRow(m1) == getLastIdxRow(m2));
    return (countElMatrix(m1) == countElMatrix(m2)) && (ROWS(m1) == ROWS(m2)) && (COLS(m1) == COLS(m2));
}

/* ********** Operasi lain ********** */
int countElMatrix(Matrix m)
/* Mengirimkan banyaknya elemen m */
{
    // KAMUS
    // ALGORITMA
    return (ROWS(m)*COLS(m));
}

/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
boolean isSquare(Matrix m)
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
{
    // KAMUS
    // ALGORITMA
    return (ROWS(m) == COLS(m));
}
boolean isSymmetric(Matrix m)
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m)
   dan untuk setiap elemen m, m(i,j)=m(j,i) */
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    // sym : boolean True jika simetris, False jika tidak simetris
    Index i, j;
    boolean sym;

    // ALGORITMA
    sym = true;
    if(countElMatrix(m) > 0){
        if(isSquare(m)){
            i = 0;
            while(i <= getLastIdxRow(m) && sym){
                j = 0;
                while(j < i && sym){
                    if(ELMT_MATRIX(m, i, j) != ELMT_MATRIX(m, j, i))
                        sym = false;
                    else
                        j += 1;
                }
                i += 1;
            }
        }
        else
            sym = false;
    }
    return sym;
}
boolean isIdentity(Matrix m)
/* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan
   setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    // id : boolean True jika merupakan matriks identitas, False jika tidak
    Index i, j;
    boolean id;

    // ALGORITMA
    id = true;

    if(countElMatrix(m) > 0){
        if(isSquare(m)){
            i = 0;
            while(i <= getLastIdxRow(m) && id){
                j = 0;
                while(j <= getLastIdxCol(m) && id){
                    if(i == j && ELMT_MATRIX(m, i, j) != 1)
                        id = false;
                    else if(i != j && ELMT_MATRIX(m, i, j) != 0)
                        id = false;
                    else
                        j += 1;
                }
                i += 1;
            }
        }
        else
            id = false;
    }
    return id;
}
boolean isSparse(Matrix m)
/* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi:
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    // cnt : integer variabel counter kemunculan angka 0
    Index i, j;
    int cnt;

    cnt = 0;

    for(i=0; i<=getLastIdxRow(m); i++)
        for(j=0; j<=getLastIdxCol(m); j++)
            if(ELMT_MATRIX(m, i, j) == 0)
                cnt += 1;

    return ((double)((double)cnt/(double)countElMatrix(m)) > 0.95);
}
Matrix inverse1(Matrix m)
/* Menghasilkan salinan m dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    // temp : Matrix temporary
    Index i, j;
    Matrix temp;

    // ALGORITMA
    CreateMatrix(ROWS(m), COLS(m), &temp);
    copyMatrix(m, &temp);

    for(i=0; i<=getLastIdxRow(temp); i++)
        for(j=0; j<=getLastIdxCol(temp); j++)
            ELMT_MATRIX(temp, i, j) *= (-1);

    return temp;
}
void pInverse1(Matrix *m)
/* I.S. m terdefinisi */
/* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    Index i, j;

    // ALGORITMA
    for(i=0; i<=getLastIdxRow(*m); i++)
        for(j=0; j<=getLastIdxCol(*m); j++)
            ELMT_MATRIX(*m, i, j) *= (-1);
}

float determinant(Matrix m)
/* Prekondisi: isSquare(m) */
/* Menghitung nilai determinan m */
{
    Index i, j, k;
    float total, sign;
    Matrix temp;
    int l, n;

    CreateMatrix(getLastIdxRow(m), getLastIdxCol(m), &temp);

    total = 0;
    sign = 1; // sign multiplier

    if(countElMatrix(m) == 1)
        return ELMT_MATRIX(m, 0, 0);
    else if(countElMatrix(m) == 4)
        return (ELMT_MATRIX(m, 0, 0)*ELMT_MATRIX(m, 1, 1)) - (ELMT_MATRIX(m, 0, 1)*ELMT_MATRIX(m, 1, 0));
    else{
        for(i=0; i<=getLastIdxRow(m); i++){
            l = 0;
            n = 0;
            for(j=1; j<=getLastIdxCol(m); j++)
                for(k=0; k<=getLastIdxRow(m); k++)
                    if(k != i){
                        ELMT_MATRIX(temp, l, n) = ELMT_MATRIX(m, j, k);
                        n += 1;
                        if(n == getLastIdxCol(m)){
                            l += 1;
                            n = 0;
                        }
                    }
            total += ELMT_MATRIX(m, 0, i)*pow(-1, i)*determinant(temp);
        }
        return total;
    }
}

void transpose(Matrix *m)
/* I.S. m terdefinisi dan isSquare(m) */
/* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
{
    // KAMUS
    // i, j : integer (Index) variabel pencacah looping
    // temp : Matrix temporary
    Index i, j;
    Matrix temp;

    // ALGORITMA
    CreateMatrix(ROWS(*m), COLS(*m), &temp);
    copyMatrix(*m, &temp);

    int tempNum = ROWS(*m);
    ROWS(*m) = COLS(*m);
    COLS(*m) = tempNum;

    for(i=0; i<=getLastIdxRow(temp); i++)
        for(j=0; j<=getLastIdxCol(temp); j++)
            ELMT_MATRIX(*m, j, i) = ELMT_MATRIX(temp, i, j);
}

/* Operasi berbasis baris dan per kolom */
float rowMean (Matrix m, Index i)
/* Menghasilkan rata-rata dari elemen pada baris ke-i */
/* Prekondisi: i adalah indeks baris efektif dari M */
{
    Index j;
    ElTypeMatrix sum;

    sum = 0;
    for(j=0; j<=getLastIdxCol(m); j++)
        sum += ELMT_MATRIX(m, i, j);

    return (float)((float)sum/(float)(getLastIdxCol(m)+1));
}
float colMean (Matrix m, Index j)
/* Menghasilkan rata-rata dari elemen pada kolom ke-j */
/* Prekondisi: j adalah indeks kolom efektif dari M */
{
    Index i;
    ElTypeMatrix sum;

    sum = 0;
    for(i=0; i<=getLastIdxRow(m); i++)
        sum += ELMT_MATRIX(m, i, j);

    return (float)((float)sum/(float)(getLastIdxRow(m)+1));
}
void rowExtremes (Matrix m, Index i, ElTypeMatrix * max, ElTypeMatrix * min)
/* I.S. i adalah indeks baris efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada baris i dari M
           min berisi elemen minimum pada baris i dari M */
{
    Index j;

    *max = ELMT_MATRIX(m, i, 0);
    *min = ELMT_MATRIX(m, i, 0);

    for(j=1; j<=getLastIdxCol(m); j++){
        if(ELMT_MATRIX(m, i, j) > *max)
            *max = ELMT_MATRIX(m, i, j);
        if(ELMT_MATRIX(m, i, j) < *min)
            *min = ELMT_MATRIX(m, i, j);
    }
}
void colExtremes (Matrix m, Index j, ElTypeMatrix * max, ElTypeMatrix * min)
/* I.S. j adalah indeks kolom efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada kolom j dari M
           min berisi elemen minimum pada kolom j dari M */
{
    Index i;

    *max = ELMT_MATRIX(m, 0, j);
    *min = ELMT_MATRIX(m, 0, j);

    for(i=1; i<=getLastIdxRow(m); i++){
        if(ELMT_MATRIX(m, i, j) > *max)
            *max = ELMT_MATRIX(m, i, j);
        if(ELMT_MATRIX(m, i, j) < *min)
            *min = ELMT_MATRIX(m, i, j);
    }
}
int countValOnRow (Matrix m, Index i, ElTypeMatrix val)
/* Menghasilkan banyaknya kemunculan X pada baris i dari M */
{
    Index j;
    int cnt;

    for(j=0; j<=getLastIdxCol(m); j++)
        if(ELMT_MATRIX(m, i, j) == val)
            cnt += 1;

    return cnt;
}
int countValOnCol (Matrix m, Index j, ElTypeMatrix val)
/* Menghasilkan banyaknya kemunculan X pada kolom j dari M */
{
    Index i;
    int cnt;

    for(i=0; i<=getLastIdxRow(m); i++)
        if(ELMT_MATRIX(m, i, j) == val)
            cnt += 1;

    return cnt;
}
