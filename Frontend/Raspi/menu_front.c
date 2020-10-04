/***************************************************************************/ /**
  @file     +menu_front.c+
  @brief    +Archivo con recursos principales de RPi para menu y teclado+
  @author   +Grupo 3+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "headall.h"
#include "shared_res.h"
#include "digit.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define NUMOFFSET   '0' //Offset de numero entero a char 
#define RANGE       20  //Rango mínimo de detección del joytick 
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
dcoord_t myPoint;
jcoord_t myCoords;
jswitch_t mySwitch;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
void show_matrix (int *matrix, int col, int row, myPoint coord)

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
int init_front()       // Inicializo y verifico que no falle
{
    disp_init();
    joy_init();
}


/**
 * @brief Muestra el splash.
*/
void splash_front() 
{   
    myPoint = {0,0};   //CAMBIAR POR FUNCION SHOW_MATRIX
    int state = 0;
    for(int i=0; i<16; i++) {
        for(int j=0; j<16; j++) {
            state = SPLASH[i][j];
            if (state==1) {
                disp_write(myPoint, D_ON);
            }
            else {
                disp_write(myPoint, D_OFF);
            }
            myPoint.x++;
        }
        myPoint.y++;
    }
    disp_update();
}


/**
 * @brief Muestra imagen de menu y coloca palabras que recibe y colorea la palabra que se indica.
*/
void show_menu (MENU_ITEM *menu_to_show, int size, int item)
{

}


/**
 * @brief Muestra los mejores puntajes, máximo 10.
*/
void show_score (SCORE* score ,int size) 
{ 

}


/**
 * @brief Lee el teclado y carga el evento segun la libreria "event_queue.h".
 **/
void update_front_event (void)
{
    static BOOL was_moving=FALSE;   // Indica  si se estaba moviendo el cannon 
    joy_update();                   // Actualizo los valores de joystick
    myCoords = joy_get_coord();     // Tomo las coordenadas actuales
    mySwitch = joy_get_switch();    // Tomo el estado de pulsación del switch

    if (myCoords.x>RAGE){           
        add_event(MOVE_RIGHT);      // El joytick se mueve hacia la derecha
        was_moving=TRUE;
    }
    else if (myCoords.x<-RAGE){
        add_event(MOVE_LEFT);       // El joytick se mueve hacia la izquierda
        was_moving=TRUE;
    }
    else if (was_moving==TRUE){     // Si cannon estaba en movimiento y se suelta el joystick, debe parar de moverse
        add_event(MOVE_LEFT_REL);    
        add_event (MOVE_RIGHT_REL);
        was_moving=FALSE;
    }
    
    if (myCoords.y>RAGE){
        add_event(MOVE_UP);         // El joytick se mueve hacia la arriba
    }
    else if (myCoords.y<-RAGE){
        add_event(MOVE_DOWN);       // El joytick se mueve hacia abajo
    }
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
/**
 * @brief Muestra imagen de menu y coloca palabras que recibe y colorea la palabra que se indica.
*/
void show_matrix (int *matrix, int col, int row, myPoint coord)  //NOTA: NO VERIFICA QUE NO TE PASES DE LOS  VALORES DE FILA Y COUMNA
{
    for int (j=0; j<row; j++){  
        for (int i=0; i<col; i++){
            myPoint={i+coord.x,j+coord.y};          //Cargo la matriz que me pasan desde la cordanada indicada
            disp_update();
        }
    }
}