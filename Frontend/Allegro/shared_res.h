
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

#define D_WIDTH   800   //Ancho de pantalla
#define D_HEIGHT  600   //Alto de pantalla
#define FPS       60.0

#define FIL_INVADERS 5                   // Cantidad de filas de invaders
#define COL_INVADERS 9                   // Cantidad de columnas de invaders

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



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

// +ej: extern unsigned int anio_actual;+




/*******************************************************************************
 ******************************************************************************/

#endif // _SHARED_RES_H_
