/*******************************************************************************
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


#if PLATFORM == ALLEGRO
#include "../Frontend/Allegro/headall.h" 

#elif PLATFORM == RASPI
//#include "../Frontend/Raspi/.." //INCLUIR: header front.
#endif


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

STATE *fsm_interprete(STATE * p_tabla_estado_actual, event_t evento_actual);

extern STATE splash_state[];
extern STATE menu_state[];
extern STATE click_state[];
extern STATE play_state[];
extern STATE next_level_state[];
extern STATE pause_state[];
extern STATE instruction_state[];
extern STATE game_score_state[];
extern STATE saving_score_state[]; 
extern STATE global_score_state[];

STATE splash_state []= {
	{CLICK_BTN, menu_state, my_menu},
    {EXIT_EVENT, NULL, quit_game},
    {NULL_EVENT, splash_state, doNothing}
};

STATE menu_state []= {
    {MOVE_UP, menu_state, up_menu_main}, 
    {MOVE_DOWN, menu_state, down_menu_main},
    {CLICK_BTN, click_state, click_menu},
    {EXIT_EVENT, NULL, quit_game},
    {NULL_EVENT, menu_state, doNothing}
};

STATE click_state[]= {
    {PLAY_EVENT, play_state, start_game}, 
    {SCORE_EVENT, global_score_state, show_global_score},
    {INSTRUCTION_EVENT, instruction_state, shows_inst}, 
    {EXIT_EVENT, NULL, quit_game},
    {RESUME_EVENT, play_state, resume_game}, 
    {BACK_EVENT, menu_state, my_menu}, 
    {NULL_EVENT, click_state, doNothing}
};

STATE instruction_state []= {
	{CLICK_BTN, menu_state, my_menu},
    {EXIT_EVENT, NULL, quit_game},
    {NULL_EVENT, instruction_state, doNothing}
};

STATE play_state[] = {
    {PAUSE_BTN, pause_state, pause_game},    
    {CLICK_BTN, play_state, shoot_cannon},
    {MOVE_LEFT, play_state, move_cannon_left},
    {MOVE_RIGHT, play_state, move_cannon_right},
    {MOVE_RIGHT_REL, play_state, stop_cannon},
    {MOVE_LEFT_REL, play_state, stop_cannon},
    {END_GAME_EVENT, game_score_state, show_game_score},
    {NEXT_LEVEL_EV, next_level_state, increase_level},    
    {CRAB_COLL_EV, play_state, crab_coll},
    {OCTO_COLL_EV, play_state, octo_coll},
    {SQUID_COLL_EV, play_state, squid_coll},
    {UFO_COLL_EV, play_state, ufo_coll},
    {CANNON_COLL_EV, play_state, cannon_coll},
    {EXIT_EVENT, NULL, quit_game},
    {NULL_EVENT, play_state, refresh} 
};

STATE next_level_state[] ={
    {CLICK_BTN, play_state, resume_game},
    {EXIT_EVENT, NULL, quit_game},
    {NULL_EVENT, next_level_state, doNothing}
};

STATE pause_state[] = {
    {MOVE_UP, pause_state, up_menu_pause},          
    {MOVE_DOWN, pause_state, down_menu_pause},     
    {CLICK_BTN, click_state, click_menu_pause},
    {EXIT_EVENT, NULL, quit_game},
    {NULL_EVENT, pause_state, doNothing}
};

STATE game_score_state[] = {
    {CLICK_BTN, saving_score_state, saving_init},
    {EXIT_EVENT, NULL, quit_game},
    {NULL_EVENT, game_score_state, doNothing}
};

STATE saving_score_state[] = {
    {CLICK_BTN, menu_state, save_score}, 
    {MOVE_UP, saving_score_state, upper_letter}, 
    {MOVE_DOWN, saving_score_state, lower_letter}, 
    {MOVE_LEFT, saving_score_state, previous_letter}, 
    {MOVE_RIGHT, saving_score_state, next_letter},
    {EXIT_EVENT, NULL, quit_game}, 
    {NULL_EVENT, saving_score_state, show_name} 
};

STATE global_score_state[] = {
    {CLICK_BTN, menu_state, my_menu}, 
    {EXIT_EVENT, NULL, quit_game},
    {NULL_EVENT, global_score_state, doNothing}
};


/*******************************************************************************
 ******************************************************************************/

#endif // FSM_table_H