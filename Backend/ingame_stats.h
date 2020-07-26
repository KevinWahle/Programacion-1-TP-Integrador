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
void reset_points(void);
void reset_level(void);
void reset_speed(void); //NOTA: Puede ir a .c
void reset_killed_aliens(void); //NOTA: Puede ir a .c
void reset_aliens_matrix(void);

void increase_points(const int cant);
int decrease_lives(void);
void increase_lives(void); 
void increase_level(void);
void increase_speed(const int cant);

int get_lives(void);
int get_points(void);
int get_level(void);

void set_speed(int new_speed);
void set_level(int new_level);

/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/
// +ej: char lcd_goto (int fil, int col);+


/*******************************************************************************
 ******************************************************************************/

#endif // _INGAME_STATS_H_



