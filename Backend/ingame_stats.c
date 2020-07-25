#include "ingame_stats.h"
#include<time.h> 
#include <stdlib.h>

static int lives;
static int points;
static int killed_invaders[3];
//El contendio quedaría:
//  killed_invaders = {crab_killed, octopus_killed, squid_killed, UFO_killed};

static int shields[SHIELDS][SHIELD_PARTS];

/**********************************************************
***********************  RESET   **************************
**********************************************************/
void reset_lives()
{
    lives=INIT_LIFES;
} 

void reset_points()
{
    points=0;
}

void reset_shields()
{
    for (int i=0; i<SHIELDS; i++)
        {
            for (int j = 0; j < SHIELD_PARTS; j++)
            {
                shields[i][j]=SHIELD_LIVES;
            }
        }

}


/**********************************************************
******************  INCREASE / DECREASE   *****************
**********************************************************/

void increase_points(const int cant)
{
    points += cant;
}

int decrease_lives()        // REVISAR: ¿Chequeo si lives>0?
{
    return --lives;
}

/**********************************************************
*************************  GET   **************************
**********************************************************/

int get_lives()
{
    return lives;
}

int get_points()
{
    return points;
}

int* get_shields()
{
    return shields;
}

/**********************************************************
************************  VARIOUS   ***********************
**********************************************************/

void kill_alien(const int tipo_alien)       //NOTA: FALTARIA LA POSICION. EN EL FRONT, LOS BICHOS ESTAN EN UNA MATRIZ
//Sumo al puntaje actual, la cantidad propocional al
//invader proporcional.   
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
        srand(time(0)); 
        int temp;
        do {
            temp= rand()
        }while ( temp>=MIN_RAND && temp<=MAX_RAND);
        increase_points(temp*UFO_POINTS);   
        break;                         

    default:
        return 1;
    }

    if (tipo_alien>=0 && tipo_alien<=3)
    {
        killed_invaders[tipo_alien]++;  
    }
    return 0;
}

void shield_collision(int shield, int parte)
// Shield va entre 0 y SHIELDS-1
{
    if (shield>=0 && shield <SHIELDS && parte>=IZQUIERDA && parte<=DERECHA) 
    shields[shield][parte]--;                
}

void level_up(){

    
}


