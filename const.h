/***************************************************************************/ /**
  @file     +const.h+
  @brief    +Constantes en comun en todo el programa+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef CONST_H
#define CONST_H

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
enum EVENTS {
	INIT_FAILURE_EVENT, 
	OK_EVENT,
	PRESS_EVENT,
	SCORE_EVENT,
	EXIT_EVENT, 
	RESTART_EVENT, 
	CONTINUE_EVENT,
	PAUSE_EVENT, 
	RETURN_EVENT,
	END_GAME_EVENT,
	FIN_TABLE
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


/*******************************************************************************
 ******************************************************************************/

#endif // CONST_H
