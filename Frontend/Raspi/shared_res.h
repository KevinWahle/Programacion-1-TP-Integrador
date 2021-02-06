/***************************************************************************//**
  @file     +shared_res.h+
  @brief    +Recursos compartidos entre los archivos del frontend allegro+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef SHARED_RES_H
#define SHARED_RES_H

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define UFO_SOUND_TIME  0.5  

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <SDL2/SDL.h>
#include "../../../libs/joydisp/disdrv.h"
#include "../../../libs/joydisp/joydrv.h"
#include "../../../libs/audio/SDL2/src/audio.h"

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
extern Audio * shootSound;
extern Audio * invaderSound;
extern Audio * explosionSound;
extern Audio * invKillSound;
extern Audio * ufoSound;

extern Audio * keyMoved;
extern Audio * levelUp;
extern Audio * finalSong;

/*******************************************************************************
 ******************************************************************************/

#endif // _SHARED_RES_H_