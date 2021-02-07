/***************************************************************************//**
  @file     +ingame_stats.h+
  @brief    +Estadisticas generales del juego+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef _INGAME_STATS_H_
#define _INGAME_STATS_H_

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define MIN_SPEED        1    // Velocidad mínima de los aliens.
#define MAX_SPEED        100  // Velocidad máxima de los aliens.
#define STEP_SPEED       1    // Incremento de la velocidad por unidad de tiempo.
#define STEP_LEVEL_SPEED 10   // Incremento de velocidad por nivel superado.

#define CRAB_POINTS     10    // Puntos ganados por asesinar a un crab.
#define OCTOPUS_POINTS  20    // Puntos ganados por asesinar a un octopus.
#define SQUID_POINTS    30    // Puntos ganados por asesinar a un squid.
#define UFO_POINTS      50    // Unidad de puntaje que genera asesinar un UFO. 
#define MIN_RAND        2     // Multiplicador mínimo por el que se multiplica
                              // la unidad de puntaje de un UFO. 
                              // Min puntaje = MIN_RAND * UFO_POINTS
#define MAX_RAND        4     // Multiplicador máximo por el que se multiplica
                              // la unidad de puntaje de un UFO. 
                              // Max puntaje = MAX_RAND * UFO_POINTS

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief resetea las vidas actuales.
*/
void reset_lives(void);

/**
 * @brief resetea los puntos actuales.
*/
void reset_points(void);

/**
 * @brief resetea el nivel actual.
*/
void reset_level(void);


/**
 * @brief resetea la cantidad de aliens asesinados 
*/
void reset_killed_aliens(void); 

/**
 * @brief Permite decrementar en 1 la cantidad de vidas disponibles
 *  sin necesidad acceder a la variable "lives".
 * @return Retorna las vidas disponibles post-decremento.
*/
int decrease_lives(void);

/**
 * @brief Permite incrementar en 1 la cantidad de vidas disponibles
 *  sin necesidad acceder a la variable "lives".
*/
void increase_lives(void); 

/**
 * @brief Permite incrementar en 1 el número del nivel
 *  sin necesidad acceder a la variable "level".
*/
void increase_level(void);


/**
 * @brief Permite conocer los puntos obtenidos sin necesidad de acceder a
 * la variable "points".
 * @return Retorna la cantidad de puntos obtenidos en la partida.
*/
unsigned long int get_points(void);

/**
 * @brief Permite conocer el nivel actual sin necesidad acceder a
 * la variable "level".
 * @return Retorna el nivel actual.
*/
int get_level(void);

/**
 * @brief Permite conocer el nivel actual sin necesidad acceder a
 * la variable "lives".
 * @return Retorna la cantidad de vidas actuales.
*/
int get_lives();

/**
 * @brief Incrementa el contador de aliens asesinados y tambien los puntos
 * en función a la especie del invasor destruido. 
 * @param tipo_alien: especie invasora que fue destruida.
*/
void kill_alien(const int tipo_alien);

/**
 * @brief Actualiza la velocidad, incrementandola. 
 * @param seg: cada cuantos segundos se quiere incrementar.
*/
void speed_update(const float seg);

/**
 * @brief contabiliza la cantidad de aliens asesinados del tipo
 *        indicado como parámetro. 
 * @param tipo_alien: especie de alien.
*/
unsigned int get_killed_aliens(const int tipo_alien);

/*******************************************************************************
 ******************************************************************************/

#endif // _INGAME_STATS_H_



