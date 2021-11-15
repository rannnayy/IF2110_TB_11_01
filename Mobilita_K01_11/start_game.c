/********* START GAME *********/
/*
    File Name   : start_game.c
    Author      : K01_11
    Last Update : 10/11/2021
    Description : Function to start Mobilita game implementations, including load and read file as well as store in variables
                  and various data structures.
*/

#include <stdio.h>
#include <stdlib.h>
#include "start_game.h"
// #include "pcolor.h"

FILE* writeFile;

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
    printf("Masukkan nama file: ");
    startWordConsole();

    char filename[FILENAME_MAX];
    for(int i = 0; i < currentWord.length; i++)
        filename[i] = currentWord.contents[i];
    //memset(&filename, '\0', sizeof(filename));
    for(int i = currentWord.length; i < FILENAME_MAX; i++)
        filename[i] = '\0';
    //memcpy(filename, currentWord.contents, currentWord.length);
    int lenBefore = currentWord.length;

    // Start file reading
    boolean started;
    startWordFile(filename, &started);
    while(!started){
        printf("File %s tidak tersedia\n", filename);
        printf("Masukkan nama file: ");

        startWordConsole();
        if(lenBefore > currentWord.length)
            for(int i = 0; i < lenBefore; i++)
                if(i < currentWord.length)
                    filename[i] = currentWord.contents[i];
                else
                    filename[i] = '\0';
        else
            for(int i = 0; i < currentWord.length; i++)
                filename[i] = currentWord.contents[i];

        startWordFile(filename, &started);
        lenBefore = currentWord.length;
    }
    processFileRead();
    ignoreBlankFile();

    //printf("\n");
    *N = 0;
    *M = 0;
    // Assign N (number of rows)
    DigitsToInt(currentWordFile, &(*N));

    advWordFile();
    // Assign M (number of columns)
    DigitsToInt(currentWordFile, &(*M));

    // printf("%d %d\n", *N, *M);

    int x, y;
    x = 0;
    y = 0;
    // Assign POINT headQuarter
    advWordFile();
    // Assign x of POINT headQuarter
    DigitsToInt(currentWordFile, &x);

    advWordFile();
    // Assign y of POINT headQuarter
    DigitsToInt(currentWordFile, &y);

    // Make POINT headQuarter
    *headQuarter = MakePOINT(x, y);

    // TulisPOINT(*headQuarter);
    // printf("\n");

    *nLoc = 0;
    advWordFile();
    // Assign nLoc (number of locations)
    DigitsToInt(currentWordFile, &(*nLoc));

    // printf("%d\n", *nLoc);

    int i;
    CreateListDin(&(*building), *nLoc);
    NEFF(*building) = *nLoc;
    for(i = 0; i < *nLoc; i++){
        x = 0;
        y = 0;
        // Store Building Character (Assumption: number of buildings max 26)
        advWordFile();
        ELMT_CHAR(*building, i) = currentWordFile.contents[0];

        // Store Building Point, each for x and y
        advWordFile();
        DigitsToInt(currentWordFile, &x);
        advWordFile();
        DigitsToInt(currentWordFile, &y);

        ELMT_POINT(*building, i) = MakePOINT(x, y);

    }
    // displayList(*building);
    // printf("\n");

    int j;
    // Store Adjacency Matrix
    CreateMatrix((*nLoc)+1, (*nLoc)+1, &(*adjMatrix));
    for(i = 0; i < (*nLoc)+1; i++){
        for(j = 0; j < (*nLoc)+1; j++){
            advWordFile();
            ELMT_MATRIX(*adjMatrix, i, j) = (int)(currentWordFile.contents[0] - 48);
        }
    }
    // displayMatrix(*adjMatrix);
    // printf("\n");

    *nOrder = 0;
    advWordFile();
    // Assign nOrder (number of Orders)
    DigitsToInt(currentWordFile, &(*nOrder));

    // printf("%d\n", *nOrder);

    CreateList(&(*orders));
    Elements ordEl;
    for(i = 0; i < (*nOrder); i++){
        // Store ordEl.nTime
        advWordFile();
        NTIME(ordEl) = 0;
        DigitsToInt(currentWordFile, &NTIME(ordEl));
        // Store ordEl.pickUp
        advWordFile();
        PICKUP(ordEl) = (char)currentWordFile.contents[0];
        // Store ordEl.dropOff
        advWordFile();
        DROPOFF(ordEl) = (char)currentWordFile.contents[0];
        // Store ordEl.itemType
        advWordFile();
        ITEMTYPE(ordEl) = (char)currentWordFile.contents[0];
        // Store ordEl.perish
        if (ITEMTYPE(ordEl) == 'P'){
            advWordFile();
            PERISH(ordEl) = 0;
            DigitsToInt(currentWordFile, &PERISH(ordEl));
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

void LoadGame(int* N, int* M, int* nLoc, int* nOrder, POINT* headQuarter, ListDin* building, Matrix* adjMatrix, List* orders,
              PrioQueue* orderedOrders, char* current_loc, int* current_time, int* current_money, int* current_bagcapacity,
              int* nToDoList, List* toDoList, int* nInProgress, List* inProgress, int* nInventory, ListPos* inventory)
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
    printf("Masukkan nama file: ");
    startWordConsole();

    char filename[FILENAME_MAX];
    for(int i = 0; i < currentWord.length; i++)
        filename[i] = currentWord.contents[i];
    for(int i = currentWord.length; i < FILENAME_MAX; i++)
        filename[i] = '\0';
    int lenBefore = currentWord.length;

    // Start file reading
    boolean started;
    startWordFile(filename, &started);
    while(!started){
        printf("File %s tidak tersedia\n", filename);
        printf("Masukkan nama file: ");

        startWordConsole();
        if(lenBefore > currentWord.length)
            for(int i = 0; i < lenBefore; i++)
                if(i < currentWord.length)
                    filename[i] = currentWord.contents[i];
                else
                    filename[i] = '\0';
        else
            for(int i = 0; i < currentWord.length; i++)
                filename[i] = currentWord.contents[i];

        startWordFile(filename, &started);
        lenBefore = currentWord.length;
    }
    processFileRead();
    ignoreBlankFile();

    //printf("\n");
    *N = 0;
    *M = 0;
    // Assign N (number of rows)
    DigitsToInt(currentWordFile, &(*N));

    advWordFile();
    // Assign M (number of columns)
    DigitsToInt(currentWordFile, &(*M));

    // printf("%d %d\n", *N, *M);

    int x, y;
    x = 0;
    y = 0;
    // Assign POINT headQuarter
    advWordFile();
    // Assign x of POINT headQuarter
    DigitsToInt(currentWordFile, &x);

    advWordFile();
    // Assign y of POINT headQuarter
    DigitsToInt(currentWordFile, &y);

    // Make POINT headQuarter
    *headQuarter = MakePOINT(x, y);

    // TulisPOINT(*headQuarter);
    // printf("\n");

    *nLoc = 0;
    advWordFile();
    // Assign nLoc (number of locations)
    DigitsToInt(currentWordFile, &(*nLoc));

    // printf("%d\n", *nLoc);

    int i;
    CreateListDin(&(*building), *nLoc);
    NEFF(*building) = *nLoc;
    for(i = 0; i < *nLoc; i++){
        x = 0;
        y = 0;
        // Store Building Character (Assumption: number of buildings max 26)
        advWordFile();
        ELMT_CHAR(*building, i) = currentWordFile.contents[0];

        // Store Building Point, each for x and y
        advWordFile();
        DigitsToInt(currentWordFile, &x);
        advWordFile();
        DigitsToInt(currentWordFile, &y);

        ELMT_POINT(*building, i) = MakePOINT(x, y);

    }
    // displayList(*building);
    // printf("\n");

    int j;
    // Store Adjacency Matrix
    CreateMatrix((*nLoc)+1, (*nLoc)+1, &(*adjMatrix));
    for(i = 0; i < (*nLoc)+1; i++){
        for(j = 0; j < (*nLoc)+1; j++){
            advWordFile();
            ELMT_MATRIX(*adjMatrix, i, j) = (int)(currentWordFile.contents[0] - 48);
        }
    }
    // displayMatrix(*adjMatrix);
    // printf("\n");

    *nOrder = 0;
    advWordFile();
    // Assign nOrder (number of Orders)
    DigitsToInt(currentWordFile, &(*nOrder));

    // printf("%d\n", *nOrder);

    CreateList(&(*orders));
    Elements ordEl;
    for(i = 0; i < (*nOrder); i++){
        // Store ordEl.nTime
        advWordFile();
        NTIME(ordEl) = 0;
        DigitsToInt(currentWordFile, &NTIME(ordEl));
        // Store ordEl.pickUp
        advWordFile();
        PICKUP(ordEl) = (char)currentWordFile.contents[0];
        // Store ordEl.dropOff
        advWordFile();
        DROPOFF(ordEl) = (char)currentWordFile.contents[0];
        // Store ordEl.itemType
        advWordFile();
        ITEMTYPE(ordEl) = (char)currentWordFile.contents[0];
        // Store ordEl.perish
        if (ITEMTYPE(ordEl) == 'P'){
            advWordFile();
            PERISH(ordEl) = 0;
            DigitsToInt(currentWordFile, &PERISH(ordEl));
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
    pqEls pqEl;
    for(i = 0; i < (*nOrder); i++){
        advWordFile();
        NTIME(pqEl) = 0;
        DigitsToInt(currentWordFile, &NTIME(pqEl));

        advWordFile();
        PICKUP(pqEl) = (char)currentWordFile.contents[0];

        advWordFile();
        DROPOFF(pqEl) = (char)currentWordFile.contents[0];

        advWordFile();
        ITEMTYPE(pqEl) = (char)currentWordFile.contents[0];

        if (ITEMTYPE(pqEl) == 'P'){
            advWordFile();
            PERISH(pqEl) = 0;
            DigitsToInt(currentWordFile, &PERISH(pqEl));
        }
        else
            PERISH(pqEl) = -1;

        // Store Elements in Linked List
        enqueue(&(*orderedOrders), pqEl);
    }

    advWordFile();
    // Assign current_loc (last current location)
    *current_loc = (char)currentWordFile.contents[0];
    //printf("%c\n", *current_loc);

    *current_time = 0;
    advWordFile();
    // Assign current_time (last current time)
    DigitsToInt(currentWordFile, &(*current_time));
    //printf("%d\n", *current_time);

    *current_time = 0;
    advWordFile();
    // Assign current_money (last current money)
    DigitsToInt(currentWordFile, &(*current_money));
    //printf("%d\n", *current_money);

    *current_time = 0;
    advWordFile();
    // Assign current_bagcapacity (last current bag capacity)
    DigitsToInt(currentWordFile, &(*current_bagcapacity));
    //printf("%d\n", *current_bagcapacity);

    *nToDoList = 0;
    advWordFile();
    DigitsToInt(currentWordFile, &(*nToDoList));
    //printf("%d\n", *nToDoList);

    CreateList(&(*toDoList));
    Elements tdlEl;
    for(i = 0; i < (*nToDoList); i++){
        advWordFile();
        NTIME(tdlEl) = 0;
        DigitsToInt(currentWordFile, &NTIME(tdlEl));

        advWordFile();
        PICKUP(tdlEl) = (char)currentWordFile.contents[0];

        advWordFile();
        DROPOFF(tdlEl) = (char)currentWordFile.contents[0];

        advWordFile();
        ITEMTYPE(tdlEl) = (char)currentWordFile.contents[0];

        if (ITEMTYPE(tdlEl) == 'P'){
            advWordFile();
            PERISH(tdlEl) = 0;
            DigitsToInt(currentWordFile, &PERISH(tdlEl));
        }
        else
            PERISH(tdlEl) = -1;

        // Store Elements in Linked List
        insertLinkedListLast(&(*toDoList), tdlEl);
    }
    //displayLinkedList(*toDoList);
    //printf("\n");

    *nInProgress = 0;
    advWordFile();
    DigitsToInt(currentWordFile, &(*nInProgress));
    //printf("%d\n", *nInProgress);

    CreateList(&(*inProgress));
    Elements ipEl;
    for(i = 0; i < (*nInProgress); i++){
        advWordFile();
        NTIME(ipEl) = 0;
        DigitsToInt(currentWordFile, &NTIME(ipEl));

        advWordFile();
        PICKUP(ipEl) = (char)currentWordFile.contents[0];

        advWordFile();
        DROPOFF(ipEl) = (char)currentWordFile.contents[0];

        advWordFile();
        ITEMTYPE(ipEl) = (char)currentWordFile.contents[0];

        if (ITEMTYPE(ipEl) == 'P'){
            advWordFile();
            PERISH(ipEl) = 0;
            DigitsToInt(currentWordFile, &PERISH(ipEl));
        }
        else
            PERISH(ipEl) = -1;

        // Store Elements in Linked List
        insertLinkedListLast(&(*inProgress), ipEl);
    }
    //displayLinkedList(*inProgress);
    //printf("\n");

    *nInventory = 0;
    advWordFile();
    DigitsToInt(currentWordFile, &(*nInventory));
    //printf("%d\n", *nInventory);

    int temp;
    CreateListPos(&(*inventory));
    for(i = 0; i < (*nInventory); i++){
        temp = 0;
        advWordFile();
        DigitsToInt(currentWordFile, &(temp));
        insertLast_ListPos(&(*inventory), temp);
    }
    //displayList_ListPos(*inventory);
    //printf("\n");
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

void Help()
{
    printf(" /$$   /$$ /$$$$$$$$ /$$       /$$$$$$$\n");
    printf("| $$  | $$| $$_____/| $$      | $$__  $$\n");
    printf("| $$  | $$| $$      | $$      | $$  \\ $$\n");
    printf("| $$$$$$$$| $$$$$   | $$      | $$$$$$$/\n");
    printf("| $$__  $$| $$__/   | $$      | $$____/\n");
    printf("| $$  | $$| $$      | $$      | $$\n");
    printf("| $$  | $$| $$$$$$$$| $$$$$$$$| $$\n");
    printf("|__/  |__/|________/|________/|__/\n");

    printf("COMMANDS\n");
    printf("1. New Game\n");
    printf("    Ketik NEW_GAME untuk memulai permainan baru.\n");

    printf("2. Load Game\n");
    printf("    Ketik LOAD_GAME untuk melanjutkan permainan yang telah tersimpan.\n");

    printf("3. Exit\n");
    printf("    Ketik EXIT untuk keluar dari permainan.\n");

    printf("4. Waktu\n");
    printf("    Ketik TIME untuk menunjukkan waktu permainan saat ini.\n");

    printf("5. Daftar Pesanan\n");
    printf("    Ketik ORDER untuk menunjukkan daftar pesanan.\n");

    printf("6. To Do List\n");
    printf("    Ketik TO_DO untuk menunjukkan To Do List.\n");

    printf("7. In Progress List\n");
    printf("    Ketik IN_PROGRESS untuk menunjukkan In Progress List.\n");

    printf("8. Kapasitas Tas\n");
    printf("    Ketik BAG untuk menunjukkan kapasitas tas saat ini.\n");

    printf("9. Jenis Item\n");
    printf("    Ketik ITEM untuk menunjukkan jenis item yang tersedia.\n");

    printf("10. Ability Aktif\n");
    printf("    Ketik ACTIVE_ABILITY untuk melihat ability yang sedang aktif.\n");

    printf("11. Gadget\n");
    printf("    Ketik GADGET untuk menujukkan daftar gadget yang tersedia.\n");

    printf("12. Gadget Aktif\n");
    printf("    Ketik ACTIVE_GADGET untuk melihat gadget yang sedang aktif.\n");

    printf("13. Daftar Inventory\n");
    printf("    Ketik INVENTORY untuk menunjukkan daftar inventory yang tersedia.\n");

    printf("14. Map\n");
    printf("    Ketik MAP untuk menunjukkan peta permainan saat ini.\n");

    printf("15. Move\n");
    printf("    Ketik MOVE untuk menunjukkan lokasi-lokasi yang dapat disinggahi.\n    Lalu, silahkan memilih angka yang hendak dituju.\n");

    printf("16. Pick Up\n");
    printf("    Ketik PICK_UP untuk mengambil item jika ada pesanan yang harus diambil pada lokasi.\n");

    printf("17. Drop Off\n");
    printf("    Ketik DROP_OFF untuk mengantarkan item ke lokasi jika item di tumpukan teratas tas sesuai dengan pesanan\n");

    printf("18. Buy\n");
    printf("    Ketik BUY pada posisi Headquarters untuk menampilkan gadget yang dapat dibeli lalu membelinya.\n    Setelah muncul daftar gadget, silahkan masukkan angka gadget yang hendak dibeli.\n");
}

void SaveGame(int N, int M, int nLoc, int nOrder, POINT headQuarter, ListDin building, Matrix adjMatrix, List orders,
              PrioQueue orderedOrders, char current_loc, int current_time, int current_money, int current_bagcapacity,
              int nToDoList, List toDoList, int nInProgress, List inProgress, int nInventory, ListPos inventory)
{
    char out_filename[FILENAME_MAX];

    printf("Masukkan nama file penyimpanan: ");
    startWordConsole();

    for(int i = 0; i < currentWord.length; i++)
        out_filename[i] = currentWord.contents[i];
    for(int i = currentWord.length; i < FILENAME_MAX; i++)
        out_filename[i] = '\0';
    int lenBefore = currentWord.length;

    // If file of name out_filename existed, the content will be overwritten, else will make new file and fill it
    writeFile = fopen(out_filename, "w");
    if(writeFile != NULL){
        printf("Disimpan dalam file %s\n", out_filename);
        rewind(writeFile);

        fprintf(writeFile, "%d %d\n", N, M);
        fprintf(writeFile, "%d %d\n", Absis(headQuarter), Ordinat(headQuarter));
        fprintf(writeFile, "%d\n", nLoc);
        for(int i = 0; i < nLoc; i++)
            fprintf(writeFile, "%c %d %d\n", ELMT_CHAR(building, i), Absis(ELMT_POINT(building, i)), Ordinat(ELMT_POINT(building, i)));
        for(int i = 0; i < nLoc+1; i++){
            for(int j = 0; j < nLoc+1; j++){
                fprintf(writeFile, "%d", ELMT_MATRIX(adjMatrix, i, j));
                if(j < nLoc)
                    fprintf(writeFile, " ");
            }
            fprintf(writeFile, "\n");
        }

        Address p = FIRST(orders);
        fprintf(writeFile, "%d\n", nOrder);
        for(int i = 0; i < nOrder; i++){
            fprintf(writeFile, "%d %c %c %c %d\n", NTIME(INFO(p)), PICKUP(INFO(p)), DROPOFF(INFO(p)), ITEMTYPE(INFO(p)), PERISH(INFO(p)));
            p = NEXT(p);
        }

        for(int i = 0; i < nOrder; i++){
            pqEls tempPQ;
            dequeue(&orderedOrders, &tempPQ);
            fprintf(writeFile, "%d %c %c %c %d\n", NTIME(tempPQ), PICKUP(tempPQ), DROPOFF(tempPQ), ITEMTYPE(tempPQ), PERISH(tempPQ));
        }
        // Baca array orderedOrders.buffer[IDX_HEAD] -- orderedOrders.buffer[IDX_TAIL]

        fprintf(writeFile, "%c\n", current_loc);
        fprintf(writeFile, "%d\n", current_time);
        fprintf(writeFile, "%d\n", current_money);
        fprintf(writeFile, "%d\n", current_bagcapacity);
        fprintf(writeFile, "%d\n", nToDoList);

        p = FIRST(toDoList);
        for(int i = 0; i < nToDoList; i++){
            fprintf(writeFile, "%d %c %c %c %d\n", NTIME(INFO(p)), PICKUP(INFO(p)), DROPOFF(INFO(p)), ITEMTYPE(INFO(p)), PERISH(INFO(p)));
            p = NEXT(p);
        }

        fprintf(writeFile, "%d\n", nInProgress);

        p = FIRST(inProgress);
        for(int i = 0; i < nInProgress; i++){
            if(PERISH(INFO(p)) == -1)
                fprintf(writeFile, "%d %c %c %c\n", NTIME(INFO(p)), PICKUP(INFO(p)), DROPOFF(INFO(p)), ITEMTYPE(INFO(p)));
            else
                fprintf(writeFile, "%d %c %c %c %d\n", NTIME(INFO(p)), PICKUP(INFO(p)), DROPOFF(INFO(p)), ITEMTYPE(INFO(p)), PERISH(INFO(p)));
            p = NEXT(p);
        }

        fprintf(writeFile, "%d\n", nInventory);
        for(int i = 0; i < nInventory; i++){
            fprintf(writeFile, "%d", ELMT_LISTPOS(inventory, i));
            if(i < nInventory-1)
                fprintf(writeFile, "\n");
        }

        fclose(writeFile);
    }
    else
        printf("Tidak bisa menyimpan ke file.");
}
