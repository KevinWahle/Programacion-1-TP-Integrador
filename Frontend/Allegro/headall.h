/***************************************************************************//**
  @file     +headall.h+
  @brief    +header principal de allegro+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef HEADALL_H_
#define HEADALL_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "../../const.h"
#include "../../Backend/scoretable.h" //Se necesita libreria para reconocer la estructura SCORE
#include "../../Backend/event_queue/event_queue.h" //Se necesita libreria para reconocer las funcion add_event


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


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
 * @brief Muestra imagen del menu y coloca las palabras que reciba.
 * @param texto[] Recibe un puntero a esturctura de strings
 * @param size Recibe cantidad de palabras a imprimir
 * @param option Recibe un entero indicando que palabra colorear
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
 * @brief Muestra las instrucciones.
*/
void shows_inst ();

/**
 * @brief Lee el teclado y carga el evento segun la libreria "event_queue.h".
 **/
void update_front_event();

/**
 * @brief Destruye los recursos empleados.
 **/
void destroy_front();


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR IN-GAME
 ******************************************************************************/

/**
 * @brief Inicializa los recursos del juego
 * @return 0 si es satisfactorio, otro si hubo error
 **/
int init_game(void);

/**
 * @brief Actualiza lo que se muestra en pantalla durante el juego
*/
void redraw();

/**
 * @brief Actualiza la velocidad del juego
 * @param newSpeed El nuevo valor de velocidad para el juego
*/
void update_speed_front(int newSpeed);

/**
 * @brief Coloca el cannon en la posición al revivir, debajo de un shield
*/
void reviveCanon(void);

/**
 * @brief Ubica a los invaders en la posición inicial
*/
void placeInvaders(void);

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


/*******************************************************************************
 ******************************************************************************/

#endif // HEADALL_H_
