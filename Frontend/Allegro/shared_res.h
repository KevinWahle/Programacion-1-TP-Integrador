
/***************************************************************************//**
  @file     +shared_res.h+
  @brief    +Recursos compartidos entre los archivos del frontend allegro+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef _SHARED_RES_H_
#define _SHARED_RES_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h> //manejo de imagenes
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
//Extensiones con acodec .wav, .flac, .ogg, .it, .mod, .s3m, .xm.

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define D_WIDTH   800   //Ancho de pantalla
#define D_HEIGHT  600   //Alto de pantalla
#define FPS       60.0

#define FIL_INVADERS 5                   // Cantidad de filas de invaders
#define COL_INVADERS 9                   // Cantidad de columnas de invaders


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

// Objeto invader
typedef struct 
{
    float x;
    float y;
    int invaderState;    // Si esta vivo o muerto 
    int invaderType;
    ALLEGRO_BITMAP *invadersPointer;   // Puntero util para asociarlo al bitmap
}invader_t;

// Objeto UFO
typedef struct 
{
    float x;
    float y;
    int invaderState;
    int invaderType;
    direction_t direction;      //  El UFO puede aparecer desde la izquierda o desde la derecha
    ALLEGRO_BITMAP *invadersPointer;
} UFO_t;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *canonPointer;
extern ALLEGRO_EVENT_QUEUE *timer_queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_FONT *fontsc;

// Invaders matrix
extern invader_t invaders[FIL_INVADERS][COL_INVADERS];

extern const int invadersDistribution[FIL_INVADERS];

extern UFO_t UFO_invader;

/*******************************************************************************
 ******************************************************************************/

#endif // _SHARED_RES_H_
