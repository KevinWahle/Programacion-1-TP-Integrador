/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "FSM_routines.h"
#include "const.h"
#include <stdio.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+

MENU_ITEM main_menu[] = {  
                            {.option = "Play", .essential = TRUE, .ID = PLAY_ID},
                            {.option = "Score", .essential = FALSE, .ID = SCORE_ID},
                            {.option = "Options", .essential = FALSE, .ID = OPTIONS_ID},
                            {.option = "Exit", .essential = TRUE, .ID = EXIT_ID},
                        };
 

MENU_ITEM pause_menu[] = {  
                            {.option = "Resume", .essential = TRUE, .ID = RESUME_ID},
                            {.option = "Restart", .essential = TRUE, .ID = PLAY_ID},
                            {.option = "Back to menu", .essential = TRUE, .ID= BACK_ID} ,
                        };

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/



/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static actual_option = 0;



/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

// NOTA: no se usa.
int essentials_count (int cant){ 
     int cant_essentials=0;
    for(int i=0; i<cant; i++)
    {
        if((main_menu[i]).essential==TRUE)
        {
            cant_essentials++ ;             
        }        
    }
    return cant_essentials;
}

void show_splash(void){     
    splash_front();
    
    #ifdef DEBUG
    printf("Muestro el SPLASH. \n");
    #endif          
}

void my_menu(){
    actual_option=0;
    show_menu (main_menu, sizeof(main_menu)/sizeof(MENU_ITEM), actual_option);  //Actualizo el menu, resaltando la opcion actualizada.  

    #ifdef DEBUG
        printf("Muestro el menú principal. \n");
    #endif

}

void up_menu(){
if (ONLY_ESSENTIAL){                                                    
        do{                                                                
           if(sizeof(main_menu)/sizeof(MENU_ITEM) > actual_option){                     // Si el front solo permite mostrar las opciones esenciales:
                actual_option++;                                                        //subimos en el menú hasta la siguiente opcion esencial siempre
           }                                                                            //y cuando haya una arriba.
        } while ((main_menu[actual_option]).essential=FALSE && sizeof(main_menu)/sizeof(MENU_ITEM) > actual_option);
    }
    
    else{                                                               // Si el front permite mostrar las opciones no esenciales:
        if(sizeof(main_menu)/sizeof(MENU_ITEM) > actual_option){        
        actual_option++;                                                //subimos en el menú hasta la siguiente opcion
        }
    }

    #ifdef DEBUG
    printf("La nueva opción actual es: %d \n", main_menu[actual_option].ID);
    #endif 

    show_menu (main_menu, sizeof(main_menu)/sizeof(MENU_ITEM), actual_option);          // Actualizamos el front.

    #ifdef DEBUG
    printf("Se actualizó el menú");
    #endif 
}

void down_menu(){
    if (ONLY_ESSENTIAL){
        do{
           if(actual_option>0){                                                         // Si el front solo permite mostrar las opciones esenciales:
                actual_option--;                                                        //bajamos en el menú hasta la siguiente opción esencial siempre
           }                                                                            //y cuando haya una abajo.
        } while ((main_menu[actual_option]).essential=FALSE && actual_option>0);
    }
    
    else{                                                               // Si el front permite mostrar las opciones no esenciales:
        if(actual_option > 0){
            actual_option--;                                            //bajamos en el menú hasta la siguiente opcion
        }
    }
    
    #ifdef DEBUG
    printf("La nueva opción actual es: %d \n", main_menu[actual_option].ID);
    #endif 
    
    show_menu (main_menu, sizeof(main_menu)/sizeof(MENU_ITEM), actual_option);          // Actualizamos el front.

    #ifdef DEBUG
    printf("Se actualizó el menú");
    #endif 
}

void click_menu()
{
    int add;        // WARNING: Deberia estar inicializada (por las dudas)
    switch (main_menu[actual_option].ID)
    {
        case PLAY_ID:
            add = add_event(PLAY_EVENT);
        break;

        case SCORE_ID:
            add = add_event(SCORE_EVENT); 
        break;

        case OPTIONS_ID:
            add = add_event(OPTIONS_EVENT);
        break;

        case EXIT_ID:
            add = add_event(EXIT_EVENT);
        break;        
    }
    actual_option=0;

    #ifdef DEBUG
        printf("Se agregó a la cola de eventos: %d \n", main_menu[actual_option].ID);
    #endif      
}

void click_menu_pause()
{
    int add;        // WARNING: Deberia estar inicializada (por las dudas)

    switch (pause_menu[actual_option].ID)
    {
        case PLAY_ID:
            add = add_event(PLAY_EVENT);
        break;

        case RESUME_ID:
            add = add_event(RESUME_EVENT);
        break;
        
        case BACK_ID:
            add = add_event(BACK_EVENT);
        break;
    }

    actual_option=0;

    #ifdef DEBUG
        printf("Se agregó a la cola de eventos: %d \n", main_menu[actual_option].ID);

        if(add==1)
        printf("No se pudo agregar")
        
    #endif 
}


void pause_game(void){
    actual_option=0;
    show_menu(pause_menu, sizeof(pause_menu)/sizeof(MENU_ITEM), actual_option);

    #ifdef DEBUG
        printf("Mostrando menú de pausa. \n");
    #endif
}

void resume_game(void){
    
    
    #ifdef DEBUG
        printf("Reanudo partida. \n");
    #endif
}
    
void show_game_score(unsigned long long int score){
    //CONTINUAR: funcion_front (cantidad de bichos muertos de cada tipo,...,pts,nivel);

    #ifdef DEBUG
        printf("Mostrando las estadisticas de la partida. \n");
    #endif
}

void start_game(void){
    //CONTINUAR:
    reset_lives();
    reset_points();
    reset_shields();
    reset_level();
    
    #ifdef DEBUG
        printf("Preparo las variables para jugar. \n");
    #endif
}

void show_global_score(void) {
    SCORE leadboard[LEADERBOARD_SIZE];                     
    SCORE* p_leadboard=leadboard;
    int basura= lect_score(p_leadboard);
    //NOTA: AGREGAR funcion_bustelo (p_leadboard);

    #ifdef DEBUG
        printf("Mostrando Leadboard. \n");
    #endif
}

void quit_game(void) {
    destroy_front();
    show_game_score(score); //TODO: crear score
    running=0;

    #ifdef DEBUG
        printf("Salgo del juego. \n");
    #endif
}

void doNothing(void) {
//* DO NOTHING*//
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 