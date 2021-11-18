#include <stdio.h>
#include "point.h"

int main()
{
    // KAMUS LOKAL
    /*
        exPoint1 : POINT
        exPoint2 : POINT
        x : Integer
        y : Integer
        dX : Integer
        dY : Integer
        sudut : Float
    */
    POINT exPoint1, exPoint2;
    int x, y, dX, dY;
    float sudut;

    // ALGORITMA
    printf("Masukkan 2 titik (Format : X Y) : \n");
    scanf("%d %d", &x, &y);
    printf("1. MakePOINT(%d,%d) -> exPoint1\n", x, y);
    exPoint1 = MakePOINT(x,y);
    TulisPOINT(exPoint1);
    printf("\n");

    printf("2. BacaPOINT() : -> exPoint2\n");
    BacaPOINT(&exPoint2);
    TulisPOINT(exPoint2);
    printf("\n");

    printf("3. EQ(exPoint1, exPoint2) : %u\n\n", EQ(exPoint1, exPoint2));

    printf("4. NEQ(exPoint1, exPoint2) : %u\n\n", NEQ(exPoint1, exPoint2));

    printf("5. IsOrigin(exPoint2) : %u\n\n", IsOrigin(exPoint2));

    printf("6. IsOnSbX(exPoint2) : %u\n\n", IsOnSbX(exPoint2));

    printf("7. IsOnSbY(exPoint2) : %u\n\n", IsOnSbY(exPoint2));

    printf("8. Kuadran(exPoint2) : %d\n\n", Kuadran(exPoint2));

    printf("9. NextX(exPoint2) : ");
    TulisPOINT(NextX(exPoint2));
    printf("\n");

    printf("10. NextY(exPoint2) : ");
    TulisPOINT(NextY(exPoint2));
    printf("\n");

    printf("Masukkan deltaX dan deltaY (Format : X Y) :\n");
    scanf("%d%d", &dX, &dY);
    printf("11. PlusDelta : ");
    TulisPOINT(PlusDelta(exPoint2, dX, dY));
    printf("\n");

    printf("12. MirrorOf(exPoint2, true) : ");
    TulisPOINT(MirrorOf(exPoint2, true));
    printf("\n");

    printf("13. MirrorOf(exPoint2, false) : ");
    TulisPOINT(MirrorOf(exPoint2, false));
    printf("\n");

    printf("14. Panjang(exPoint1, exPoint2) : %.3f\n\n", Panjang(exPoint1, exPoint2));

    printf("15. Geser(exPoint1, dX, dY) : ");
    Geser(&exPoint2, dX, dY);
    TulisPOINT(exPoint2);
    printf("\n");

    printf("16. GeserKeSbX(exPoint2) : ");
    GeserKeSbX(&exPoint2);
    TulisPOINT(exPoint2);
    printf("\n");

    printf("17. GeserKeSbY(exPoint2) : ");
    GeserKeSbY(&exPoint2);
    TulisPOINT(exPoint2);
    printf("\n");

    printf("18. Mirror(exPoint1, true) : ");
    Mirror(&exPoint1, true);
    TulisPOINT(exPoint1);
    printf("\n");

    printf("19. Mirror(exPoint1, false) : ");
    Mirror(&exPoint1, false);
    TulisPOINT(exPoint1);
    printf("\n");

    printf("Masukkan sudut perputaran (derajat) : \n");
    scanf("%f", &sudut);
    printf("20. Putar(exPoint1, sudut) : ");
    Putar(&exPoint1, sudut);
    TulisPOINT(exPoint1);
    printf("\n");

    return 0;
}

