#include <stdio.h>
#include "../const.h"
#include "FSM_table.h"

typedef unsigned char EVENT;
//typedef struct state_diagram_edge STATE;

typedef struct state_diagram_edge
{
    EVENT evento;
    STATE *proximo_estado;
    void (*p_rut_accion)(void);
}STATE;

STATE init_state[] = {         
    {OK_EVENT, splash_state, show_splash},
    {INIT_FAILURE_EVENT, NULL, exit},
    {FIN_TABLE, init_state, doNothing}
}
STATE splash_state[] = {
    {PRESS_EVENT, menu_state, show_menu},
    {FIN_TABLE, splash_state, doNothing}
}
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



int main()
{
    estado_actual=0;
    
    return 0;
}

STATE *fsm_interprete(STATE * p_tabla_estado_actual, EVENT evento_actual)
{
    #ifdef DEBUG
    printf(" >>%c<<\n ",evento_actual); // Para debuggear
    #endif  //DEBUG

    while (p_tabla_estado_actual -> evento != evento_actual && p_tabla_estado_actual -> evento !=FIN_TABLE)
    ++p_tabla_estado_actual;
    
    (*p_tabla_estado_actual -> p_rut_accion) (); // Ejecuta Rutina de accion correspondiente
    p_tabla_estado_actual = p_tabla_estado_actual -> proximo_estado; // Encuentro próximo estado
    return (p_tabla_estado_actual);    
}

