/*******************************************************************************
  @file     +FSM_routines.h+
  @brief    +Funciones que conforman las rutas de acción entre los diferentes
            estados de la FSM.+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef _FSM_ROUTINES_H_
#define _FSM_ROUTINES_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "scoretable.h"
#include "ingame_stats.h"

//REVISAR: ME PARECE QUE ESTO SE PODRÍA MOVER AL .c (Piensa Basili)
#if PLATFORM == ALLEGRO
#include "../Frontend/Allegro/headall.h" 

#elif PLATFORM == RASPI
#include "../Frontend/Raspi/headall.h" 
#endif

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
extern BOOL running;

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Llama a la función que se encarga del splash
*/
void show_splash(void);


/**
 * @brief Llama a la función que se encarga de mostrar el menu, 
 *        indicandole las opciones a mostrar y la opcion a resaltar
*/
void my_menu(void);


/**
 * @brief Llama a la función que se encarga de mostrar el menu que se le pase, 
 *        indicandole las opciones a mostrar y la opcion a resaltar
 * @param menu menu a mostrar en pantalla
 * @param menu_size tamaño del menu
*/
void up_menu(MENU_ITEM* menu, int menu_size);


/**
 * @brief Llama a la función que se encarga de mostrar el menu que se le pase, 
 *        indicandole las opciones a mostrar y la opcion a resaltar
 * @param menu: menú a mostrar en pantalla.
 * @param menu_size: tamaño del menú.
*/
void down_menu(MENU_ITEM* menu, int menu_size);


/**
 * @brief Añade la opcion seleccionada en el menú general a la cola de eventos.
*/
void click_menu(void);


/**
 * @brief Llama a la función que se encarga de mostrar el menu de pausa, 
 *        indicandole las opciones a mostrar y la opción a resaltar.
*/
void pause_game(void);


/**
 * @brief Reanuda la partida.
*/
void resume_game(void);


/**
 * @brief Inicializa y/o resetea los puntos y las variables propias del juego.
*/
void start_game(void);


/**
 * @brief LLama a la función que se encarga de mostrar el score, indicandole el 
 *        puntaje final y la cantidad de aliens asesinados.
*/
void show_game_score();


/**
 * @brief LLama a la función que se encarga de mostrar el tablero de los top score, 
 *        por constantes del programa se encarga de determinar el tamaño del mismo.
*/
void show_global_score(void);


/**
 * @brief LLama a la función que se encarga de destruir los recursos del front.
*/
void quit_game(void);


/**
 * @brief No hace nada. Su creación fue necesaria a causa de la arquitectura 
 *        de la máquina de estados. 
*/
void doNothing(void);


/**
 * @brief Añade la opcion seleccionada en el menú de pausa a la cola de eventos.
*/
void click_menu_pause(void);


/**
 * @brief Llama a la función encargada de matar al crab.
*/
void crab_coll(void);


/**
 * @brief Llama a la función encargada de matar al octopus.
*/
void octo_coll(void);


/**
 * @brief Llama a la función encargada de matar al squid.
*/
void squid_coll(void);


/**
 * @brief Llama a la función encargada de matar al ufo.
*/
void ufo_coll(void);


/**
 * @brief Decrementa una vida y, si es necesario, agrega el evento
 *        de finalizar evento a la cola de eventos.
*/
void cannon_coll(void);


/**
 * @brief Llama a la función encargada seleccionar la opcion de arriba del menu principal.
*/
void up_menu_main(void);


/**
 * @brief Llama a la función encargada seleccionar la opcion de abajo del menu principal.
*/
void down_menu_main(void);


/**
 * @brief Llama a la función encargada seleccionar la opcion de arriba del menu de pausa.
*/
void up_menu_pause(void);


/**
 * @brief Llama a la función encargada seleccionar la opcion de abajo del menu de pausa.
*/
void down_menu_pause(void);


/**
 * @brief pasa a la letra siguiente del nombre para poder modificarla.
*/
void next_letter(void);

/**
 * @brief vuelve a la letra anterior del nombre para poder modificarla.
*/
void previous_letter(void);

/**
 * @brief pasa a la siguiente letra del abcedario.
*/
void upper_letter(void);

/**
 * @brief pasa a la letra anterior del abcedario.
*/
void lower_letter(void);

/**
 * @brief Guarda en un .txt el puntaje y el nombre correspondiente.
*/
void save_score(void);


/**
 * @brief inicializa las variables para poder cargar el nombre.
*/
void saving_init(void);

/**
 * @brief Actualiza el timer y lo que se muestra en pantalla.
*/
void refresh (void);

/**
 * @brief Llama a la función que se encarga demostrar el nombre del usuario en pantalla 
 *        (para luego vincularlo al puntaje correspondiente).
*/
void show_name(void);

/**
 * @brief Llama a la función que se encarga de mover el cannon hacia la derecha.
*/
void move_cannon_right(void);

/**
 * @brief Llama a la función que se encarga de mover el cannon hacia la izquierda.
*/
void move_cannon_left(void);

/**
 * @brief  Llama a la función del front que detiene el movimiento del cañón.
*/
void stop_cannon(void);


/*******************************************************************************
 ******************************************************************************/

#endif // _FSM_ROUTINES_H_
