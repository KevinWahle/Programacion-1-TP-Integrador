
typedef unsigned char BYTE;
//typedef struct state_diagram_edge STATE;

typedef struct state_diagram_edge
{
    BYTE evento;
    STATE *proximo_estado;
    void (*p_rut_accion)(void);
}STATE;

STATE estado_pito[] = {         //TODO: considerar otro nombre del estado
    {Evento1, estado_1, rut_acc1},
    {Evento1, estado_1, rut_acc1}, 
    {Evento1, estado_1, rut_acc1}, 
    {FIN_TABLE, estado_0, rut_acc1}
};


int main()
{
    
    
    return 0;
}

void fsm()
{
    printf(" >>%c<<\n ",evento_actual); // Para debuggear

    while (p_tabla_estado -> evento != evento_actual && p_tabla_estado -> evento !=FIN_TABLA)
    ++p_tabla_estado;
    
    (*p_tabla_estado -> p_rut_accion) (); // 2- Ejecuta Rutina de accion corresondiente
    p_tabla_estado=p_tabla_estado -> proximo_estado; // 3- Encuentro próximo estado
    return(p_tabla_estado);    
}