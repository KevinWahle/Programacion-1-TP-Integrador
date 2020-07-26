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
#include "event_queue\event_queue.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 *******************************************************************************/
typedef struct state_diagram_edge STATE;

struct state_diagram_edge{
    event_t evento;
	//Evento que activa la rutina de acción

    STATE *proximo_estado;
    // Puntero que apunta al estado al que hay que ir en caso
    //que se cumpla el evento correspondiente. 

    void (*p_rut_accion)(void);
    // Función a realizar durante la transición entre un estado y otro.
};

extern STATE splash_state[];
extern STATE menu_state[];
extern STATE click_state[];
extern STATE play_state[];
extern STATE game_score_state[];
extern STATE global_score_state[];

STATE splash_state []= {
	{CLICK_BTN, menu_state, my_menu},
    {FIN_TABLE, splash_state, doNothing}
};

STATE menu_state []= {
    {MOVE_UP, menu_state, up_menu}, 
    {MOVE_DOWN, menu_state, down_menu},
    {CLICK_BTN, click_state, click_menu},
    {FIN_TABLE, menu_state, doNothing}
};

STATE click_state[]= {
    {PLAY_EVENT, play_state, start_game}, 
    {SCORE_EVENT, global_score_state, show_global_score},
//    {OPTIONS_EVENT, click_state, doNothing},
    {EXIT_EVENT, NULL, quit_game},
    {FIN_TABLE, click_state, doNothing}
};

STATE play_state[] = {
    {PAUSE_EVENT, menu_state, pause_game},      //pause_game va a tener adentro a show_menu() 
    {END_GAME_EVENT, game_score_state, show_game_score},
    {FIN_TABLE, play_state, doNothing} //NOTA: no debería
};

STATE pause_state[k] = {
    {MOVE_UP, menu_state, up_menu},         //REVISAR: crear estado click_state como el del main menu() 
    {MOVE_DOWN, menu_state, down_menu},     // y hacer el tema de poder subir y bajar en el menú.
    {RESTART_EVENT, play_state, start_game},
    {RESUME_EVENT, play_state, resume_game},
    {FIN_TABLE, play_state, doNothing}
};

STATE game_score_state[] = {
    {RETURN_EVENT, menu_state, my_menu}, 
    {FIN_TABLE, game_score_state, doNothing}
};

STATE global_score_state[] = {
    {RETURN_EVENT, menu_state, my_menu}, 
    {FIN_TABLE, global_score_state, doNothing}
};


/*******************************************************************************
 ******************************************************************************/

#endif // FSM_table_H