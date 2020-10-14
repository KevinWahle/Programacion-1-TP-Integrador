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
#include "digits.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define NUMOFFSET       '0'     //Offset de numero entero a char
#define MAYUSOFFSET     'A'     //Offset de letra ascii  
#define MINUSOFFSET     'a'     //Offset de letra ascii  
#define RANGE           20      //Rango mínimo de detección del joytick 
#define SPLASH_DELAY    3       //Tiempo que se muestra el splash

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum {A=10,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z};

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
dcoord_t myPoint;
jcoord_t myCoords;
jswitch_t mySwitch;

const int (*my_char)[DIGIT_COL];        // Puntero que apuntara a cada digito a mostrar

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Muestra en pantalla la matriz seleccionada. 
 * @param col Cantidad de columnas
 * @param row Cantidad de filas
 * @param cord ubicacion del display para colocar la matriz
*/
void show_matrix (int col, int row, dcoord_t coord);

/**
 * @brief Reconoce que letra recibe y la transforma a un formato para raspi.
 * @param caracter Caracter que se analiza
*/
void whatisit (char caracter);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
int init_front()       // Inicializo y verifico que no falle
{
    disp_init();
    joy_init();
    return NO_ERROR;
}


/**
 * @brief Muestra el splash.
*/
void splash_front() 
{   
    int state;
    disp_clear();
    for(int i=0; i<8; i++) {
        myPoint.y = i+4;
        for(int j=0; j<16; j++) {
            myPoint.x = j;
            state = SPLASH[i][j];
            if (state==1) {
                disp_write(myPoint, D_ON);
            }
            else {
                disp_write(myPoint, D_OFF);
            }
        }
    }
    disp_update();
}


/**
 * @brief Coloca la palabra que recibe segun item. Una palabra de 4 letras como maximo por pantalla.
*/
void show_menu (MENU_ITEM *menu_to_show, int size, int item)
{
    disp_clear();
    myPoint = (dcoord_t) {0,4};
    for(int i=0; menu_to_show[item].option[i]!='\0' && i<4; i++){   //Maximo 4 letras por palabra
        whatisit (menu_to_show[item].option[i]);
        show_matrix (DIGIT_COL, DIGIT_ROW, myPoint); //imprimo la letra (que siempre va a ser de 3*5)
        myPoint.x = myPoint.x+4; //muevo el puntero cuatro posiciones (2 de la letra acutal + el espacio + la nueva letra)

    } 
}


/**
 * @brief Muestra los mejores puntajes, máximo 10.
*/
void show_score (SCORE* score ,int size) 
{ 
    // NOTA: COMMING SOON!
}


/**
 * @brief Lee el teclado y carga el evento segun la libreria "event_queue.h".
 **/
void update_front_event (void)
{
    static BOOL was_moving = FALSE;   // Indica  si se estaba moviendo el cannon
    static BOOL press = FALSE;
    joy_update();                   // Actualizo los valores de joystick
    myCoords = joy_get_coord();     // Tomo las coordenadas actuales
    mySwitch = joy_get_switch();    // Tomo el estado de pulsación del switch

    if (myCoords.x>RANGE){           
        add_event(MOVE_RIGHT);      // El joytick se mueve hacia la derecha
        was_moving=TRUE;
    }
    else if (myCoords.x<-RANGE){
        add_event(MOVE_LEFT);       // El joytick se mueve hacia la izquierda
        was_moving=TRUE;
    }
    else if (was_moving==TRUE){     // Si cannon estaba en movimiento y se suelta el joystick, debe parar de moverse
        add_event(MOVE_LEFT_REL);    
        add_event (MOVE_RIGHT_REL);
        was_moving=FALSE;
    }
    
    if (myCoords.y>RANGE){
        add_event(MOVE_UP);         // El joytick se mueve hacia la arriba
    }
    else if (myCoords.y<-RANGE){
        add_event(MOVE_DOWN);       // El joytick se mueve hacia abajo
    }
    if (mySwitch == J_PRESS) {
        press = TRUE;
    }
    if (press && mySwitch == J_NOPRESS) {
        add_event(CLICK_BTN);
        press = FALSE;
    }
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
/**
 * @brief Muestra en pantalla la matriz seleccionada.
*/
void show_matrix (int col, int row, dcoord_t cord)  //NOTA: NO VERIFICA QUE NO TE PASES DE LOS  VALORES DE FILA Y COUMNA
{
    dcoord_t myPunto;
    for (int j=0; j<row; j++){  
        for (int i=0; i<col; i++){
            myPunto = (dcoord_t) {i+cord.x,j+cord.y};               //Cargo la matriz que me pasan desde la cordanada indicada y voy incrementando su puntero
            if (my_char[j][i]==1) {
                disp_write(myPunto, D_ON);             // Enciendo el led correspondiente
            }
            else {
                disp_write(myPunto, D_OFF);           // Enciendo el led correspondiente
            }
        }
    }
    disp_update();                                    // Muestro en pantalla   
}


/**
 * @brief Reconoce que letra recibe y la transforma a un formato para raspi.
*/
void whatisit (char caracter) 
{    
    if (caracter-NUMOFFSET>=0  &&  caracter-NUMOFFSET<=9) {     //Los números van de 0 a 9
        caracter = caracter - NUMOFFSET;
    }
    else {                                                      // Las letras comienzan desde 10
        if (caracter>=MINUSOFFSET){
            caracter = caracter - MINUSOFFSET + 10;             // En minúscula         
        }
        else{
            caracter= caracter - MAYUSOFFSET + 10;               // En mayuscula
        }
    }

    switch (caracter)                                           // Guardo los punteros al caracter seleccionado 
    {    
    case 1:
        my_char=NUMBER_1;           
        break;
    case 2:
        my_char=NUMBER_2;
        break;    
    case 3:
        my_char=NUMBER_3;
        break;
    case 4:
        my_char=NUMBER_4;
        break;
    case 5:
        my_char=NUMBER_5;
        break;
    case 6:
        my_char=NUMBER_6;
        break;
    case 7:
        my_char=NUMBER_7;
        break;
    case 8:
        my_char=NUMBER_8;
        break;
    case 9:
        my_char=NUMBER_9;
        break;
    case A:
        my_char=LETTER_A;
        break;
    case B:
        my_char=LETTER_B;
        break; 
    case C:
        my_char=LETTER_C;
        break; 
    case D:
        my_char=LETTER_D;
        break; 
    case E:
        my_char=LETTER_E;
        break; 
    case F:
        my_char=LETTER_F;
        break; 
    case G:
        my_char=LETTER_G;
        break; 
    case H:
        my_char=LETTER_H;
        break; 
    case I:
        my_char=LETTER_I;
        break; 
    case J:
        my_char=LETTER_J;
        break; 
    case K:
        my_char=LETTER_K;
        break;
    case L:
        my_char=LETTER_L;
        break; 
    case M:
        my_char=LETTER_M;
        break; 
    case N:
        my_char=LETTER_N;
        break; 
    case O:
        my_char=LETTER_O;
        break; 
    case P:
        my_char=LETTER_P;
        break; 
    case Q:
        my_char=LETTER_Q;
        break; 
    case R:
        my_char=LETTER_R;
        break; 
    case S:
        my_char=LETTER_S;
        break; 
    case T:
        my_char=LETTER_T;
        break;     
    case U:
        my_char=LETTER_U;
        break; 
    case V:
        my_char=LETTER_V;
        break; 
    case W:
        my_char=LETTER_W;
        break; 
    case X:
        my_char=LETTER_X;
        break; 
    case Y:
        my_char=LETTER_Y;
        break; 
    case Z:
        my_char=LETTER_Z;
        break;    
    default:
        break;
    }
   
}


// SOLO PARA PODER COMPILAR:

void show_inst(){}

void destroy_front(){
    disp_clear();
    printf("Nos vimos!\n");
}

void score_name_front(char* actual_name, int size, int letter_counter, unsigned long int score){}
