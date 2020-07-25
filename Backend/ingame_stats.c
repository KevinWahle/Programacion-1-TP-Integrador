#include "ingame_stats.h"

static int lives;
static int points;
static int killed_invaders[3];
//Primer elemento scrabs, segundo octopus, tercero squids 
//y ultimo UFOs.


void reset_lives()
{
    lives=INIT_LIFES;
} 

void reset_points()
{
    points=0;
}

void increase_points(int cant)
{
    points += cant;
}

int decrease_lives()
{
    return --lives;
}

int get_lives()
{
    return lives;
}

int get_points()
{
    return points;
}

void kill_alien(const int tipo_alien)
{
    switch (tipo_alien)
    /* NOTA: Definir los aliens en algun .h  
    Preferentemente:
    *   CRAB = 1
    *   OCTOPUS = 2 
    *   SQUID = 3
    *   UFO = 4 
    */
    {
    case CRAB:
        increase_points(CRAB_POINTS);
        
        break;

    case OCTOPUS:
        increase_points(OCTOPUS_POINTS);
        break;

    case SQUID:
        increase_points(SQUID_POINTS);
        break;            

    case UFO:
        increase_points(UFO_POINTS);
        break; 

    default:
        return 1;
    }

    if (tipo_alien>=0 && tipo_alien<=3)
    {
        killed_invaders[tipo_alien]++;  // Incremento la cantidad de invaders del tipo
                                        //del que fue asesinado.
    }
    return 0;
}

void shield_collision()
{

}

void level_up(){
    
}
