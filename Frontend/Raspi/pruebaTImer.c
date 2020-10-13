#include <stdio.h>
#include "timer/timer.h"

int main(void)
{
    own_timer_t myTimer;
    double deltaTime = 1;
    setTimer(&myTimer, deltaTime);
    startTimer(&myTimer);
    int cont = 0;
    int contador = 0;
    while(contador<=10)
    {
        // printf("AT LEAST TIL HERE PRINT SMTHING MAN\n");
        while(!checkTimer(&myTimer));
        printf("%d\n", ++cont);
    }
    while (1)
    {
        
    }
    
}

