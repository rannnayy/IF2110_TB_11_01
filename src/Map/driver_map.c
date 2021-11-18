#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "map.c"
#include "pcolor.c"
#include "matrix.c"
#include "../List/list_linked.c"
#include "../List/node.c"
#include "../List/listdin.c"
#include "point.c"
// Driver Map
// Version 1.0

int main(){
    printf("Apakah (9999,9999) titik valid di map? %d\n", isMapIdxValid(9999, 9999));
    printf("Membuat map yang di contoh spek tubes\n");
    MAP testing;
    int row = 10;
    int col = 15;
    CreateMap(row+2, col+2, &testing);

    //inisialisasi map 
    char temp;
    for(int i = 0; i < row+2; i++){
        for (int j = 0; j < col+2; j++){
            if ((i == 0 || i == row+2-1) ||(j == 0 || j == col+2-1)){
                ELMT_MAP(testing, i, j) = '*';
            } else {
                ELMT_MAP(testing, i, j) = ' ';
            }
        }
    }

    // inisialisasi buildings
    ListDin building;
    CreateListDin(&building, 18);


    POINT tempPoint;
/*      A 10 1    
        B 1 15
        C 1 9
        D 1 13
        E 2 3
        F 3 1
        G 3 8
        H 3 14
        I 4 5
        J 5 12
        K 6 3
        L 7 10
        M 8 2
        N 8 6
        O 8 15
        P 9 13
        Q 10 3 */
    char buildingChar[18] = {'8', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q'};
    int pointX[18] = {1, 10, 1, 1, 1, 2, 3, 3, 3, 4, 5, 6, 7, 8, 8, 8, 9, 10};
    int pointY[18] = {1, 1, 15, 9, 13, 3, 1, 8, 14, 5, 12, 3, 10, 2, 6,15, 13, 3};
    building.nEff = 18;
    for(int i = 0; i < 18; i++){
        tempPoint = MakePOINT(pointX[i], pointY[i]);
        building.buffer[i].buildingChar = buildingChar[i];
        building.buffer[i].buildingPoint = tempPoint;
    }
    // printf("%d\n", length(building));
    // displayList(building);
    for (int i=0; i<length(building); i++){
        ELMT_MAP(testing, Absis(ELMT_POINT(building, i)), Ordinat(ELMT_POINT(building, i))) = ELMT_CHAR(building, i);
    }

    List dummy; CreateList(&dummy); char currentLoc = 'A';
    printf("\nMencetak map 1 (colorless)!\n");
    displayMap(testing);

    MAP map2;
    copyMap(testing, &map2);
    printf("\nMencetak map2 hasil copy map 1!\n");
    displayMap(map2);


    printf("buat map 3x3 kecil! (char tanpa spasi maupun enter)\n");
    MAP map3; 
    readMap(&map3, 3, 3);
    displayMap(map3);

    printf("location code untuk A? %d\n",  getLocationCode(currentLoc, building));
    
    // is Accesible butuh adjacency matrix

    printf("menggunakan dummy (NULL), apakah ada yg bisa dipickup dan didropoff? %d %d\n", isPickUp(dummy, currentLoc), isDropOff(dummy, currentLoc));
    
    //colored loc dan map tidak bisa dijalankan di saya sayangnya, kurang tau mengapa

    return 0;
}