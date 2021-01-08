
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
#define LENG_SC     10  //Dígitos del score SIN terminador.

#define D_WIDTH   800   //Ancho de pantalla
#define D_HEIGHT  600   //Alto de pantalla
#define FPS       60.0

#define FIL_INVADERS 5                   // Cantidad de filas de invaders
#define COL_INVADERS 9                   // Cantidad de columnas de invaders

#define SIZE_FMU    50
#define SIZE_FSC    28
#define SIZE_FGM    20

#define INVADERS_STATES 2


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

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
extern ALLEGRO_FONT *fontgm;

extern ALLEGRO_SAMPLE *shootSound;
extern ALLEGRO_SAMPLE *explosionSound;
extern ALLEGRO_SAMPLE *invaderSound;
extern ALLEGRO_SAMPLE *invaderKilledSound;
extern ALLEGRO_SAMPLE *UFOSound;
extern ALLEGRO_SAMPLE *levelUpSound;
extern ALLEGRO_SAMPLE *finalSong;

extern ALLEGRO_BITMAP *squidPointer[INVADERS_STATES];
extern ALLEGRO_BITMAP *crabPointer[INVADERS_STATES];
extern ALLEGRO_BITMAP *octoPointer[INVADERS_STATES];

extern UFO_t UFO_invader;

/*******************************************************************************
 * FUNCTION PROTOTYPES
 ******************************************************************************/
/**
 * @brief Transforma un entero no signado a un string para luego imprimir.
 * @param num Recibe el numero a transformar.
 * @param chscore[] Recibe el string dode transformara el numero a char
 * @return Devulve el string ya transformado.
*/
void intochar(unsigned long int num, char chscore[LENG_SC]);

/*******************************************************************************
 ******************************************************************************/


#endif // _SHARED_RES_H_
