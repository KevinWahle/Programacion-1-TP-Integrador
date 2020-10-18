/***************************************************************************//**
  @file     +headall.h+
  @brief    +Header principal de allegro+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef HEADALL_H_
#define HEADALL_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "../../RPi_Files/joydisp/disdrv.h"
#include "../../RPi_Files/joydisp/joydrv.h"
#include "../../RPi_Files/audio/SDL1/libaudio.h"

#include "../../const.h"
#include "timer/timer.h"    //Libreria de timer para delays
#include "../../Backend/scoretable.h" //Se necesita libreria para reconocer la estructura SCORE
#include "../../Backend/event_queue/event_queue.h" //Se necesita libreria para reconocer las funcion add_event

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define ONLY_ESSENTIAL 

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum DIRECTIONS {LEFT, RIGHT, STOP, ERROR_DIREC}; // SOLUCIONAR LO DE ERROR_DIREC!!!! RANCIO

typedef uint8_t direction_t;  // Necesario para move_cannon()

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR MENU AND KEYBOARD
 ******************************************************************************/
void show_inst ();

/**
 * @brief Inicializa los recursos a emplear.
 * @return Si hubo o no error.
*/
int init_front();

/**
 * @brief Muestra el splash.
*/
void splash_front(); 

/**
 * @brief Coloca la palabra que recibe segun item. Una palabra de 4 letras como maximo por pantalla.
 * @param *menu_to_show Recibe un puntero a esturctura de strings
 * @param size Recibe cantidad de palabras a imprimir, no es necesaria en raspi ya que muestra una palabra por pantalla
 * @param item Recibe un entero indicando que palabra mostrar
*/
void show_menu (MENU_ITEM *menu_to_show, int size, int item);

/**
 * @brief Muestra imagen de score y muestra hasta top 10.
 * @param score[] Recibe un puntero a esturctura de que tiene nombres ypuntajes
 * @param size Recibe el tamaño actual de la lista de puntaje
*/
void show_score (SCORE* score ,int size);

/**
 * @brief Muestra imagen de score y muestra el punjate final de partida
 * @param actual_name Recibe un puntero a el nombre que quiere ingresar el usiario
 * @param size Recibe el largo del arreglo
 * @param letter_counter  Recibe la letra a resaltar (va de 0 a size-1)
 * @param score Puntaje de final de partida
*/
void score_name_front(char* actual_name, int size, int letter_counter, unsigned long int score);

/**
 * @brief Lee el teclado y carga el evento segun la libreria "event_queue.h".
 **/
void update_front_event();

/**
 * @brief Finaliza el programa y muestra la imagen de finalización
 **/
void destroy_front();

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR IN-GAME
 ******************************************************************************/
/**
 * @brief Inicializa lo necesario para empezar la partida
*/
void init_game(void);

/**
 * @brief Actualiza lo que se muestra en pantalla durante el juego
*/
void redraw(unsigned long int score, int lives, int level);

/**
 * @brief Ubica a los invaders en la posición inicial
*/
void placeInvaders(void);

/**
 * @brief Pantalla entre niveles
*/
void show_level_screen (int level);

/**
 * @brief Actualiza la velocidad del juego
 * @param newSpeed El nuevo valor de velocidad para el juego
*/
void update_speed_front(int newSpeed, int maxSpeed);

/**
 * @brief Coloca el cannon en la posición al revivir, debajo de un shield
*/
void reviveCanon(void);

/**
 * @brief Ejecuta un disparo del canon
 * @return TODO?: CODIGO DE ERROR?
*/
void shoot_cannon(void);

/**
 * @brief Solicita un movimiento continuo del cannon en la direccion indicada
 * @param dir la direccion a la que se desea mover. STOP si se desea parar
*/
void move_cannon(direction_t dir);

/**
 * @brief Elimina los disparos actuales
*/
void clean_shoots(void);

/**
 * @brief Imprime estadísticas de final de partida
*/
void game_score_front(unsigned long int score, int level, int killed_crabs, int killed_octo, int killed_squid, int killed_ufo);

/**
 * @brief Detiene los eventos innecesarios durante la pausa
*/
void pause_game_front(void);

/**
 * @brief Vuelve a escuchar notificaciones
*/
void resume_game_front(void);

/**
 * @brief Verifica si se mataron a todos los invaders
 * @return 1 si estan todos muertos, 0 si no.
*/
int checkWin(void);

/*******************************************************************************
 ******************************************************************************/

#endif // HEADALL_H_