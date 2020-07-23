#include <stdio.h>
#include "../const.h"
#include "FSM_table.h"
#include "FSM_routines.h"


MENU_ITEM menu_items[] = {  "Play",
                            "Score",
                            "etc,",
                            "etc..."
                            };

int main()
{
    static BOOL playing;
    STATE* p_tabla_estado_actual = init_state;

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