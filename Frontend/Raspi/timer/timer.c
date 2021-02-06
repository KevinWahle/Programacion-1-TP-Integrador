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
 * @param delta_time: tiempo que debe transcurrir hasta que se active
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
        if (timer->init_clock + timer->delta_clock < clock() ) {
            
            timer->init_clock += timer->delta_clock*((clock_t)((clock()-timer->init_clock)/timer->delta_clock));  // Reseteo al último fin de timer
            
        }
        
    }
    
    // return timerup;
    return prev_init != timer->init_clock;   // Solo si se modifico el init_clock, el timer paso su tiempo
}

double getElapsedTime(own_timer_t* timer){
    return (double)((clock()-timer->init_clock))/CLOCKS_PER_SEC;
}

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