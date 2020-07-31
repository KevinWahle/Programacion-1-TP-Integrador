//Programa dado por la catedra para testear el display

/*
    Enciende todo el display de a un LED por vez
*/

#include <stdio.h>
#include "disdrv.h"
#include "termlib.h"

int main(void)
{
    dcoord_t myPoint = {};
    disp_init();
    disp_clear();
    for(  myPoint.y = DISP_MIN; myPoint.y <= (DISP_MAX_Y); myPoint.y++ )
    {
        for(  myPoint.x = DISP_MIN; myPoint.x <= (DISP_MAX_X); myPoint.x++  )
        {
            disp_write(myPoint, D_ON);
            printf(YELLOW_TEXT  "(%2d,%2d)", myPoint.x, myPoint.y );
            disp_update();
        }
        printf("\n");
    }
    return 0;
}