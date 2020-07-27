/***************************************************************************//**
  @file     +scoretable.c+
  @brief    +Modifica y lee el golbal score+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef _SCORETABLE_H_
#define _SCORETABLE_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/



/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define NAME    6 // Implica que cada nombre tiene que tener 5 letras como máximo
#define LEADERBOARD_SIZE     5 // Tamaño del top


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct     // Estructura que contiene al nombre del usuario con su correspondiente puntaje 
{
    char name[NAME];
    unsigned long int pts;
} SCORE;


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void put_score (char* name, unsigned long int score, const int top, SCORE* my_pun); 
/**
 * @brief Coloca los nombres y scores en un txt odenados
 * @param name: string con el nombres
 * @param score: puntaje asignado al nombre
 * @param top: cantidad de puntjes a mostrar
 * @param mypun: puntero a una posicion de memoria donde se almacenaran los datos del score
 * @return 
*/

int lect_score (SCORE* my_pun); 
/**
 * @brief  Coloco en memoria los datos del score
 * @param mypun: puntero a una posicion de memoria donde se almacenaran los datos del score
 * @return cantidad de personas actuales en el top
*/

/*******************************************************************************
 ******************************************************************************/

#endif // _SCORETABLE_H_


