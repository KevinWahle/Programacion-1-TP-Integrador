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
void reset_lives(void);
/**
 * @brief resetea las vidas
*/

void reset_points(void);
/**
 * @brief resetea los puntos
*/

void reset_level(void);
/**
 * @brief resetea el nivel
*/

void reset_speed(void); //NOTA: Puede ir a .c
/**
 * @brief resetea la velocidad
*/

void reset_killed_aliens(void); //NOTA: Puede ir a .c
/**
 * @brief resetea la cantidad de aliens asesinados
*/

void increase_points(const int cant);
/**
 * @brief incrementa los puntos
 * @param cant cantidad de puntos a incrementar
*/

int decrease_lives(void);
/**
 * @brief Permite decrementar en 1 la cantidad de vidas disponibles
 *  sin necesidad acceder a la variable "lives".
 * @return Retorna las vidas disponibles post-decremento.
*/

void increase_lives(void); 
/**
 * @brief incrementa las vidas
*/

void increase_level(void);
/**
 * @brief incrementa el nivel
*/

void increase_speed(const int cant);
/**
 * @brief incrementa la  velocidad
 * @param cant cantidad de velocidad a incrementar
*/

int get_lives(void);
/**
 * @brief Permite conocer las vidas disponibles de la nave sin necesidad 
 * de acceder a la variable "lives" 
 * @return Retorna la cantidad de vidas disponibles.
*/

int get_points(void);
/**
 * @brief Permite conocer los puntos obtenidos sin necesidad de acceder a
 * la variable "points".
 * @return Retorna la cantidad de puntos obtenidos en la partida.
*/

int get_level(void);
/**
 * @brief Permite conocer el nivel actual sin necesidad acceder a
 * la variable "level".
 * @return Retorna el nivel actual.
*/

void set_speed(int new_speed);
/**
 * @brief actualiza la velocidad
 * @param new_speed representa el nuevo valor de la velocidad
*/

void set_level(int new_level);
/**
 * @brief actualiza el nivel
 * @param new_level representa el nuevo nivel
*/


/*******************************************************************************
 ******************************************************************************/

#endif // _INGAME_STATS_H_



