

/* TEST OF Sound Library libaudio by dany*/
// gcc testaudio.c libaudio.c -I/usr/local/include -L/usr/local/lib -lSDL -lpthread -o testaudio
// Run with ./testaudio


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "../../RPi_Files/audio/SDL1/libaudio.h"

#include "timer/timer.h"
//char AudioFile[]="./Sound/red.wav";
//char AudioFile[]="LiveItUp.wav";

//void do_something(void);

int main(void) 
{
    init_sound(); 

    own_timer_t temp;
    setTimer(&temp, 8.0);
    startTimer(&temp);

    while(1)
    {
        while( !checkTimer(&temp) );
        end_play();
        stop_sound();
        printf("OSTRAS, SE DEBERIA DISPARAR YA\n");
        if( !(player_status() == PLAYING ) )
        {
            char mySong[] = "../Sounds/shoot.wav";
	        set_file_to_play(mySong);       				
	        play_sound();
        }
    }
}
