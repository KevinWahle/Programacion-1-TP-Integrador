#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../../some files/RPi_Files/audio/SDL2/src/audio.h"            // ATENCAO LA RUTA // ../../some files/RPi_Files/audio/SDL2/src/audio.h
#include "timer/timer.h"
// gcc pruebaSonido.c libaudio.c -I/usr/local/include -L/usr/local/lib -lSDL -lpthread -o testaudio

int main(void) 
{

    // probamos:
    SDL_Init(SDL_INIT_AUDIO);

    if ( initAudio() == NO_INIT)
    {
        fprintf(stderr, "Audio not initilized.\n");
	    endAudio();
	    return -1;
    }

    Audio * sound = createAudio( "../Sounds/level-up-sound-effect (1).wav" , 0, 127);

    own_timer_t temp;
    setTimer(&temp, 8.0);
    startTimer(&temp);

  /* playMusic("../Sounds/IntroCheta.wav", 128/2);

    SDL_Delay(10000);

    endAudio();*/
    
    int i = 0;
    while( i < 5)
    {
        i++;
        while( !checkTimer(&temp) );
        
        printf("OSTRAS, SE DEBERIA DISPARAR YA\n");

        playSoundFromMemory(sound, 127);
    }
    
    endAudio();
    
    SDL_Quit();

}
