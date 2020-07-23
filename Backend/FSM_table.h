/***************************************************************************/ /**
  @file     +FSM_table.h+
  @brief    +Tabla de estados de la maquina de estados+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef FSM_TABLE_H
#define FSM_TABLE_H

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef unsigned char EVENT;
typedef struct state_diagram_edge
{
    EVENT evento;
    struct state_diagram_edge *proximo_estado;
    void (*p_rut_accion)(void);
} STATE;

STATE init_state[] = {         
    {OK_EVENT, splash_state, show_splash},
    {INIT_FAILURE_EVENT, NULL, exit},
    {FIN_TABLE, init_state, doNothing}
};

STATE splash_state[] = {
    {PRESS_EVENT, menu_state, show_menu},
    {FIN_TABLE, splash_state, doNothing}
};

STATE menu_state[] = {
    {SCORE_EVENT, global_score_state, show_global_score}, 
    {EXIT_EVENT, NULL, exit},
    {RESTART_EVENT, play_state, restart_game},
    {CONTINUE_EVENT, play_state, continue_game},
    {FIN_TABLE, menu_state, doNothing}
};

STATE play_state[] = {
    {PAUSE_EVENT, menu_state, pause_game},      //pause_game va a tener adentro a show_menu() 
    {END_GAME_EVENT, game_score_event, end_game},
    {FIN_TABLE, play_state, doNothing}
};

STATE game_score_event[] = {
    {RETURN_EVENT, menu_state, show_menu}, 
    {FIN_TABLE, game_score_event, doNothing}
};

STATE global_score_event[] = {
    {RETURN_EVENT, menu_state, show_menu}, 
    {FIN_TABLE, global_score_event, doNothing}
};


/*******************************************************************************
 ******************************************************************************/

#endif // FSM_table_H