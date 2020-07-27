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
#include "event_queue/event_queue.h"
#include "ingame_stats.h"

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
    {MOVE_UP, menu_state, up_menu_main}, 
    {MOVE_DOWN, menu_state, down_menu_main},
    {CLICK_BTN, click_state, click_menu},
    {FIN_TABLE, menu_state, doNothing}
};

STATE click_state[]= {
    {PLAY_EVENT, play_state, start_game}, 
    {SCORE_EVENT, global_score_state, show_global_score},
//    {OPTIONS_EVENT, click_state, doNothing},
    {EXIT_EVENT, NULL, quit_game},
    {RESUME_EVENT, play_state, resume_game}, 
    {BACK_EVENT, menu_state, my_menu}, 
    {FIN_TABLE, click_state, doNothing}
};

STATE play_state[] = {
    {PAUSE_EVENT, menu_state, pause_game},       
    {END_GAME_EVENT, game_score_state, show_game_score},
    {NEXT_LEVEL_EV, play_state, increase_level},
    {CRAB_COLL_EV, play_state, crab_coll},
    {OCTO_COLL_EV, play_state, octo_coll},
    {SQUID_COLL_EV, play_state, squid_coll},
    {UFO_COLL_EV, play_state, ufo_coll},
    {FIN_TABLE, play_state, refresh} 
};

STATE pause_state[] = {
    {MOVE_UP, pause_state, up_menu_pause},          
    {MOVE_DOWN, pause_state, down_menu_pause},     
    {CLICK_BTN, click_state, click_menu_pause},
    {FIN_TABLE, pause_state, doNothing}
};

STATE game_score_state[] = {
    {CLICK_BTN, menu_state, my_menu}, 
    {FIN_TABLE, game_score_state, doNothing}
};

STATE global_score_state[] = {
    {CLICK_BTN, menu_state, my_menu}, 
    {FIN_TABLE, global_score_state, doNothing}
};


/*******************************************************************************
 ******************************************************************************/

#endif // FSM_table_H