/***************************************************************************/ /**
  @file     +FSM_table.h+
  @brief    +Tabla de estados de la maquina de estados+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef FSM_TABLE_H
#define FSM_TABLE_H


/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "../const.h"
#include "FSM_routines.h"
#include "event.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef unsigned char EVENT;
typedef struct state_diagram_edge STATE;

struct state_diagram_edge{
    EVENT evento;
	// Arreglo con todos los eventos admitidos que activan la rutina de acción

    STATE *proximo_estado;
    // Puntero que apunta al estado al que hay que ir en caso
    //que se cumpla el evento correspondiente. 

    void (*p_rut_accion)(void);
    // Función a realizar durante la transición entre un estado y otro.
};

extern STATE splash_state[];
extern STATE menu_state[];
extern STATE play_state[];
extern STATE game_score_state[];
extern STATE global_score_state[];


STATE splash_state []= {
	{PRESS_EVENT, menu_state, show_menu},
    {FIN_TABLE, splash_state, doNothing}
};

STATE menu_state []= {
    {SCORE_EVENT, global_score_state, show_global_score}, 
    {EXIT_EVENT, NULL, quit_game},
    {RESTART_EVENT, play_state, restart_game},
    {RESUME_EVENT, play_state, resume_game},
    {FIN_TABLE, menu_state, doNothing}
};

STATE play_state[] = {
    {PAUSE_EVENT, menu_state, pause_game},      //pause_game va a tener adentro a show_menu() 
    {END_GAME_EVENT, game_score_state, end_game},
    {FIN_TABLE, play_state, doNothing}
};

STATE game_score_state[] = {
    {RETURN_EVENT, menu_state, show_menu}, 
    {FIN_TABLE, game_score_state, doNothing}
};

STATE global_score_state[] = {
    {RETURN_EVENT, menu_state, show_menu}, 
    {FIN_TABLE, global_score_state, doNothing}
};


/*******************************************************************************
 ******************************************************************************/

#endif // FSM_table_H