// Programa dado por la catedra para testear el joystick


#include <stdio.h>
#include "joydrv.h"
#include "termlib.h"

int main(void)
{
    jcoord_t myCoords;
    joy_init();
    do
    {
        joy_update();
        myCoords = joy_get_coord();
        printf( CYAN_TEXT "(%4d, %4d)\n", myCoords.x, myCoords.y);
    } while(joy_get_switch() == J_NOPRESS);
    return 0;
}