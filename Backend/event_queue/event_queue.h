/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

#ifndef _EVENT_QUEUE_H_
#define _EVENT_QUEUE_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define MAX_EVENTS  500

#define NULL_EVENT  ((event_t)(-1))

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef uint16_t event_t;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


/**
 * @brief Agrega un evento a la lista
 * @param event evento a añadir a la cola
 * @return 1 si se completo, 0 si la cola está llena
*/
int add_event(event_t event);

/**
 * @brief Obtiene el próximo evento en la cola
 * @return El último evento de la cola, NULL_EVENT si la cola está vacía
*/
event_t get_next_event(void);

/**
 * @brief Elimina el último elemento agregado a la cola
 * @return 1 si se completo, 0 si la cola está llena
*/
int remove_last_event(void);

//int remove_eventa_at_index(size_t index);

void empty_queue(void);
/*******************************************************************************
 ******************************************************************************/

#endif // _EVENT_QUEUE_H_
