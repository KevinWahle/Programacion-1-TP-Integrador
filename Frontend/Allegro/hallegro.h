/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
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
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs
#include <allegro5/allegro_audio.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_acodec.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
//Extensiones con acodec .wav, .flac, .ogg, .it, .mod, .s3m, .xm. 


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define D_WIDTH   800
#define D_HEIGHT  600
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
int init_all();

/**
 * @brief Carga la imagenes, fuentes y sonidos.
*/
int load_all();

/**
 * @brief Muestra imagen de carga.
*/
void cargando_ando();

/**
 * @brief Destruye los recursos empleados.
 **/
void destroy_all();


/*******************************************************************************
 ******************************************************************************/

#endif // HALLEGRO_H_