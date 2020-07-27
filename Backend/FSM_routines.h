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
extern running;   //REVISAR: Falta tipo de dato


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
 * @brief Llama a la funcion que se encarga del splash
*/

void my_menu(void);
/**
 * @brief Llama a la funcion que se encarga de mostrar el menu, indicandole las opciones a mostrar y la opcion a resaltar
*/

void up_menu(void);
/**
 * @brief Llama a la funcion que se encarga de mostrar el menu, indicandole las opciones a mostrar y la opcion a resaltar
*/

void down_menu(void);
/**
 * @brief Llama a la funcion que se encarga de mostrar el menu, indicandole las opciones a mostrar y la opcion a resaltar
*/

void click_menu(void);
/**
 * @brief Añanade la opcion seleccionada a la cola de eventos
*/

void pause_game(void);
/**
 * @brief Llama a la funcion que se encarga de mostrar el menu de pausa, indicandole las opciones a mostrar y la opcion a resaltar
*/

void resume_game(void);
/**
 * @brief CONTINUAR: 
*/

void start_game(void);
/**
 * @brief Resetea todos los puntos y estadisticas CONTINUAR:
*/

void show_game_score(unsigned long long int score);
/**
 * @brief LLama a la funcion que se encarga de mostrar el score, indicandole el puntaje final y la cantidad de aliens asesinados
*/

void show_global_score(void);
/**
 * @brief LLama a la funcion que se encarga de mostrar el score, indicandole el top deseado
*/

void quit_game(void);
/**
 * @brief LLama a la funcion que se encarga de destruir los recursos del front
*/

void doNothing(void);
/**
 * @brief No hace nada
*/

void click_menu_pause(void);
/**
 * @brief Añanade la opcion seleccionada a la cola de eventos
*/
/////////////////////////////////////////////////////////////////////////////NOTA: HASTA  ACA COMENTÉ

void crab_coll(void);
/**
 * @brief 
*/
void octo_coll(void);


void squid_coll(void);

void ufo_coll(void);

void cannon_coll(void);

void up_menu_main(void);
void down_menu_main(void);
void up_menu_pause(void);
void down_menu_pause(void);









/*******************************************************************************
 ******************************************************************************/

#endif // _FSM_ROUTINES_H_
