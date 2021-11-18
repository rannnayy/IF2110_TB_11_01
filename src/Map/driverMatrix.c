#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main()
{
    Matrix ex1, ex2, ex3;

    CreateMatrix(3, 3, &ex1);
    CreateMatrix(2, 3, &ex2);
    CreateMatrix(3, 3, &ex3);

    printf("Masukkan M1\n");
    readMatrix(&ex1, 3, 3);

    printf("Masukkan M2\n");
    readMatrix(&ex2, 2, 3);
    printf("Masukkan M3\n");
    readMatrix(&ex3, 3, 3);

    printf("%d\n", isIdxValid(50, 50));

    printf("Last col 1: %d\n", getLastIdxCol(ex1));
    printf("Last col 2: %d\n", getLastIdxCol(ex2));
    printf("Last col 3: %d\n", getLastIdxCol(ex3));

    printf("Last row 1: %d\n", getLastIdxRow(ex1));
    printf("Last row 2: %d\n", getLastIdxRow(ex2));
    printf("Last row 3: %d\n", getLastIdxRow(ex3));

    printf("%d\n", isIdxMatrixEff(ex1, 50, 50));

    printf("%d\n", getElmtDiagonal(ex1, 0));

    copyMatrix(ex1, &ex3);

    displayMatrix(ex1);
    printf("\n");
    displayMatrix(ex2);
    printf("\n");
    displayMatrix(ex3);
    printf("\n");

    displayMatrix(addMatrix(ex1, ex3));
    printf("\n");
    displayMatrix(subtractMatrix(ex1, ex3));
    printf("\n");
    displayMatrix(multiplyMatrix(ex1, ex3));
    printf("\n");
    displayMatrix(multiplyConst(ex1, 5));
    printf("\n");

    pMultiplyConst(&ex1, 2);
    displayMatrix(ex1);
    printf("\n");

    printf("%d\n", isMatrixEqual(ex1, ex3));
    printf("%d\n", isMatrixNotEqual(ex1, ex3));
    printf("%d\n", isMatrixSizeEqual(ex1, ex3));

    printf("%d\n", countElMatrix(ex1));

    printf("%d\n", isSquare(ex1));
    printf("%d\n", isSymmetric(ex1));
    printf("%d\n", isIdentity(ex1));

    printf("%d\n", isSparse(ex1));

    printf("Sblm inverse1\n");
    displayMatrix(ex1);
    printf("\n");
    displayMatrix(inverse1(ex1));
    printf("\n");

    printf("Sblm pInverse1\n");
    displayMatrix(ex3);
    printf("\n");
    pInverse1(&ex3);
    displayMatrix(ex3);
    printf("\n");

    printf("%.2f\n", determinant(ex1));

    printf("Sblm transpose\n");
    displayMatrix(ex2);
    printf("\n");
    transpose(&ex2);
    displayMatrix(ex2);
    printf("\n");
}
