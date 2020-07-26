#include "ingame_stats.h"
#include "../const.h"
#include <time.h> 
#include <stdlib.h>
#include <stdio.h>

static int lives;
static int points;
static int level;
static int speed=MIN_SPEED;

static int killed_invaders[CANT_INVADERS];
//El contendio quedaría:
//  killed_invaders = {crab_killed, octopus_killed, squid_killed, UFO_killed};


/**********************************************************
***********************  RESET   **************************
**********************************************************/
void reset_lives()
{
    lives=INIT_LIFES;   //Devuelvo la variable vidas a su valor inicial.
    
    #ifdef DEBUG
        printf("Renuevo vidas. \n");
    #endif  
} 

void reset_points()
{
    points=0;           //Devuelvo la variable puntos a su valor inicial.
    
    #ifdef DEBUG
        printf("Renuevo puntos. \n");
    #endif  
}

void reset_level()
{
    set_level(0)        // Reinicio al nivel 0.
    reset_speed();
    #ifdef DEBUG
        printf("Renuevo vidas. \n");
    #endif  
}

void reset_speed()
{
    #ifdef DEBUG
        printf("Reseto la velocidad...");
    #endif 
    
    set_speed(MIN_SPEED);
}

void reset_killed_aliens()
{
    for (int i=CRAB; i<=UFO; i++)
    {
        killed_invaders[i]=0;      // Vuelve el contador de muertes de aliens de cada tipo a 0
    }
}


/**********************************************************
******************  INCREASE / DECREASE   *****************
**********************************************************/

void increase_points(const int cant)
{
    points += cant;         // Incremento los puntos en cant.
        
    #ifdef DEBUG
        printf("Incremento en %d los puntos, hay %d puntos \n", cant, puntos);
    #endif  
}   

int decrease_lives()      
{
    lives--;                // Decremento la cantidad de vidas en uno.

    #ifdef DEBUG
        printf("Decremento 1 vida, quedan %d vidas \n", lives);
    #endif  

    return lives;
}

void increase_lives()      
{
    lives++;                // Incremento la cantidad de vidas en uno.

    #ifdef DEBUG
        printf("Incremento 1 vida, quedan %d vidas \n", lives);
    #endif  

}

void increase_level(){
    level++;                // Incremento el nivel en uno.
    if(lives<=2){
        lives++;
    }

    int newspeed = level*STEP_LEVEL_SPEED;
    set_speed(newspeed);
    //NOTA: Agregar speed_calculator(speed) y el archivo donde este su prototipo.

 
    //CONTINUAR:
    // reset_aliens_matrix(); //NOTA: incluir archivo con la funcion reset_aliens_matrix();

    #ifdef DEBUG
        printf("Se incremento el nivel, esta en el nivel %d \n", level);
        printf("La velocidad de inicio de nivel es: %d", speed);
    #endif  
}


void increase_speed(const int cant){
    
    if (speed<(MAX_SPEED-cant)){
        speed+=cant;            // Incremento en cant la velocidad
    }

    //NOTA: Agregar speed_calculator(speed) y el archivo donde este su prototipo.

    #ifdef DEBUG
        printf("Incremento en %d la velocidad, ahora la velocidad es: %d \n", cant, speed);
    #endif  
}

/**********************************************************
*************************  GET   **************************
**********************************************************/

int get_lives()
{
    #ifdef DEBUG
    printf("Se tienen %d vidas \n", lives);
    #endif 
    
    return lives;       // Devuelvo la cant de vidas de la nave.
}

int get_points()
{
    #ifdef DEBUG
    printf("Se tienen %d puntos \n", points);
    #endif 
    
    return points;      // Devuelvo la cant de puntos de la partida.
}

int get_level()
{
    #ifdef DEBUG
    printf("Esta en el nivel %d \n", level);
    #endif 
    
    return level;       // Devuelve el nivel en el que se encuentra
}

/**********************************************************
**************************  SET   *************************
**********************************************************/

void set_speed(int new_speed){              
    speed=new_speed;

    #ifdef DEBUG
        printf("La velocidad paso a ser: %d \n", speed);
    #endif 
}

void set_level(int new_level)
{
    level=new_level; 
}



/**********************************************************
************************  VARIOUS   ***********************
**********************************************************/

void kill_alien(const int tipo_alien)       //NOTA: EN EL FRONT, LOS BICHOS ESTAN EN UNA MATRIZ
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
        increase_points(CRAB_POINTS);       // Aumenta los puntos relacioados al "crab"
        
        break;

    case OCTOPUS:
        increase_points(OCTOPUS_POINTS);    // Aumenta los puntos relacionados al "octopus"
        break;

    case SQUID:
        increase_points(SQUID_POINTS);      // Aumenta los puntos relacionados al "squid"
        break;            

    case UFO:
        srand(time(0));                 
        int temp;
        do {
            temp= rand();                               
        }while ( temp>=MIN_RAND && temp<=MAX_RAND);     // Elegimos un puntaje aleatorio multiplo de 50 entre los valores deseados
        increase_points(temp*UFO_POINTS);               // Aumenta los puntos relacionados al "ufo"
        break;                         

    default:
        return 1;                                       
    }

    if (tipo_alien>=CRAB && tipo_alien<=UFO)            // Corroboramos para evitar cualquier tipo de error
    {
        killed_invaders[tipo_alien]++;                  // Sumamos el contador de muertes relacionado al tipo de alien      
    }
    
    #ifdef DEBUG
        printf("Tipo de invader asesinado: %d \t Puntos: %d \n\n", tipo_alien, get_points());
    
        for(int i=0, i=<UFO, i++){
        printf("Invaders del tipo %d asesinados: %d", tipo_alien, killed_invaders[tipo_alien]);
        }
        printf("\n")
    
    #endif 
    
    return 0;
}





