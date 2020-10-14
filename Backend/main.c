#include <stdio.h>
#include "../const.h"
#include "FSM_table.h"
#include "FSM_routines.h"
#include "event_queue/event_queue.h"

int main(void)
{
    STATE* p_tabla_estado_actual = splash_state;

    if (init_front()!=NO_ERROR) {                         // init_front inicializa el front sea cual sea la plataforma,       
                                                //si hay error de inicialización corta el programa.
        #ifdef DEBUG
            printf("Error de inicialización\n");
        #endif

        return -1;          
    }   

    show_splash();

    while (running)
    {
        update_front_event();               // Actualizar la lista de eventos que me indica el front.
        event_t evento = get_next_event();  // Tomo un nuevo evento de la cola de eventos.
        
        #ifdef DEBUG
            if (evento != 65535){
            printf("El nuevo evento es: %d \n", evento);
            }
        #endif

        p_tabla_estado_actual = fsm_interprete(p_tabla_estado_actual, evento);  // Actualizo el estado
    }

    return 0;
}

STATE *fsm_interprete(STATE * p_tabla_estado_actual, event_t evento_actual)
{
    #ifdef DEBUG
    //printf("Evento: %d. \n", evento_actual); // Para debuggear
    #endif  //DEBUG

    while ((p_tabla_estado_actual -> evento) != evento_actual && (p_tabla_estado_actual -> evento) !=NULL_EVENT){
        ++p_tabla_estado_actual;
    }
    

    (p_tabla_estado_actual -> p_rut_accion) (); // Ejecuta Rutina de accion correspondiente
    p_tabla_estado_actual = (p_tabla_estado_actual -> proximo_estado); // Encuentro próximo estado
    return (p_tabla_estado_actual);    
}
