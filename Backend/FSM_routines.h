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
extern BOOL running;


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

void up_menu(MENU_ITEM* menu); //REVISAR: hay que  incluir donde esta la constante
/** 
 * @brief Llama a la funcion que se encarga de mostrar el menu, indicandole las opciones a mostrar y la opcion a resaltar
 * @param // CONTINUAR:
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

void crab_coll(void);
/**
 * @brief Llama a la funcion encargada de matar al crab
*/

void octo_coll(void);
/**
 * @brief Llama a la funcion encargada de matar al octopus
*/

void squid_coll(void);
/**
 * @brief Llama a la funcion encargada de matar al squid
*/

void ufo_coll(void);
/**
 * @brief Llama a la funcion encargada de matar al ufo
*/

void cannon_coll(void);
/**
 * @brief Decrementa una vida y agrega el suceso a  la cola de eventos
*/

void up_menu_main(void);
/**
 * @brief Llama a la funcion encargada seleccionar la opcion de arriba del menu principal
*/

void down_menu_main(void);
/**
 * @brief Llama a la funcion encargada seleccionar la opcion de abajo del menu principal
*/

void up_menu_pause(void);
/**
 * @brief Llama a la funcion encargada seleccionar la opcion de arriba del menu principal
*/

void down_menu_pause(void);

/**
 * @brief Llama a la funcion encargada seleccionar la opcion de arriba del menu principal
*/








/*******************************************************************************
 ******************************************************************************/

#endif // _FSM_ROUTINES_H_
