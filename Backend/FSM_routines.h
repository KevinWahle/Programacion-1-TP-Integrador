/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

#ifndef _FSM_ROUTINES_H_
#define _FSM_ROUTINES_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "scoretable.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
extern running;


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
//REVISAR: @baisili REVISAR: @basili REVISAR:
/**
 * @brief completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
*/

void show_splash(void);
/**
 * @brief llama a la funcion que se encarga del splash
*/

void my_menu(void);
/**
 * @brief llama a la funcion que se encarga del splash
*/

void up_menu(void);

void down_menu(void);

void click_menu(void);

void pause_game(void);

void resume_game(void);

void start_game(void);

void show_game_score(unsigned long long int score);

void show_global_score(void);

void quit_game(void);

void doNothing(void);

void click_menu_pause(void);

void crab_coll(void);

void octo_coll(void);

void squid_coll(void);

void ufo_coll(void);

void cannon_coll(void);







/*******************************************************************************
 ******************************************************************************/

#endif // _FSM_ROUTINES_H_
