#include <stdio.h>
#include <stdint.h>


#include "raspi_front_hder.h"

#define D_WIDTH 16
#define D_HEIGHT 16

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

enum blockStates {STATE_0, STATE_1, STATE_2, STATE_3, STATE_4};   // STATE_0 seria el estado del bloque sin danios. STATE_4 en este caso es el ultimo estado


enum MYKEYS {
    KEY_SPACE, KEY_DOWN, KEY_LEFT, KEY_RIGHT //arrow keys
};

// Objeto shot
typedef struct  
{
    float x;              // su posicion
    float y;
    int shotState;       // si "existe" o no
}shot_t;

// Objeto caja de disparo. A todos los objetos capaces de colisionar, para la dteccion de colision se le arma una caja de colision que sirve para el algoritmo de deteccion de colision
typedef struct 
{
    int x;         // Alcanza con la posicion del punto de arriba a la izquierda de la caja y el ancho y largo
    int y;
    int height;
    int width;
}collBoxShot_t;

//Objeto bloque
typedef struct 
{
    int x;
    int y;
    int height;
    int width;
    int state;           // Ya vimos que puede tener varios estados
}block_t;

//Objeto shield
typedef struct
{
    block_t block_1;     //Aclaracion: El shield tiene 5 blocks. Por eso no se puede hacer un shields con mas o menos blocks
    block_t block_2;     // No se pueden agregar bloques asi porque si al shield porque cada blocke debe ser codiado su posicion
}shield_t;

typedef int cannonPosition_t;

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE (SOLO PARA SHARED_RES)
 ******************************************************************************/

/************ALLEGRO VARIABLES DEFINITION***************/

// Invaders matrix
invader_t invaders[FIL_INVADERS][COL_INVADERS];

UFO_t UFO_invader = {   .y = UFO_HEIGHT,
                        .invaderType = UFO,
                        .invaderState = 0     //Arranca muerta
                    };

const int invadersDistribution [FIL_INVADERS] = {
                                                  SQUID,
                                                  CRAB,
                                                  CRAB,
                                                  OCTO,
                                                  OCTO,
                                                  };


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// Lista de los disparos de los invaders.
static shot_t invaderShotList[MAX_INVADERS_SHOT];

// Contador de la cantidad de balas disparadas por los invaders
static int actualInvadersShots; 
// Contador de la cantidad de balas disparadas por el canon
static int actualCanonShots;



// El cañón
static cannonPosition_t cannonXpos = 0;
static direction_t cannonDir = STOP;

static shot_t canonShotList[MAX_CANON_SHOT];

static direction_t proxDir = LEFT;

//TASAS DE CAMBIO VARIABLES:

static float dxInvader;
static float shotFromInvaderFrec;

static shield_t shielders[TOTAL_SHIELDS];

// Velocidades y probabilidades variables
static float tasaDeCambioInvaders = MIN_SPEED_INVADER;
static int probDisparoInvaders = MIN_POSIBILIY_OF_SHOT_FROM_INVADERS;
static int probUfo = MIN_POSIBILIY_OF_APPEAR_UFO;


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Ejecuta un disparo del invader
 * @param1 i fila de la matriz de invader
 * @param2 j columan de la matriza de invader
*/
static void invaderShot(int i, int j);

/**
 * @brief Ve si hubo una colision del disparo ejecutado por algun invader
*/
static void getInvaderShotCollison(void);

/**
 * @brief Ve si hubo una colision del disparo ejecutado por el canon
*/
static void getCanonShotCollision(void);

/**
 * @brief Mueve el conjunto invader
 * @param direction La ultima direccion con la que se movio el conjunto invader
 * @return La direccion con la que se movio
*/
static direction_t moveInvaders(direction_t direction);

/**
 * @brief Mueve el conjunto para abajo
*/
static void moveInvadersDown(void);

/**
 * @brief Dice si toco piso o no algun invader
 * @return Si algun invader toco la linea horizontal que se considere como "piso"
*/
static int is_invadersOnFloor(void);

/**
 * @brief Ejecuta o no un disparo de los invaders
*/
static void shouldInvaderShot(void);

/**
 * @brief Crea un shield direction la ultima direccion con la que se movio el conjunto invader
 * @param1 x_shield  la coord en x
 * @param2 y_shield  la coord en y
 * @param3 shield_t* shield: Puntero a shield_t
*/
static void createShield(int x_shield, int y_shield, shield_t *shield);

/**
 * @brief Ubica los shields en el mapa
*/
static void placeShields(void);

/**
 * @brief Dibuja los shields
*/
static void drawShields(void);

/**
 * @brief Se fija si una CAJA choco con algun bloque
 * @param collBoxShot_t* Puntero a la caja de lo que quiere chequear si colisiono o no 
 * @return 1 si choco 0 si no
*/
static int getCollisionOnBlock(collBoxShot_t *boxOfTheShot);

/**
 * @brief Ve si dos cajas estan chocando o no
 * @param1 collBox_t*  la direccion de la caja 1 
 * @param2 collBox_t* la direccion de la caja 2
 * @return 1 si chocan 0 si no
*/
static int isCollision( collBoxShot_t * box1, collBoxShot_t * box2);

/**
 * @brief dibuja los invaders
 * @param invader_t recibe la matriz de los invaders
*/
static void drawAliveInvaders(void);

/**
 * @brief chequea si cambiar la direccion o no
 * @param direction la direccion con la que se venia moviendo 
 * @return la direccion a la que haya que ir
*/
static direction_t decideWhetherChangeDirectionOrNot(direction_t direction);

/**
 * @brief Mueve a la nodriza, si la hay
*/
static void moveUFO(void);

/**
 * @brief dice si hubo colision o no de alguna caja con la nodriza
 * @param collBoxShot_t *boxOfTheShot: Direccion de la caja 
 * @return 1 si es colision 0 si no
*/
static int getColisionOnUFO(collBoxShot_t *boxOfTheShot);

/**
 * @brief hace aparecer o no a UFO
*/
static void shouldUFOappear(void);

/**
 * @brief Actualiza la posicion y dibuja el cannon
*/
static void drawCannon(void);

/**
 * @brief Muestra en pantalla los puntos de la partida.
 **/
void update_points(int score);

/**
 * @brief Muestra en pantalla las vidas restantes de la partida.
 **/
void update_lives(int lives);

/**
 * @brief Muestra en pantalla el nivel actual.
 **/
void update_level (int level);

/**
 * @brief Resetea tasas de velocidades y probabilidades de disparo
 **/
static void restartTasas(void);

/**
 * @brief Muestra en pantalla los puntos, las vidasd y el nivel de la partida.
 * @param1 score Puntaje a imptimir
 * @param2 lives Vidas a imprimir
 * @param3 level Nivel actual a imprimir
 **/
static void inGameStats(unsigned long int score, int lives, int level );
static void updateCannonPos(void);

void move_cannon(direction_t dir)
{
    cannonDir = dir;
}

static void updateCannonPos(void)
{
    switch(cannonDir)
    {
      case LEFT:
        if((cannonXpos - TASA_DE_CAMBIO_CANON) > 0)
        {
          cannonXpos -= TASA_DE_CAMBIO_CANON;
        }
        break;

      case RIGHT:
        if((cannonXpos +  AL_GET_CANNON_WIDTH(canonPointer) + TASA_DE_CAMBIO_CANON) < D_WIDTH)
        {
          cannonXpos += TASA_DE_CAMBIO_CANON;
        }
        break;

      case STOP:
      default:
        break;
  }
}

static void drawCannon(void)
{
    updateCannonPos(); 

}

static void canonDesign(void)
{
    
}


static void cleanDisplay(void)
{
    dcoord_t coord = {0 ,0};
    for(int i = 0; i < D_HEIGHT; i++)
    {
        for(int j = 0; j < D_WIDTH; j++ )
        {
            coord.x = j;
            coord.y = i;
            disp_write( coord, D_ON );
        }
    }
}
