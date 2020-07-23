
typedef unsigned char BYTE;
typedef struct state_diagram_edge STATE;

struct state_diagram_edge{
    BYTE evento;
    STATE *proximo_estado;
    void (*p_rut_accion)(void);
};



int main()
{
    
    
    return 0;
}