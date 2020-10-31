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
void setTimer(own_timer_t* timer, double delta_time) {
    timer->delta_clock = delta_time*CLOCKS_PER_SEC;
    timer->running = 0;
}

/**
 * @brief Inicia el contador del timer
 * @param timer: Timer a iniciar
 **/
void startTimer(own_timer_t* timer) {
    timer->running = 1;
    timer->init_clock = clock();  // El tiempo inicial
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
        timer->init_clock += timer->delta_clock*((clock_t)((clock()-timer->init_clock)/timer->delta_clock));  // Reseteo al ultimo fin de timer
    }
    if (timer->delta_clock > 0.1*CLOCKS_PER_SEC) {
        printf("Tiempo restante del timer : %lu \n", (timer->delta_clock-(clock()-timer->init_clock))/CLOCKS_PER_SEC );
    }
    return prev_init != timer->init_clock;   // Solo si se modifico el init_clock, el timer paso su tiempo
}

// /**
//  * @brief Pausa el contador de un timer
//  * @param timer el timer a pausar
// */
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
 * @brief Detiene el timer
 * @param timer el timer a detener
*/
void stopTimer (own_timer_t *timer){
    timer->running = 0;
}

/**
 * @brief Resetea el contador de un timer, no modifica el estado del timer
 * @param timer el timer a resetear
*/
void resetTimer (own_timer_t *timer){
    timer->init_clock = clock();
} 