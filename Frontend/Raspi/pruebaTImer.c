#include <stdio.h>
#include "timer.h"

int main(void)
{
    own_timer_t myTimer;
    double deltaTime = 5;
    setTimer(&myTimer, deltaTime);
    while(1)
    {
        printf("AT LEAST TIL HERE PRINT SMTHING MAN");
        while(!checkTimer(&myTimer));
        printf("LLEGUE");
    }
}

