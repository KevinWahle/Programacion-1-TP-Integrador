/***************************************************************************//**
  @file     +ingame_stats.c+
  @brief    +Estadisticas generales del juego+
  @author   +Grupo 3+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "ingame_stats.h"
#include <time.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Resetea el timer
*/
void reset_timer(void);

/**
 * @brief resetea la velocidad
*/
void reset_speed(void);

/**
 * @brief incrementa los puntos
 * @param cant cantidad de puntos a incrementar
*/
void increase_points(const int cant);

/**
 * @brief actualiza la velocidad
 * @param new_speed representa el nuevo valor de la velocidad
*/
void set_speed(int new_speed);

/**
 * @brief actualiza el nivel
 * @param new_level representa el nuevo nivel
*/
void set_level(int new_level);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static int lives, level, speed=MIN_SPEED;   // Variables estaticas internas que permiten
static unsigned long int points;            // el desarrollo de la partida.



static clock_t start;                               // Referencia para medir tiempo.                         

static unsigned int killed_invaders[TYPES_INVADERS];
// Arreglo con la cantidad de invaders asesinados de cada tipo. 
//Su contendio quedaría:
// killed_invaders = {crab_killed, octo_killed, squid_killed, UFO_killed};


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


/**********************************************************
***********************  RESET   **************************
**********************************************************/
void reset_lives()
{
    lives=INIT_LIFES;   //Devuelvo la variable vidas a su valor inicial.
    //update_lives(lives);     // INCLUIR: header con el prototipo
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
    set_level(0);        // Reinicio al nivel 0.
    reset_speed();       // Reinicio la velocidad
    
    #ifdef DEBUG
        printf("Resteo nivel. \n");
    #endif  
}


void reset_killed_aliens()
{
    for (int i=CRAB; i<=UFO; i++)
    {
        killed_invaders[i]=0;      // Vuelve el contador de muertes de aliens de cada tipo a 0
    }

    #ifdef DEBUG
        printf("Se reinicion la cantidad de aliens asesindos...\n");
    #endif 
}



/**********************************************************
******************  INCREASE / DECREASE   *****************
**********************************************************/


int decrease_lives()      
{
    lives--;                // Decremento la cantidad de vidas en uno.
    
    //update_lives(lives);     // INCLUIR: header con el prototipo
    
    #ifdef DEBUG
        printf("Decremento 1 vida, quedan %d vidas \n", lives);
    #endif  

    return lives;
}

void increase_lives()      
{
    if(lives<=2){           // Si perdi alguna vida:
        lives++;            // Incremento la cantidad de vidas en uno. 
        //update_lives(lives);     // INCLUIR: header con el prototipo
        #ifdef DEBUG
        printf("Incremento 1 vida, quedan %d vidas \n", lives);
        #endif          
    }                  
}

void increase_level(){
    level++;                // Incremento el nivel en uno.
    increase_lives();
    int newspeed = level*STEP_LEVEL_SPEED;
    set_speed(newspeed);
    reset_timer();
    //INCLUIR: Agregar update_speed_front(speed) y el archivo donde este su prototipo.

 
    //CONTINUAR:
    // placeInvader(); 
    // clean_shoots();
    //INCLUIR: incluir archivo con la funcion reset_aliens_matrix();

    #ifdef DEBUG
        printf("Se incremento el nivel, esta en el nivel %d\n", level);
        printf("La velocidad de inicio de nivel es: %d\n", speed);
    #endif  
}

void speed_update(const float seg)
{
    clock_t end = clock();                                      // Tomo el tiempo actual de la consola.
    float difference =((float)(end-start)/CLOCKS_PER_SEC);      // Calculo cuantos segundos.
    if (difference >= seg)                                      // Si pasó más tiempo del debido:
    {
        reset_timer();                                          // Actualizo el tiempo de referencia.
        
        if( (speed + STEP_SPEED) <= MAX_SPEED)           // Si puedo incrementar la velocidad sin superar
            speed += STEP_SPEED;                         // la velocidad máxima, la incremento.
        
        #ifdef DEBUG
        printf("La nueva velocidad es: %d \n", speed);
        #endif
        
        //update_speed_front(speed);
        //INCLUIR: donde se encuentre update_speed_front.

    }        
}

/**********************************************************
************************   GET   **************************
**********************************************************/

unsigned long int get_points()    
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

unsigned int get_killed_aliens(const int tipo_alien)
{
    #ifdef DEBUG
    printf("Se mataron %d de la especie: %d \n", killed_invaders[tipo_alien], tipo_alien);
    #endif 

    return killed_invaders[tipo_alien]; 
}


/**********************************************************
**********************  VARIOUS   *************************
**********************************************************/

void kill_alien(const int tipo_alien)       
//Sumo al puntaje actual, la cantidad propocional al
//invader proporcional.   
{
    switch (tipo_alien)
    /*
        Preferentemente:
    *   CRAB = 1
    *   OCTO = 2 
    *   SQUID = 3
    *   UFO = 4 
    */
    {
    case CRAB:
        increase_points(CRAB_POINTS);       // Aumenta los puntos relacioados al "crab"
        
        break;

    case OCTO:
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

    }
    if (tipo_alien>=CRAB && tipo_alien<=UFO)            // Corroboramos para evitar cualquier tipo de error
    {
        killed_invaders[tipo_alien]++;                  // Sumamos el contador de muertes relacionado al tipo de alien      
    }
    
    //update_points(get_points());   //INCLUIR: header con el prototipo
    
    #ifdef DEBUG
        printf("Tipo de invader asesinado: %d \t Puntos: %lu \n\n", tipo_alien, get_points());
    
        for(int i=0; i<=UFO; i++){
        printf("Invaders del tipo %d asesinados: %d\n", tipo_alien, killed_invaders[tipo_alien]);
        }
        printf("\n");
    
    #endif 
    
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void reset_timer(void)
{
    start=clock();                  // Renuevo el tiempo de referecia.
}

void reset_speed()
{
    set_speed(MIN_SPEED);   // Reseteo la velocidad al mínimo.
    reset_timer();          // Reseteo el valor de referencia.

    #ifdef DEBUG
        printf("Reseto la velocidad y la referencia...\n");
    #endif 
}

void increase_points(const int cant)
{
    points += cant;         // Incremento los puntos en cant.
        
    #ifdef DEBUG
        printf("Incremento en %d los puntos, hay %lu puntos \n", cant, get_points());
    #endif  
}   
 
void set_speed(int new_speed){              
    speed=new_speed;                                // Actualizamos la velocidad

    #ifdef DEBUG
        printf("La velocidad paso a ser: %d \n", speed);
    #endif 
}

void set_level(int new_level)
{
    level=new_level;                                // Actualizamos el nivel

    #ifdef DEBUG
        printf("El nivel paso a ser: %d \n", level);
    #endif 
}



