/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "FSM_routines.h"
#include "ingame_stats.h"
#include "event_queue/event_queue.h"
#include "const.h"
#include <stdio.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define SEG 1
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

/**********************************************************
***********************  SPLASH   **************************
**********************************************************/

void show_splash(void){     
    splash_front(); //NOTA: incluir donde se encuentra splash_front
    
    #ifdef DEBUG
    printf("Muestro el SPLASH. \n");
    #endif          
}

/**********************************************************
***********************  MENU  **************************
**********************************************************/

void my_menu(){
    actual_option=0;
    show_menu (main_menu, sizeof(main_menu)/sizeof(MENU_ITEM), actual_option);  //Actualizo el menu, resaltando la opcion actualizada.  

    #ifdef DEBUG
        printf("Muestro el menú principal. \n");
    #endif

}

void up_menu(MENU_ITEM* menu, int menu_size){ //REVISAR: HACER
    
    #ifdef ONLY_ESSENTIAL            //NOTA: Alguna razón para no usar #if de precompilador?                                         
            do{                                                                
                if(smenu_ize/sizeof(MENU_ITEM) > actual_option){                         // Si el front solo permite mostrar las opciones esenciales:
                    actual_option++;                                                        //subimos en el menú hasta la siguiente opcion esencial siempre
                }                                                                           //y cuando haya una arriba.
            } while ((menu[actual_option]).essential=FALSE && sizeof(menu)/sizeof(MENU_ITEM) > actual_option);
    
    #else                                                               // Si el front permite mostrar las opciones no esenciales:
        if(menu_size/sizeof(MENU_ITEM) > actual_option){        
            actual_option++;                                                //subimos en el menú hasta la siguiente opcion
        }

    #endif

    #ifdef DEBUG
    printf("La nueva opción actual es: %d \n", main_menu[actual_option].ID);
    #endif 

    show_menu (menu, menu_size/sizeof(MENU_ITEM), actual_option);          // Actualizamos el front. //NOTA: incluir donde se encuentra show_menu()

    #ifdef DEBUG
    printf("Se actualizó el menú");
    #endif 
}

void down_menu(MENU_ITEM* menu, int menu_size){
     #ifdef ONLY_ESSENTIAL            //NOTA: Alguna razón para no usar #if de precompilador?   
        do{
           if(actual_option>0){                                                         // Si el front solo permite mostrar las opciones esenciales:
                actual_option--;                                                        //bajamos en el menú hasta la siguiente opción esencial siempre
           }                                                                            //y cuando haya una abajo.
        } while ((menu[actual_option]).essential=FALSE && actual_option>0);
    
    
    #else                                                               // Si el front permite mostrar las opciones no esenciales:
        
        if(actual_option > 0){
            actual_option--;                                            //bajamos en el menú hasta la siguiente opcion
        }
        
    #endif
    

    #ifdef DEBUG
    printf("La nueva opción actual es: %d \n", main_menu[actual_option].ID);
    #endif 
    
    show_menu (menu, menu_size/sizeof(MENU_ITEM), actual_option);          // Actualizamos el front. 
    //NOTA: incluir donde se encuentra show_menu

    #ifdef DEBUG
    printf("Se actualizó el menú");
    #endif 
}

void click_menu()
{
    int add=0;       
    switch (main_menu[actual_option].ID)
    {
        case PLAY_ID:
            add = add_event(PLAY_EVENT);        // Añadimos a  la cola de eventos
        break;

        case SCORE_ID:
            add = add_event(SCORE_EVENT);       // Añadimos a  la cola de eventos
        break;

        case OPTIONS_ID:
            add = add_event(OPTIONS_EVENT);     // Añadimos a  la cola de eventos
        break;

        case EXIT_ID:
            add = add_event(EXIT_EVENT);        // Añadimos a  la cola de eventos
        break;        
    }
    actual_option=0;

    #ifdef DEBUG
        printf("Se agregó a la cola de eventos: %d \n", main_menu[actual_option].ID);
    #endif      
}

void click_menu_pause()
{
    int add=0;       

    switch (pause_menu[actual_option].ID)
    {
        case PLAY_ID:
            add = add_event(PLAY_EVENT);            // Añadimos a  la cola de eventos
        break;

        case RESUME_ID:
            add = add_event(RESUME_EVENT);          // Añadimos a  la cola de eventos
        break;
        
        case BACK_ID:
            add = add_event(BACK_EVENT);            // Añadimos a  la cola de eventos
        break;
    }

    actual_option=0;

    #ifdef DEBUG
        printf("Se agregó a la cola de eventos: %d \n", main_menu[actual_option].ID);

        if(add==1)
        printf("No se pudo agregar")
        
    #endif 
}

void up_menu_main()
{
    up_menu(main_menu, sizeof(main_menu));
}

void down_menu_main()
{
    down_menu(main_menu, sizeof(main_menu));
}

void up_menu_pause()
{
    up_menu(pause_menu, sizeof(main_menu));
}

void down_menu_pause()
{
    down_menu(pause_menu, sizeof(main_menu));
}

/**********************************************************
*************  PAUSE/RESUME/START/QUIT   ******************
**********************************************************/

void pause_game(void){
    actual_option=0;
    show_menu(pause_menu, sizeof(pause_menu)/sizeof(MENU_ITEM), actual_option);
    //NOTA: Incluir en donde se encuentra show_menu.
    
    #ifdef DEBUG
        printf("Mostrando menú de pausa. \n");
    #endif
}

void resume_game(void){
    
    
    #ifdef DEBUG
        printf("Reanudo partida. \n");
    #endif
}
void start_game(void){
    //CONTINUAR:
    reset_lives();
    reset_points();
    reset_level();
    reset_killed_aliens();
    reset_front();
    //NOTA: Incluir en donde se encuentra reset_front.
    
    #ifdef DEBUG
        printf("Preparo las variables para jugar. \n");
    #endif
}
void quit_game(void) {
    destroy_front();
    //NOTA: Incluir en donde se encuentra destroy_front.
    running=0;

    #ifdef DEBUG
        printf("Salgo del juego. \n");
    #endif
}
/**********************************************************
***********************  SCORE   **************************
**********************************************************/    

void show_game_score(){

    unsigned long long int score= get_points();
    int level= get_level();
    int killed_crabs= get_killed_aliens(CRAB); 
    int killed_octo= get_killed_aliens(OCTOPUS); 
    int killed_squid= get_killed_aliens(SQUID); 
    int killed_ufo= get_killed_aliens(UFO); 
    //CONTINUAR: game_score_front(score, level, killed_crabs, killed_octo, killed_squid, killed_ufo);
    //NOTA: Incluir en donde se encuentra game_score_front.

    #ifdef DEBUG
        printf("Mostrando las estadisticas de la partida. \n");
    #endif
}


void show_global_score(void) {
    SCORE leadboard[LEADERBOARD_SIZE];                     
    SCORE* p_leadboard=leadboard;
    int basura= lect_score(p_leadboard);
    //NOTA: AGREGAR funcion_bustelo (p_leadboard);
    //Incluir Carpeta en la que este la funcion que muestra el leadboard.

    #ifdef DEBUG
        printf("Mostrando Leadboard. \n");
    #endif
}
/**********************************************************
*********************  COLLISION   ************************
**********************************************************/
void crab_coll()
{
    kill_alien(CRAB);       //Ejecutamos la función que guarda en
                            // la info de la partida que se asesinó 
                            // un crab.
}
void octo_coll()
{
    kill_alien(OCTOPUS);    //Ejecutamos la función que guarda en
                            // la info de la partida que se asesinó 
                            // un octopus. 
}

void squid_coll()
{
    kill_alien(SQUID);      //Ejecutamos la función que guarda en
                            // la info de la partida que se asesinó 
                            // un squid. 
}

void ufo_coll()
{
    kill_alien(UFO);        //Ejecutamos la función que guarda en
                            // la info de la partida que se asesinó 
                            // un UFO.    
}

void cannon_coll()
{
    if(decrease_lives()<1)          // Si las vidas llegan a 0,
    {                               //se considera que el jugador ya perdió.
        add_event(END_GAME_EVENT);  

        #ifdef DEBUG
            printf("El jugador se quedó sin vidas");
        #endif
    }

    // NOTA: Agregar si se actualizan las cantidad de vidas en pantalla.
}

/**********************************************************
*********************  VARIOUS   **************************
**********************************************************/

void refresh(void){
    speed_update(SEG);      // Actualizo la velocidad con la que se mueven los invaders.
    redraw();               // Redibujo la pantalla
    //NOTA: incluir donde se encuentre redraw()
}


void doNothing(void) {
//* DO NOTHING*//
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 