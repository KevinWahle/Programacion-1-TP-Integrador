/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "timer.h"

#include <stdio.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/**
 * @brief Agrega un timer a la lista de timers
 * @param timer: Timer a establecer.
 * @param delta_clock: tiempo que debe transcurrir hasta que se active
 * el timer.
 * @return 0 si no pasó el tiempo necesario, 1 si pasó el tiempo necesario.
 **/
void setTimer(own_timer_t* timer, double delta_clock) {
    timer->init_clock = clock();  // El tiempo inicial
    timer->delta_clock = delta_clock*CLOCKS_PER_SEC;
    timer->running = 1;
}

/**
 * @brief Verifica si se cumplio el tiempo del timer
 * @param timer el timer a verificar
 * @return 1 si se completo, 0 si no
*/
int checkTimer (own_timer_t *timer) {
    clock_t prev_init = timer->init_clock;
    if(timer->running)
    {
        printf("Timer activado\n");
        timer->init_clock += timer->delta_clock*((clock_t)((clock()-timer->init_clock)/timer->delta_clock));  // Reseteo al ultimo fin de timer
        printf("prev_init = %ld, init_clock = %ld\n",prev_init, timer->init_clock);
    }
    return prev_init != timer->init_clock;   // Solo si se modifico el init_clock, el timer paso su tiempo
}

/**
 * @brief Pausa el contador de un timer
 * @param timer el timer a pausar
*/
// void pauseTimer (own_timer_t *timer) {
//     timer->delta_clock -= clock()/CLOCKS_PER_SEC - timer->init_clock;
//     timer->running = 0;
//     timer->elapsed= (clock()- timer->init_clock)% timer->delta_clock;
// }

// /**
//  * @brief Retome el contador de un timer
//  * @param timer el timer a pausar
// */
// void resumeTimer (own_timer_t *timer) {
//     double time_now = clock()/CLOCKS_PER_SEC;    // Fijo timer
//     timer->init_clock += timer->delta_clock*((int)((time_now-timer->init_clock)/timer->delta_clock));  // Reseteo al ultimo fin de timer
//     timer->running = 1;
// }

/**
 * @brief Resetea el contador de un timer
 * @param timer el timer a resetear
*/
void resetTimer (own_timer_t *timer){
    timer->init_clock = clock();
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 