#include <stdio.h>
#include "../const.h"
#include "FSM_table.h"
#include "FSM_routines.h"

enum { PC, RASPI };
#define PLATFORM PC
// Cambiar a por PC o Raspi para compilar para la plataforma adecuada

#if PLATFORM == PC
#include "../Frontend/Allegro/hallegro.h" 
#elif PLATFORM == RASPI
#include "../Frontend/Raspi/....."
#endif


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

        if (get_device_status==BUSY)
        {
            EVENT evento = get_event;
            p_tabla_estado_actual = fsm_interprete(p_tabla_estado_actual, evento);
        }    
    }

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
/*
splash -------toca tecla----show menu {menu}----> menu
        show_menu()
            menu()

loop()        
    evento = espero_evento_front()
    interprete(
        evento = rutina_menu()
        
    )
*/




/*TODO: 
        Definir get_Device_Status. DEBE RETORNAR 0 si no se pasa NADA 
*/