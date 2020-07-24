/***************************************************************************/ /**
  @file     +const.h+
  @brief    +Constantes en comun en todo el programa+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef CONST_H
#define CONST_H

#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

enum EVENTS {
	INIT_FAILURE_EVENT, 
//	OK_EVENT,
//	PRESS_EVENT,	
	PLAY_EVENT, 
	SCORE_EVENT,
	OPTIONS_EVENT,
	EXIT_EVENT,
	RESUME_EVENT,
	RESTART_EVENT, 
	PAUSE_EVENT, 
	RETURN_EVENT,
	END_GAME_EVENT,

	MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    CLICK_BTN,  // Botón de click, shoot o aceptar
    PAUSE_BTN,
	FIN_TABLE
};


enum IDS{
	PLAY_ID,
	SCORE_ID,
	OPTIONS_ID,
	EXIT_ID,
	RESUME_ID,
	RESTART_ID,
};

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum COND
{
	FALSE,
	TRUE
};

enum ERRORES		// Distintos tipos de errores
{
	NO_ERROR = -2,
	ERROR = -1
};

typedef uint8_t BOOL;

typedef struct {
	char* option;
	BOOL essential;
	int ID;
} MENU_ITEM;


/*******************************************************************************
 ******************************************************************************/

#endif // CONST_H
