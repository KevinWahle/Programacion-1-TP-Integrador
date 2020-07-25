#include "ingame_stats.h"

static int lives;
static int points;
static int killed_invaders[3];
static int shields[SHIELDS][SHIELD_PARTS];
//Primer elemento scrabs, segundo octopus, tercero squids 
//y ultimo UFOs.


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
        increase_points(UFO_POINTS);    
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

void shield_collision()
{

}

void level_up(){
    
}
