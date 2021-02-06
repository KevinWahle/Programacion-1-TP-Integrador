/***************************************************************************//**
  @file     +const.h+
  @brief    +Constantes en comun en todo el programa+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef CONST_H
#define CONST_H

// Las defino como constantes != 0 para detectar si no se define PLATFORM
#define ALLEGRO 'A'
#define RASPI  'R'

#if (PLATFORM!=ALLEGRO && PLATFORM!=RASPI)
	#error La plataforma no es valida o no ha sido definida. Defina la plataforma compilando con -D PLATFORM=[ALLEGRO/RASPI]
#endif

#if PLATFORM==ALLEGRO 
    #undef	ONLY_ESSENTIAL		//Borramos el identificador que oculta los menus secundarios.
#elif PLATFORM==RASPI
    #define ONLY_ESSENTIAL		//Definimos el identificador que oculta los menus secundarios.
#endif


#include <stdint.h>
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
//#define DEBUG 1

enum EVENTS {
	
	// Eventos que provienen del back.
	INIT_FAILURE_EVENT, 						
	PLAY_EVENT, 
	SCORE_EVENT,
	INSTRUCTION_EVENT,
	RESUME_EVENT,
	BACK_EVENT,
	NEXT_LEVEL_EV,
	FIN_TABLE,


	// Eventos que provienen del front y son hardware.
	
	// Eventos de apretado de tecla
	MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    CLICK_BTN,  // Botón de click: se usa tanto para shoot como para aceptar
    PAUSE_BTN,	// Botón con el que se accede al menú de pausa
	
	// Eventos de soltado de tecla:
    MOVE_LEFT_REL,
    MOVE_RIGHT_REL,

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

// Identificadores para diferenciar las distintas opciones 
// seleccionadas en el menú.
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

// Estructura utilizada para cada una de las opciones clickeables 
// en los diferentes menúes.
typedef struct {
	char* option;
	BOOL essential;
	int ID;
} MENU_ITEM;

// Identificadores para las diferentes especies de invaders.
// NOTA: Conviene definirlo así para funciones internas.
enum INVADERS{
    CRAB = 0,
    OCTO,
    SQUID,
    UFO,
};

#define TYPES_INVADERS	4	// Cantidad de especies de invaders.
#define INIT_LIFES 3		// Cantidad inicial de vidas por partida.

/*******************************************************************************
 ******************************************************************************/

#endif // CONST_H