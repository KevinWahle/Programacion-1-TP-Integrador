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

static MENU_ITEM main_menu[] = {  
                            {.option = "Play", .essential = TRUE},
                            {.option = "Score", .essential = FALSE},
                            {.option = "Options", .essential = FALSE},
                            {.option = "Exit", .essential = TRUE},
                        };

static MENU_ITEM pause_menu[] = {  
                            {.option = "Resume", .essential = TRUE},
                            {.option = "Restart", .essential = TRUE},
                            {.option = "Exit", .essential = TRUE},
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


void show_menu(void){
/* 
    Debe mostrar en el front que sea el menú
    DEBE RETORNAR SI SE MOSTRARON solo los realmentes esenciales (1) o no (0).
    if (ESSENTIAL==TRUE){
        showall();
    }
    else{
        show_essentials();
    }

    return ESSENTIAL;
*/
    MENU ITEM* selectedItem = menu(main_menu);
    switch (selectedItem -> ID) {
        case PLAY:
            break;
        case EXIT:
            break;
    }
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



 