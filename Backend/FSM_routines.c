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


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+

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
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void show_splash(void){
    splash_front();
    //TODO
}

void my_menu(){
    mi_var= show_menu (main_menu, 5);
}

void show_menu(MENU_ITEM* menu_to_show, int menu_size, int highlight_item){
 
    //Debe mostrar en el front que sea el menú
    //DEBE RETORNAR SI SE MOSTRARON solo los realmentes esenciales (1) o no (0).
    
    if (ONLY_ESSENTIALS==TRUE){           
        show_all_menu(menu_to_show);
    }
    else{
        show_essentials_menu(menu_to_show);
    }
/*
  
    
    show_menu(main menu); //def en front
    #include "front.h"

    menu_manager()
    if () 



*/
    //return ESSENTIAL;

    /*
    MENU ITEM* selectedItem = menu(main_menu);
    switch (selectedItem -> ID) {
        case PLAY:
            break;
        case EXIT:
            break;
    }
    */
}

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



 