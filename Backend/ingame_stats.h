//TODO: Completar descripciones y ver donde poner los prototipos.

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
 * @brief resetea la velocidad
*/
void reset_speed(void); //NOTA: Puede ir a .c

/**
 * @brief resetea la cantidad de aliens asesinados
*/
void reset_killed_aliens(void); //NOTA: Puede ir a .c

/**
 * @brief incrementa los puntos
 * @param cant cantidad de puntos a incrementar
*/
void increase_points(const int cant);

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
 * @brief incrementa la  velocidad
 * @param cant cantidad de velocidad a incrementar
*/
void increase_speed(const int cant);

/**
 * @brief Permite conocer las vidas disponibles de la nave sin necesidad 
 * de acceder a la variable "lives" 
 * @return Retorna la cantidad de vidas disponibles.
*/
int get_lives(void);

/**
 * @brief Permite conocer los puntos obtenidos sin necesidad de acceder a
 * la variable "points".
 * @return Retorna la cantidad de puntos obtenidos en la partida.
*/
int get_points(void);

/**
 * @brief Permite conocer el nivel actual sin necesidad acceder a
 * la variable "level".
 * @return Retorna el nivel actual.
*/
int get_level(void);

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


/**
 * @brief Incrementa el contador de aliens asesinados y tambien los puntos
 * en funcion a la especie del invasor destruido. 
 * @param tipo_alien: especie invasora que fue destruida.
*/
void kill_alien(const int tipo_alien);

/**
 * @brief Actualiza la velocidad, incrementandola. 
 * @param seg: cada cuantos segundos se quiere incrementar.
*/
void speed_update(const float seg);

/**
 * @brief Resetea el timer
*/
void reset_timer(void);


/*******************************************************************************
 ******************************************************************************/

#endif // _INGAME_STATS_H_



