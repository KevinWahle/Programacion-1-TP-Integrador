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
#define DEBUG 1

enum EVENTS {
	
	// Eventos que provienen del back.
	INIT_FAILURE_EVENT, 						
	PLAY_EVENT, 
	SCORE_EVENT,
	INSTRUCTION_EVENT,
	RESUME_EVENT,
	PAUSE_EVENT, 
	BACK_EVENT,
	NEXT_LEVEL_EV,
	FIN_TABLE,


	// Eventos que provienen del front y son hardware.
	MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    CLICK_BTN,  // Botón de click, shoot o aceptar
    PAUSE_BTN,

	// Eventos que provienen del front y son sobre el juego.
	CRAB_COLL_EV,
	OCTO_COLL_EV,
	SQUID_COLL_EV,
	UFO_COLL_EV,
	CANNON_COLL_EV,
	
	// Pueden ser del Back o del Front.
	EXIT_EVENT,
	END_GAME_EVENT,
};


enum IDS{
	PLAY_ID,
	SCORE_ID,
	INSTUCTION_ID,
	EXIT_ID,
	RESUME_ID,
	BACK_ID,
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

enum INVADERS{
    CRAB = 0,
    OCTO,
    SQUID,
    UFO,
};
// NOTA: Conviene definirlo así para funciones internas.

#define TYPES_INVADERS	4
#define INIT_LIFES 3

/*******************************************************************************
 ******************************************************************************/

#endif // CONST_H
