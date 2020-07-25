/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "event_queue.h"

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

static event_t queue[MAX_EVENTS];

static size_t top_of_queue = 0;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int add_event(event_t event) {
    if (top_of_queue < MAX_EVENTS) {        // Si hay lugar en la cola
        for (int i = 0; i < top_of_queue; i++) {
            queue[i+1] = queue[i];              // Muevo todos los eventos 1 posición
        }
        queue[0] = event;   // Agrego el nuevo evento al inicio
        top_of_queue++;     // Aumento tamaño de la cola
        return 0;   // Fin exitoso
    }    
    return 1;       // Error, no hay lugar
}

event_t get_next_event(void) {
    if (top_of_queue > 0) {     // Si hay eventos en la cola
        return queue[--top_of_queue];   // Devuelve ultimo evento y lo elimino de la cola
    }
    return NULL_EVENT;  // No hay eventos
}

int remove_last_event(void) {
    if (top_of_queue > 0) {     // Si hay elementos en la cola
        top_of_queue--;             // Se elimina el último elemento
        return 0;       // Fin exitoso
    }
    return 1;           // Error, no hay elementos
}

void empty_queue(void) {
    top_of_queue = 0;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int main() {
        printArray(queue, 10);
        add_event(1);
        printArray(queue, 10);
        add_event(12;
        printArray(queue, 10);
        add_event(3);
        printArray(queue, 10);
        add_event(4);
        printArray(queue, 10);
        add_event(5);
        printArray(queue, 10);
        add_event(6);
        printArray(queue, 10);
}

printArray(event_t array, size_t size) {
    printf("[ ");
    for (int i = 0l i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("]\n");

}