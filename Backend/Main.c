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

MENU_ITEM main_menu[] = {  
                            {.option = "Play", .essential = TRUE},
                            {.option = "Score", .essential = FALSE},
                            {.option = "Options", .essential = FALSE},
                            {.option = "Exit", .essential = TRUE},
                        };

MENU_ITEM pause_menu[] = {  
                            {.option = "Resume", .essential = TRUE},
                            {.option = "Restart", .essential = TRUE},
                            {.option = "Exit", .essential = TRUE},
                        };

int main()
{
    static BOOL playing;
    STATE* p_tabla_estado_actual = splash_state;

    if (init_all())             
    {
        return -1;          //init_front inicializa el front sea cual sea la plataforma,
    }                       //Debe estar definida en cada front y returnar !=0 si hay error.
    

    while (playing)
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





/*TODO: 
        Definir get_Device_Status. DEBE RETORNAR 0 si no se pasa NADA 
*/