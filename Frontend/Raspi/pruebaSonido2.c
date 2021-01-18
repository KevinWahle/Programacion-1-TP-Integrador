#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../../some files/RPi_Files/audio/SDL2/src/audio.h"            // ATENCAO LA RUTA // ../../some files/RPi_Files/audio/SDL2/src/audio.h
#include "timer/timer.h"

int main(void) 
{


    if ( initAudio() == NO_INIT)
    {
        fprintf(stderr, "Audio not initilized.\n");
	    endAudio();
	    return -1;
    }

   // Audio * sound = createAudio( "../Sounds/shoot.wav" , 0, 127);

    own_timer_t temp;
    setTimer(&temp, 8.0);
    startTimer(&temp);

  /*  playMusic("../Sounds/IntroCheta.wav", 128/2);

    SDL_Delay(10000);

    endAudio();*/
    
    int i = 0;
    while( i < 5)
    {
        i++;
        while( !checkTimer(&temp) );
        pauseAudio();
        printf("OSTRAS, SE DEBERIA DISPARAR YA\n");

            //playSoundFromMemory(sound, SDL_MIX_MAXVOLUME);
        playMusic("../Sounds/space-invaders-space-invaders (1).wav", 128/2);
        
    }
    endAudio();
}
