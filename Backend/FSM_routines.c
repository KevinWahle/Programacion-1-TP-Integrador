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
                            {.option = "Restart", .essential = TRUE, .ID = RESTART_ID},
                            {.option = "Exit", .essential = TRUE, .ID= EXIT_ID} ,
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
    //TODO
}

void my_menu(){
    show_menu (main_menu, sizeof(main_menu)/sizeof(MENU_ITEM), actual_option);  //Comienza pasando el menu, resaltando la primera opcion
    
}

void up_menu(){
    if (ESSENTIAL){
        do{
           if(sizeof(main_menu)/sizeof(MENU_ITEM) > actual_option){
                actual_option++;            
           }
        } while ((main_menu[actual_option]).essential=FALSE && sizeof(main_menu)/sizeof(MENU_ITEM) > actual_option);

        show_menu (main_menu, sizeof(main_menu)/sizeof(MENU_ITEM), actual_option);
    }
    
    else{
        if(sizeof(main_menu)/sizeof(MENU_ITEM) > actual_option){
            actual_option++;
            show_menu (main_menu, sizeof(main_menu)/sizeof(MENU_ITEM), actual_option);
        }
    }
}

void down_menu(){
    if (ESSENTIAL){
        do{
           if(actual_option>0){
                actual_option--;            
           }
        } while ((main_menu[actual_option]).essential=FALSE && actual_option>0);

        show_menu (main_menu, sizeof(main_menu)/sizeof(MENU_ITEM), actual_option);
    }
    
    else{
        if(actual_option > 0){
            actual_option--;
            show_menu (main_menu, sizeof(main_menu)/sizeof(MENU_ITEM), actual_option);
        }
    }
}

void click_menu()
{
        
}
/*
void show_menu(MENU_ITEM* menu_to_show, int menu_size, int highlight_item){
 
    //Debe mostrar en el front que sea el menú
    //DEBE RETORNAR SI SE MOSTRARON solo los realmentes esenciales (1) o no (0).
    
    if (ONLY_ESSENTIALS==TRUE){           
        show_all_menu(menu_to_show);
    }
    else{
        show_essentials_menu(menu_to_show);
    }
}
*/
void pause_game(void){
    //TODO
}

void resume_game(void){
    //TODO
}

void restart_game(void){
    //TODO
}

void end_game(void){
    //TODO
}

void show_global_score(void) {
    //TODO
}

void quit_game(void) {
    //TODO
}

void doNothing(void) {
//* DO NOTHING*//
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 