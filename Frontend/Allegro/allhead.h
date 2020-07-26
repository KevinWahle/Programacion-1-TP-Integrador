/***************************************************************************//**
  @file     +allhead.h+
  @brief    +header principal de allegro+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef HALLEGRO_H_
#define HALLEGRO_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h> //manejo de imagenes
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs
#include <allegro5/allegro_audio.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_acodec.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
//Extensiones con acodec .wav, .flac, .ogg, .it, .mod, .s3m, .xm. 

#include "../../Backend/scoretable.h" //Se necesita libreria para reconocer la estructura score

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define D_WIDTH   800   //Ancho de pantalla
#define D_HEIGHT  600   //Alto de pantalla
#define FPS       60.0

#define FIL_INVADERS 5
#define COL_INVADERS 9


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef unsigned char SHOT_TYPE;

typedef struct 
{
    int x;
    int y;
    int shotState;
    SHOT_TYPE type;
}shot_t;


typedef struct 
{
    int x;
    int y;
    int height;
    int width;
}collBoxShot_t;

typedef struct 
{
    int x;
    int y;
    int invaderState;
    int invaderType;
    ALLEGRO_BITMAP *invadersPointer;
}invader_t;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Inicializa los recursos a emplear.
 * @return Si hubo o no error.
*/
int init_front();

/**
 * @brief Carga la imagenes, fuentes y sonidos.
*/
int load_all();

/**
 * @brief Muestra imagen del menu y coloca las palabras que reciba.
 * @param texto[] Recibe un puntero a esturctura de strings
 * @param size Recibe cantidad de palabras a imprimir
 * @param option Recibe un entero indicando que palabra colorear
*/
void show_menu (char* texto[], int size, int option);

/**
 * @brief Muestra imagen descore y muestra hasta top 10.
 * @param score[] Recibe un puntero a esturctura de que tiene nombres ypuntajes
 * @param size Recibe el tamaño actual de la lista de puntaje
*/
void show_score (SCORE* score ,int size);

/**
 * @brief Muestra las instrucciones.
*/
void shows_inst (void);

/**
 * @brief Destruye los recursos empleados.
 **/
void destroy_front();


/*******************************************************************************
 ******************************************************************************/

#endif // HALLEGRO_H_