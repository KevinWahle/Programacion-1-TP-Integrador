/***************************************************************************//**
  @file     +ingame_stats.h+
  @brief    +Estadisticas generales del juego+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef _INGAME_STATS_H_
#define _INGAME_STATS_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "../const.h"
#include <time.h> 
#include <stdlib.h>
#include <stdio.h>
// #include "../Frontend/Allegro/headall.h"
#include "../Frontend/Raspi/headall.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define MIN_SPEED        1
#define MAX_SPEED        100
#define STEP_SPEED       1
#define STEP_LEVEL_SPEED 10

#define CRAB_POINTS     10
#define OCTOPUS_POINTS  20
#define SQUID_POINTS    30     
#define UFO_POINTS      50
#define MIN_RAND        2
#define MAX_RAND        4

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief resetea las vidas
*/
void reset_lives(void);

/**
 * @brief resetea los puntos
*/
void reset_points(void);

/**
 * @brief resetea el nivel
*/
void reset_level(void);



/**
 * @brief resetea la cantidad de aliens asesinados
*/
void reset_killed_aliens(void); //NOTA: Puede ir a .c

/**
 * @brief Permite decrementar en 1 la cantidad de vidas disponibles
 *  sin necesidad acceder a la variable "lives".
 * @return Retorna las vidas disponibles post-decremento.
*/
int decrease_lives(void);

/**
 * @brief incrementa las vidas
*/
void increase_lives(void); 

/**
 * @brief incrementa el nivel
*/
void increase_level(void);


/**
 * @brief Permite conocer los puntos obtenidos sin necesidad de acceder a
 * la variable "points".
 * @return Retorna la cantidad de puntos obtenidos en la partida.
*/
unsigned long int get_points(void);

/**
 * @brief Permite conocer el nivel actual sin necesidad acceder a
 * la variable "level".
 * @return Retorna el nivel actual.
*/
int get_level(void);

/**
 * @brief Permite conocer el nivel actual sin necesidad acceder a
 * la variable "lives".
 * @return Retorna la cantidad de vidas actuales.
*/
int get_lives();

/**
 * @brief Incrementa el contador de aliens asesinados y tambien los puntos
 * en funcion a la especie del invasor destruido. 
 * @param tipo_alien especie invasora que fue destruida.
*/
void kill_alien(const int tipo_alien);

/**
 * @brief Actualiza la velocidad, incrementandola. 
 * @param seg cada cuantos segundos se quiere incrementar.
*/
void speed_update(const float seg);

/**
 * @brief contabilizala cantidd de aliens asesinados  
 * @param tipo_alien especie de alien.
*/
unsigned int get_killed_aliens(const int tipo_alien);

/*******************************************************************************
 ******************************************************************************/

#endif // _INGAME_STATS_H_



