/***************************************************************************/ /**
  @file     +menu_front.c+
  @brief    +Archivo con recursos principales de RPi para menu y teclado+
  @author   +Grupo 3+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "headall.h"
#include "digits.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define NUMOFFSET       '0'     //Offset de numero entero a char
#define MAYUSOFFSET     'A'     //Offset de letra ascii  
#define MINUSOFFSET     'a'     //Offset de letra ascii
#define LENG_SC         4  
#define RANGE           50      //Rango mínimo de detección del joytick 
#define SCREEN_DELAY    2       //Tiempo que se muestra el splash
#define PAUSE_LAPSE     0.01       //Tiempo que se apreta el analógico para acceder al menu de pausa

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum {A=10,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z};

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
//static BOOL end_game=FALSE;
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

/**
 * @brief Transforma un entero no signado a un string para luego imprimir.
 * @param num Recibe el numero a transformar.
 * @param chscore[] Recibe el string dode transformara el numero a char
 * @return Devulve el string ya transformado.
*/
void intochar(unsigned long int num, char chscore[LENG_SC+1]);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
/**
 * @brief Inicializa los recursos a emplear.
*/
int init_front()
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
    myPoint = (dcoord_t) {0,6};
    for(int i=0; menu_to_show[item].option[i]!='\0' && i<LENG_SC; i++){   //Maximo 4 letras por palabra
        whatisit (menu_to_show[item].option[i]);
        show_matrix (DIGIT_COL, DIGIT_ROW, myPoint); //imprimo la letra (que siempre va a ser de 3*5)
        myPoint.x += 4; //muevo el puntero cuatro posiciones (2 de la letra acutal + el espacio + la nueva letra)
    }

    /*/// PAUSA
    own_timer_t timer_splash;
    setTimer(&timer_splash, SCREEN_DELAY);
    startTimer(&timer_splash);
    while (!checkTimer(&timer_splash));
    /// */
}


/**
 * @brief Muestra el mejor puntaje
*/
void show_score (SCORE* score ,int size)  
{ 
    disp_clear();
    char chscore[LENG_SC+1];
    unsigned long int num = 0;
    myPoint = (dcoord_t) {0,2};
    for(int i=0; i<LENG_SC; i++) {
        whatisit(score[0].name[i]);
        show_matrix (DIGIT_COL, DIGIT_ROW, myPoint); //imprimo la letra (que siempre va a ser de 3*5)
        myPoint.x += DIGIT_COL+1; //muevo el puntero el grosor de la letra + el espacio.
    }

    num=score[0].pts;
    intochar(num,chscore);
    myPoint = (dcoord_t) {0,10};
    for(int i=0; chscore[i]!='\0' && i<LENG_SC; i++) {   //Maximo 4 letras por palabra
        whatisit (chscore[i]);
        show_matrix (DIGIT_COL, DIGIT_ROW, myPoint); //imprimo la letra (que siempre va a ser de 3*5)
        myPoint.x += DIGIT_COL+1; //muevo el puntero el grosor de la letra + el espacio.
    }
}


/**
 * @brief Lee el teclado y carga el evento segun la libreria "event_queue.h".
 **/
void update_front_event (void)
{
    static BOOL was_moving_x = FALSE;   // Indica  si se estaba moviendo el cannon
    static BOOL was_moving_y = FALSE;
    static BOOL press = FALSE;          // Indica si estaba presionado
    static own_timer_t clickTimer;      // Timer para ver cuanto se apretó el joystick.  

    joy_update();                   // Actualizo los valores de joystick
    myCoords = joy_get_coord();     // Tomo las coordenadas actuales
    mySwitch = joy_get_switch();    // Tomo el estado de pulsación del switch


    if (!was_moving_x) {
        if (myCoords.x>RANGE){           
            add_event(MOVE_RIGHT);      // El joytick se mueve hacia la derecha
            was_moving_x=TRUE;
        }
        else if (myCoords.x<-RANGE){
            add_event(MOVE_LEFT);       // El joytick se mueve hacia la izquierda
            was_moving_x=TRUE;
        }
    }
    else if (myCoords.x>-RANGE && myCoords.x<RANGE) {
        add_event(MOVE_LEFT_REL);    
        add_event (MOVE_RIGHT_REL);     // El joytick se soltó
        was_moving_x=FALSE;
    }

    if (!was_moving_y) {
        if (myCoords.y>RANGE){           
            add_event(MOVE_UP);      // El joytick se mueve hacia arriba
            was_moving_y=TRUE;
        }
        else if (myCoords.y<-RANGE){
            add_event(MOVE_DOWN);       // El joytick se mueve hacia abajo
            was_moving_y=TRUE;
        }
    }
    else if (myCoords.y>-RANGE && myCoords.y<RANGE) {
        was_moving_y=FALSE;
    }

    if (mySwitch == J_PRESS && press==FALSE) {
        press = TRUE;                   // Me fijo si esta presionado
        setTimer(&clickTimer, PAUSE_LAPSE);
        startTimer(&clickTimer);
    }
    if (press && (mySwitch == J_NOPRESS) && !checkTimer(&clickTimer)) {
        printf("Se recibió disparo\n");
        printf("checkTimer: %d \n", checkTimer(&clickTimer));
        add_event(CLICK_BTN);           // Me fijo si se solto en MENOS del 
        press = FALSE;                  //tiempo para considerarlo pausa.
    }
    else if (press && (mySwitch == J_NOPRESS) && checkTimer(&clickTimer)){
        printf("Se recibió pausa\n");
        add_event(PAUSE_BTN);           // Me fijo si se solto en MAS del
        press = FALSE;                  //tiempo para considerarlo pausa.
    }

}   


/**
 * @brief Pantalla entre niveles
*/
void show_level_screen (int level) {
    disp_clear();
    char ch[]="LVL";
    char chlevel[LENG_SC+1];
    
    myPoint = (dcoord_t) {3,2};     //Imprime el las letras de Level ("LVL")
    for(int i=0; ch[i]!='\0' && i<LENG_SC; i++) {   //Maximo 4 letras por palabra
        whatisit (ch[i]);
        show_matrix (DIGIT_COL, DIGIT_ROW, myPoint); //imprimo la letra (que siempre va a ser de 3*5)
        myPoint.x += DIGIT_COL+1;   //muevo el puntero el grosor de la letra + el espacio.
    }

    intochar(level,chlevel);        
    myPoint = (dcoord_t) {0,10};    //Imprime el numero del proximo nivel
    for(int i=0; chlevel[i]!='\0' && i<LENG_SC; i++) {   //Maximo 4 letras por palabra
        whatisit (chlevel[i]);
        show_matrix (DIGIT_COL, DIGIT_ROW, myPoint); //imprimo la letra (que siempre va a ser de 3*5)
        myPoint.x += DIGIT_COL+1; //muevo el puntero el grosor de la letra + el espacio.
    }
}


/**
 * @brief Muestra el puntaje al final de la partida y el ingreso del nombre.
*/
void score_name_front(char* actual_name, int size, int letter_counter, unsigned long int score)
{    
    disp_clear();
    char chscore[LENG_SC+1];
    myPoint = (dcoord_t) {0,1};
    
    for(int elemento=0; elemento<LENG_SC; elemento++){              // Imprime los caracteres del nombre.      
        whatisit (actual_name[elemento]);
        show_matrix (DIGIT_COL, DIGIT_ROW, myPoint);
        myPoint.x += DIGIT_COL+1;
    }
    
    for (int i=0; i<DIGIT_COL; i++){        //Imprime la barra que indica la letra   
        if (letter_counter*(DIGIT_COL+1)+i<DISP_CANT_X_DOTS){    
            myPoint = (dcoord_t) {letter_counter*(DIGIT_COL+1)+i, 2+ DIGIT_ROW}; // Columna 4*NUMERO DE LETRA, fila 7 (2 espacios+5 de letra)
            disp_write(myPoint, D_ON);             // Enciendo el led correspondiente    
        }  
    }

    intochar(score,chscore);
    myPoint = (dcoord_t) {0,10};
    for(int i=0; chscore[i]!='\0' && i<LENG_SC; i++) {   //Maximo 4 letras por palabra
        whatisit (chscore[i]);
        show_matrix (DIGIT_COL, DIGIT_ROW, myPoint); //imprimo la letra (que siempre va a ser de 3*5)
        myPoint.x += DIGIT_COL+1; //muevo el puntero el grosor de la letra + el espacio.
    }
} 


/**
 * @brief Finaliza el programa y muestra la imagen de finalización
 **/
void destroy_front(){
    int state;
    disp_clear();
    for(int i=0; i<8; i++) {
        myPoint.y = i+4;
        for(int j=0; j<16; j++) {
            myPoint.x = j;
            state = END_IMG[i][j];
            if (state==1) {
                disp_write(myPoint, D_ON);
            }
            else {
                disp_write(myPoint, D_OFF);
            }
        }
    }
    disp_update();

    own_timer_t timer_splash;
    setTimer(&timer_splash, SCREEN_DELAY);
    startTimer(&timer_splash);
    while (!checkTimer(&timer_splash));

    disp_clear();
    fprintf(stderr, "See you next time...\n\n");
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
    case 0:
        my_char=NUMBER_0;           
        break;
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
        my_char=NULL_CHAR;
        break;
    }
   
}


/**
 * @brief Transforma un entero no signado a un string.
 */
void intochar(unsigned long int num, char chscore[LENG_SC+1])
{
    unsigned long int a = 0;
    
    if(num==0){
        for(int i=0;i<LENG_SC-1;i++){
            chscore[i]=' ';
        }
        chscore[LENG_SC/2]='0';           // Escribo el 0 en el medio de la pantalla.
    }
    else{
        for(int i=LENG_SC-1;i>=0;i--) {
            a = num % 10;                   // Tomo un digito a mostrar.
            if(num>0) {
                chscore[i]=a+NUMOFFSET;     // Si sigo teniendo parte del numero disponible para mostrar
                                            //muestro el nuevo digito.
                num = num / 10;             // Recorto el número para mostrar el nuevo digito.    
            }
            else {
                chscore[i]=' ';              // Si el numero que queda es = a 0, muestro espacios.
            }
        }
    }
    chscore[LENG_SC]='\0';          // Agrego el terminador
}

//TO COMPILE
void show_inst () {}