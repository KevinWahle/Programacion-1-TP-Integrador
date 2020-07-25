#include <stdio.h>
#include "../const.h"
#include "FSM_table.h"
#include "FSM_routines.h"
#include "event_queue.h"

enum { PC, RASPI };
#define PLATFORM PC
// Cambiar a por PC o Raspi para compilar para la plataforma adecuada

#if PLATFORM == PC
#include "../Frontend/Allegro/hallegro.h" 
#elif PLATFORM == RASPI
#include "../Frontend/Raspi/....."
#endif


event_t back_event_queue[MAX_EVENTS];

int main()
{
    static BOOL running;
    STATE* p_tabla_estado_actual = splash_state;

    if (init_front())             
    {
        return -1;          //init_front inicializa el front sea cual sea la plataforma,
    }                       //Debe estar definida en cada front y returnar !=0 si hay error.
    
    splash_front();

    while (running)
    {
        event_t evento = get_next_event;

        if (evento!= NULL_EVENT)
        {
            p_tabla_estado_actual = fsm_interprete(p_tabla_estado_actual, evento);
        }    
    }

    return 0;
}

STATE *fsm_interprete(STATE * p_tabla_estado_actual, event_t evento_actual)
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
