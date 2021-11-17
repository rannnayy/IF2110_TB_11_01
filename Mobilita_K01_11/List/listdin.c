/*
    NIM             : 13520019
    Nama            : Maharani Ayu Putri Irawan
    Tanggal         : 14/9/2021
    Topik praktikum : ADT List Dinamik
    Deskripsi       : Membuat implementasi ADT list dengan representasi eksplisit dan alokasi dinamik.
*/

#include <stdio.h>
#include <stdlib.h>
#include "listdin.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDin(ListDin *l, int capacity)
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */
{
    // KAMUS LOKAL
    // ALGORITMA
    CAPACITY_LISTDIN(*l) = capacity;
    NEFF(*l) = 0;
    BUFFER(*l) = (ElTypeListDin*) malloc(capacity * sizeof(ElTypeListDin));
}
void dealocate(ListDin *l)
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */
{
    // KAMUS LOKAL
    // ALGORITMA
    CAPACITY_LISTDIN(*l) = 0;
    NEFF(*l) = 0;
    free(BUFFER(*l));
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int length(ListDin l)
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */
/* *** Daya tampung container *** */
{
    // KAMUS LOKAL
    // ALGORITMA
    return NEFF(l);
}
/* *** Selektor INDEKS *** */
IdxType getLastIdx(ListDin l)
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
{
    // KAMUS LOKAL
    // ALGORITMA
    return (NEFF(l)-1);
}
/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListDin l, int i)
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    // KAMUS LOKAL
    // ALGORITMA
    return (i>=0 && (i<=CAPACITY_LISTDIN(l)-1));
}
boolean isListDinIdxEff(ListDin l, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..NEFF(l) */
{
    // KAMUS LOKAL
    // ALGORITMA
    return (i>=0 && i<=NEFF(l)-1);
}
/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmpty(ListDin l)
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
{
    // KAMUS LOKAL
    // ALGORITMA
    return(length(l) == 0);
}
/* *** Test list penuh *** */
boolean isFull(ListDin l)
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
{
    // KAMUS LOKAL
    // ALGORITMA
    return(length(l) == CAPACITY_LISTDIN(l));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi list dari pembacaan *** */
void readList(ListDin *l)
/* I.S. l sembarang dan sudah dialokasikan sebelumnya */
/* F.S. List l terdefinisi */
/* Proses : membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= CAPACITY(l) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
      0 satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk l kosong */
{
    // KAMUS LOKAL
    // n : integer banyaknya elemen
    // i : integer variabel pencacah looping
    int n, i;
    // ALGORITMA
    do{
        scanf("%d", &n);
    }
    while (!(n>=0 && n<=CAPACITY_LISTDIN(*l)));

    NEFF(*l) = n;
    if(n > 0)
        for(i=0; i<n; i++){
            scanf("%c", &ELMT_CHAR(*l, i));
            BacaPOINT(&ELMT_POINT(*l, i));
        }
}
void displayList(ListDin l)
/* Proses : Menuliskan isi list dengan traversal, list ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
{
    // KAMUS LOKAL
    // i : integer variabel pencacah looping
    int i;

    // ALGORITMA
    printf("[");
    if(length(l) > 0){
        for(i=0; i<length(l); i++){
            printf("%c", ELMT_CHAR(l, i));
            TulisPOINT(ELMT_POINT(l, i));
            if(i < length(l)-1)
                printf(",");
        }
    }
    printf("]");
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika list : Penjumlahan, pengurangan, perkalian, ... *** */
//ListDin plusMinusList(ListDin l1, ListDin l2, boolean plus)
/* Prekondisi : l1 dan l2 memiliki Neff sama dan tidak kosong */
/* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi elemen l2 pada indeks yang sama */
/*
{
    // KAMUS LOKAL
    // i : integer variabel pencacah looping
    // l : ListDin menyimpan hasil penjumlahan/pengurangan
    int i;
    ListDin l;

    //ALGORITMA
    CreateListDin(&l, CAPACITY(l1));
    NEFF(l) = NEFF(l1);

    if(plus)
        for(i=0; i<length(l1); i++)
            ELMT(l, i) = ELMT(l1, i) + ELMT(l2, i);
    else
        for(i=0; i<length(l1); i++)
            ELMT(l, i) = ELMT(l1, i) - ELMT(l2, i);

    return l;
}
*/
/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan list : < =, > *** */
boolean isListEqual(ListDin l1, ListDin l2)
/* Mengirimkan true jika l1 sama dengan l2 yaitu jika nEff l1 = l2 dan semua elemennya sama */
{
    // KAMUS LOKAL
    // i : integer variabel pencacah looping
    // eq : boolean True jika equal, False jika sebaliknya
    int i;
    boolean eq;

    // ALGORITMA
    eq = true;
    if(length(l1) == length(l2)){
        i = 0;
        while(i<length(l1) && eq){
            if((ELMT_CHAR(l1, i) != ELMT_CHAR(l2, i)) || NEQ(ELMT_POINT(l1, i), ELMT_POINT(l2, i)))
                eq = false;
            else
                i += 1;
        }
    }
    else
        eq = false;

    return eq;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOf(ListDin l, char val)
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
/* Jika tidak ada, mengirimkan IDX_UNDEF */
/* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
/* Skema Searching yang digunakan bebas */
{
    // KAMUS LOKAL
    // i : integer variabel pencacah looping
    // idx : integer penyimpan indeks pertama ditemukannya val pada ListDin
    int i;
    IdxType idx;

    // ALGORITMA
    idx = IDX_UNDEF;
    if(length(l) > 0){
        i = 0;
        while(i < length(l) && idx == IDX_UNDEF)
            if(ELMT_CHAR(l, i) == val)
                idx = i;
            else
                i += 1;
    }

    return idx;
}

/* ********** NILAI EKSTREM ********** */
//void extremes(ListDin l, ElType *max, ElType *min)
/* I.S. List l tidak kosong */
/* F.S. max berisi nilai maksimum l;
        min berisi nilai minimum l */
/*
{
    // KAMUS LOKAL
    // i : integer variabel pencacah looping
    int i;

    // ALGORITMA
    *max = ELMT(l, 0);
    *min = ELMT(l, 0);

    for(i=1; i<length(l); i++){
        if(ELMT(l, i) > *max)
            *max = ELMT(l, i);
        if(ELMT(l, i) < *min)
            *min = ELMT(l, i);
    }
}
*/

/* ********** OPERASI LAIN ********** */
void copyList(ListDin lIn, ListDin *lOut)
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */
{
    // KAMUS LOKAL
    // i : integer variabel pencacah looping
    int i;

    // ALGORITMA
    CreateListDin(&(*lOut), CAPACITY_LISTDIN(lIn));
    NEFF(*lOut) = NEFF(lIn);
    for(i=0; i<length(lIn); i++){
        ELMT_CHAR(*lOut, i) = ELMT_CHAR(lIn, i);
        Absis(ELMT_POINT(*lOut, i)) = Absis(ELMT_POINT(lIn, i));
        Ordinat(ELMT_POINT(*lOut, i)) = Ordinat(ELMT_POINT(lIn, i));
    }
}
//ElType sumList(ListDin l)
/* Menghasilkan hasil penjumlahan semua elemen l */
/* Jika l kosong menghasilkan 0 */
/*
{
    // KAMUS LOKAL
    // i : integer variabel pencacah looping
    // ans : ElType, dalam hal ini integer, menyimpan hasil penjumlahan semua elemen l
    int i;
    ElType ans;

    // ALGORITMA
    ans = 0;
    if(length(l) > 0)
        for(i=0; i<length(l); i++)
            ans += ELMT(l, i);

    return ans;
}
*/
int countVal(ListDin l, char val)
/* Menghasilkan berapa banyak kemunculan val di l */
/* Jika l kosong menghasilkan 0 */
{
    // KAMUS LOKAL
    // i : integer variabel pencacah looping
    // cnt : integer variabel penghitung
    int i, cnt;

    // ALGORITMA
    cnt = 0;
    if(length(l) > 0)
        for(i=0; i<length(l); i++)
            if(ELMT_CHAR(l, i) == val)
                cnt += 1;

    return cnt;
}
//boolean isAllEven(ListDin l)
/* Menghailkan true jika semua elemen l genap. l boleh kosong */
/*
{
    // KAMUS LOKAL
    // i : integer variabel pencacah looping
    // even : boolean True jika genap, False jika ganjil
    int i;
    boolean even;

    // ALGORITMA
    even = true;
    i = 0;
    if(length(l) > 0)
        while(i<length(l) && even){
            if(ELMT(l, i)%2 == 1)
                even = false;
            else
                i += 1;
        }

    return even;
}
*/

/* ********** SORTING ********** */
void sort(ListDin *l, boolean asc)
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */
{
    // KAMUS LOKAL
    // n : integer variabel penyimpan length
    // i, j : integer variabel pencacah looping
    // idx : integer index pivot
    // temp : ElType, dalam hal ini integer, menyimpan nilai sementara untuk swap 2 nilai ListDin
    int n, i, j, idx;
    ElTypeListDin temp;

    // ALGORITMA
    n = length(*l);
    // Selection Sort
    if(n>1){
        if(asc){ //membesar
            for(i=0; i<n-1; i++){
                idx = i;
                for(j=i+1; j<n; j++)
                    if((int)ELMT_CHAR(*l, idx) > (int)ELMT_CHAR(*l, j))
                        idx = j;
                //Swap
                temp.buildingChar = ELMT_CHAR(*l, i);
                Absis(temp.buildingPoint) = Absis(ELMT_POINT(*l, i));
                Ordinat(temp.buildingPoint) = Ordinat(ELMT_POINT(*l, i));

                ELMT_CHAR(*l, i) = ELMT_CHAR(*l, idx);
                Absis(ELMT_POINT(*l, i)) = Absis(ELMT_POINT(*l, idx));
                Ordinat(ELMT_POINT(*l, i)) = Ordinat(ELMT_POINT(*l, idx));

                ELMT_CHAR(*l, idx) = temp.buildingChar;
                Absis(ELMT_POINT(*l, idx)) = Absis(temp.buildingPoint);
                Ordinat(ELMT_POINT(*l, idx)) = Ordinat(temp.buildingPoint);
            }
        }
        else{ //mengecil
            for(i=0; i<n-1; i++){
                idx = i;
                for(j=i+1; j<n; j++)
                    if((int)ELMT_CHAR(*l, idx) < (int)ELMT_CHAR(*l, j))
                        idx = j;
                //Swap
                temp.buildingChar = ELMT_CHAR(*l, i);
                Absis(temp.buildingPoint) = Absis(ELMT_POINT(*l, i));
                Ordinat(temp.buildingPoint) = Ordinat(ELMT_POINT(*l, i));

                ELMT_CHAR(*l, i) = ELMT_CHAR(*l, idx);
                Absis(ELMT_POINT(*l, i)) = Absis(ELMT_POINT(*l, idx));
                Ordinat(ELMT_POINT(*l, i)) = Ordinat(ELMT_POINT(*l, idx));

                ELMT_CHAR(*l, idx) = temp.buildingChar;
                Absis(ELMT_POINT(*l, idx)) = Absis(temp.buildingPoint);
                Ordinat(ELMT_POINT(*l, idx)) = Ordinat(temp.buildingPoint);
            }
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListDin *l, ElTypeListDin val)
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
{
    // KAMUS
    // ALGORITMA
    ELMT_CHAR(*l, length(*l)) = val.buildingChar;
    Absis(ELMT_POINT(*l, length(*l))) = Absis(val.buildingPoint);
    Ordinat(ELMT_POINT(*l, length(*l))) = Ordinat(val.buildingPoint);
    NEFF(*l) += 1;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListDin *l, ElTypeListDin *val)
/* Proses : Menghapus elemen terakhir list */
/* I.S. List lidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */
{
    // KAMUS
    // ALGORITMA
    (*val).buildingChar = ELMT_CHAR(*l, length(*l)-1);
    Absis((*val).buildingPoint) = Absis(ELMT_POINT(*l, length(*l)-1));
    Ordinat((*val).buildingPoint) = Ordinat(ELMT_POINT(*l, length(*l)-1));
    NEFF(*l) -= 1;
}

/* ********* MENGUBAH UKURAN ARRAY ********* */
void growList(ListDin *l, int num)
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */
{
    //BUFFER(*l) = realloc(BUFFER(*l), sizeof(ElType) * (CAPACITY(*l)+num));
    // KAMUS LOKAL
    // i : integer variabel pencacah looping
    // temp : ListDin sementara untuk copy nilai ListDin *l untuk di assign lagi nilainya ke ListDin *l baru yang telah memiliki CAPACITY yang diinginkan
    ListDin temp;
    int i;

    // ALGORITMA
    copyList(*l, &temp);
    dealocate(&(*l));
    CreateListDin(&(*l), CAPACITY_LISTDIN(temp)+num);
    NEFF(*l) = NEFF(temp);
    for(i=0; i<length(temp); i++){
        ELMT_CHAR(*l, i) = ELMT_CHAR(temp, i);
        Absis(ELMT_POINT(*l, i)) = Absis(ELMT_POINT(temp, i));
        Ordinat(ELMT_POINT(*l, i)) = Ordinat(ELMT_POINT(temp, i));
    }
    dealocate(&temp);
}
void shrinkList(ListDin *l, int num)
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */
{
    //BUFFER(*l) = (ElType*) realloc(BUFFER(*l), sizeof(ElType) * (CAPACITY(*l)-num));
    // KAMUS LOKAL
    // i : integer variabel pencacah looping
    // temp : ListDin sementara untuk copy nilai ListDin *l untuk di assign lagi nilainya ke ListDin *l baru yang telah memiliki CAPACITY yang diinginkan
    ListDin temp;
    int i;

    // ALGORITMA
    copyList(*l, &temp);
    dealocate(&(*l));
    CreateListDin(&(*l), CAPACITY_LISTDIN(temp)-num);
    if(CAPACITY_LISTDIN(*l)<NEFF(temp))
        NEFF(*l) = CAPACITY_LISTDIN(*l);
    else
        NEFF(*l) = NEFF(temp);
    for(i=0; i<length(*l); i++){
        ELMT_CHAR(*l, i) = ELMT_CHAR(temp, i);
        Absis(ELMT_POINT(*l, i)) = Absis(ELMT_POINT(temp, i));
        Ordinat(ELMT_POINT(*l, i)) = Ordinat(ELMT_POINT(temp, i));
    }
    dealocate(&temp);
}
void compactList(ListDin *l)
/* Proses : Mengurangi capacity sehingga nEff = capacity */
/* I.S. List lidak kosong */
/* F.S. Ukuran nEff = capacity */
{
    //BUFFER(*l) = (ElType*) realloc(BUFFER(*l), sizeof(ElType) * NEFF(*l));
    // KAMUS LOKAL
    // i : integer variabel pencacah looping
    // temp : ListDin sementara untuk copy nilai ListDin *l untuk di assign lagi nilainya ke ListDin *l baru yang telah memiliki CAPACITY yang diinginkan
    ListDin temp;
    int i;

    // ALGORITMA
    copyList(*l, &temp);
    dealocate(&(*l));
    CreateListDin(&(*l), NEFF(temp));
    NEFF(*l) = NEFF(temp);
    for(i=0; i<length(temp); i++){
        ELMT_CHAR(*l, i) = ELMT_CHAR(temp, i);
        Absis(ELMT_POINT(*l, i)) = Absis(ELMT_POINT(temp, i));
        Ordinat(ELMT_POINT(*l, i)) = Ordinat(ELMT_POINT(temp, i));
    }
    dealocate(&temp);
}

