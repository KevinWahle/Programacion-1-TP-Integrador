#include <stdio.h>
#include <stdint.h>

#include "raspi_front_hder.h"
#include "disdrv.h"

#define D_WIDTH 16
#define D_HEIGHT 16

#define CANON_BLOCKS 4
#define UFO_BLOCKS 2
#define INVADER_BLOCK 1  // Es al pedo porque para evaluar la colision solo hay que ver si tienen la misma posicion, pero para no confundir 
                         // Es al pedo que la estructura de invader tenga un bloque
#define SHIELDS_BLOCKS 2

#define FIL_INVADERS 5                   // Cantidad de filas de invaders
#define COL_INVADERS 9                   // Cantidad de columnas de invaders

#define CANON_Y_POS 14

#define CANON_WIDTH 3
#define CANON_HEIGHT 2


#define UFO_WIDTH 2
#define UFO_HEIGHT 1

#define UFO_Y_POS 3

#define TOTAL_SHIELDS 4

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
    float x;
    float y;
    int height;
    int width;
    int state;           // Ya vimos que puede tener varios estados
}block_t;

//Objeto shield
typedef struct
{
    block_t blocks[SHIELDS_BLOCKS];
}shield_t;

typedef struct 
{
    float y;
    float x;                                 // Cuidado la posicion es flotante. Para la la colision debe ser int, pero no pasa nada porque se castea
    block_t blocks[CANON_BLOCKS];            // cuando dibuja tambien castea asi que no pasa nada
    direction_t direction;
}canon_t;

// Objeto invader
typedef struct 
{
    float x;
    float y;
    block_t blocks[INVADER_BLOCK];
    int invaderState;    // Si esta vivo o muerto 
    int invaderType;    // Tipo de invader (SQUID, CRAB, OCTO)
}invader_t;

typedef struct 
{
    float x;
    float y;
    block_t blocks[UFO_BLOCKS];
    int invaderState;
    int invaderType;
    direction_t direction;      //  El UFO puede aparecer desde la izquierda o desde la derecha
} UFO_t;

// En la raspberry, en el caso de las colisones, modelizar a cada objeto con una caja de colision puede no ser la forma mas optima ->
// -> pues al tener menos resolucion se nota mucho en la experiencia al usario. ->
// -> lo mas natural que se puede pensar, es que cada objeto (invaders, shields, canon, nodriza) se puede pensar como una estructura formada por ->
// -> la posicion r = (x, y) y un arreglo de bloques, de dimension definida por el programador. Cada bloque a su vez, es una estructura que ->
// -> tiene la posicion, ancho y alto (siempre 0 va a ser en raspi) y state (para colision). ->
// -> Que el usuario dibuje en una matriz la forma de los invaders, canon, shield? ->
// -> Sobre shields, puede ser...
// -> Pero naves, no se, porque cuantas formas posibles podes hacer... O sea no se si vale la pena. Estaria bueno que cuando haces:
// -> canon_t myCanon; ahi a cada bloque le harcodeas su posicion relatva al (x,y) del canon. Asi hize los bloques de cada shields.
// -> Si el usuario hace el canon dibujando en una matriz => La estructura bloque cambiarla, que tenga un campo que diga si ese bloque es el bloque
// -> por donde va a salir el disparo, funcion que calcule el ancho de lo que el usuario modelo, y no se si el alto, no se. Funcion que setee el 
// -> X0 en bloque (puede existir o no), que este mas a la izq y arriba: ej arr[][2] = { {0,1,0} ,
//                                                                                       {1,1,1} };
// -> En este caso el X0 va en el primer 0 de todos porque es el vertice de la caja, aunque no confundirse porque no se trata al canon como caja
// -> se lo trata como un conjunto de bloques. Con una funcion recorres la matriz y te fijas la relacion de la posicion entre el X0 y y los demas
// -> 1s, y te sirve para despues, a la hora de mover el conjunto , ver colisiones, etc.  
// -> Cuando la funcion que fabrica el canon a partir del dibujo por Ej, para que detecte cual es el bloque que va a disparar, si lo hay, que sea
// -> poniendo un 2 en la matriz en vez de uno
// -> Que opinas?                                                                        


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE (SOLO PARA SHARED_RES)
 ******************************************************************************/

/************ALLEGRO VARIABLES DEFINITION***************/

// Invaders matrix
invader_t invaders[FIL_INVADERS][COL_INVADERS];

const int invadersDistribution [FIL_INVADERS] = {
                                                  SQUID,
                                                  CRAB,
                                                  CRAB,
                                                  OCTO,
                                                  OCTO,
                                                  };



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

//######################################################
//############## FUNCIONES ONLY RASPBERRY ##############
//######################################################

static void updateCanonBlocksPos(void);
static void cleanDisplay(void);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// Invaders matrix
static invader_t invaders[FIL_INVADERS][COL_INVADERS];

static const int invadersDistribution [FIL_INVADERS] = {
                                                  SQUID,
                                                  CRAB,
                                                  CRAB,
                                                  OCTO,
                                                  OCTO,
                                                  };


// Lista de los disparos de los invaders.
static shot_t invaderShotList[MAX_INVADERS_SHOT];

// Contador de la cantidad de balas disparadas por los invaders
static int actualInvadersShots; 
// Contador de la cantidad de balas disparadas por el canon
static int actualCanonShots;

// El cañón

static canon_t canon;    // Creo el canon
canon.x = 0;             // Lo pongo al costado de todo a la izquierda
canon.y = CANON_Y_POS;   // Lo seteo en el piso
canon.direction = STOP;  // Al principio arranca parado

for (int i = 0; i < CANON_BLOCKS; i++)   // La altura y ancho de los bloques son 0, porque cada bloque es realidad son puntos 
{
    canon.block[i].width = 0;            // Un punto es un caso particular de un bloque
    canon.block[i].height = 0;
    canon.block[i].state = 1;    // No creo que importe mucho el state
}


updateCanonBlocksPos();       //Siempre que se actualize la posicion, hay que actualizar la posicion de todos los bloques que forman el objeto

static shot_t canonShotList[MAX_CANON_SHOT];
static direction_t proxDir = LEFT;
// El UFO

UFO_t UFO_invader = {   .y = UFO_Y_POS,
                        .invaderType = UFO,   // .x y .blocks may not be initialized
                        .invaderState = 0     //Arranca muerta
                    };



//TASAS DE CAMBIO VARIABLES:

static float dxInvader;
static float shotFromInvaderFrec;

static shield_t shielders[TOTAL_SHIELDS];

// Velocidades y probabilidades variables
static float tasaDeCambioInvaders = MIN_SPEED_INVADER;
static int probDisparoInvaders = MIN_POSIBILIY_OF_SHOT_FROM_INVADERS;
static int probUfo = MIN_POSIBILIY_OF_APPEAR_UFO;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


static void updateCanonBlocksPos(void)
{
    canon.block[0].x = canon.x + 1;
    canon.block[0].y = canon.y;

    canon.block[1].x = canon.x;
    canon.block[1].y = canon.y + 1;

    canon.block[2].x = canon.x + 1;
    canon.block[2].y = canon.y + 1;

    canon.block[3].x = canon.x + 2;
    canon.block[3].y = canon.y + 1;
}

void move_cannon(direction_t dir)
{
    canon.direction = dir;
}

static void updateCannonPos(void)
{
    switch(canon.direction)
    {
      case LEFT:
        if((canon.x - TASA_DE_CAMBIO_CANON) > 0)
        {
          canon.x -= TASA_DE_CAMBIO_CANON;
        }
        break;

      case RIGHT:
        if((canon.x  +  CANON_WIDTH + TASA_DE_CAMBIO_CANON) < D_WIDTH)
        {
          canon.x += TASA_DE_CAMBIO_CANON;
        }
        break;

      case STOP:
      default:
        break;
  }
  updateCanonBlocksPos();
}

static void drawCannon(void)
{
    updateCannonPos();
    for (int i = 0; i < CANON_BLOCKS; i++)
    {
      dcoord_t coord = { .x = (int)canon.block[i].x, .y = (int)canon.block[i].y};   // Casteo a int, en realidad a uint8_t deberia ser
      disp_write(coord , D_ON );
    }
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
            disp_write( coord, D_OFF );
        }
    }
}

void reviveCanon(void)
{
    if(TOTAL_SHIELDS > 0)
    {
        canon.x = shielders[0].block_1.x;
    }
    else
    {
        canon.x = D_WIDTH/2;
    }
}


/**
 * @brief Ejecuta un disparo del canon
 * @return TODO?: CODIGO DE ERROR?
*/
void shoot_cannon(void)
{   
                                           
    float x_shot = canon.blocks[0].x;      
    float y_shot = canon.blocks[0].y - 1; 
    
    shot_t shot = { .x = x_shot,
                    .y = y_shot,
                    .shotState = 1
                  };
    int k = 0;
    while (canonShotList[k].shotState != 0 && k < MAX_CANON_SHOT) {
        k++;        // Busco un lugar en la lista (donde el disparo no este activo)
    }
    if (k < MAX_CANON_SHOT) {
        canonShotList[k] = shot;
        actualCanonShots++;
        //En allegro la dibuja, PERO NO VOY A PRENDER LEDS, ESTA MAL QUE EL BACK DRAWEE 

               // TODO: Cambiar por codigo OK
    }
    // ARRAY OVERFLOW
                  // TODO: Cambiar por codigo de error
}

void clean_shoots(void)
{
  for(int i = 0; i < MAX_CANON_SHOT; i++)
  {
    canonShotList[i].shotState = 0;
  }
  actualCanonShots = 0;
  
  for(int i = 0; i < MAX_INVADERS_SHOT; i++)
  {
    invaderShotList[i].shotState = 0;
  }
  actualInvadersShots = 0;
}

void update_speed_front(int newSpeed, int maxSpeed) 
{
    //Si MIN speed es 0
    tasaDeCambioInvaders = (MAX_SPEED_INVADER - MIN_SPEED_INVADER)*newSpeed/maxSpeed + MIN_SPEED_INVADER;
    probDisparoInvaders =  ((MIN_POSIBILIY_OF_SHOT_FROM_INVADERS - MAX_POSIBILIY_OF_SHOT_FROM_INVADERS) - (MIN_POSIBILIY_OF_SHOT_FROM_INVADERS - MAX_POSIBILIY_OF_SHOT_FROM_INVADERS)*newSpeed/maxSpeed ) + MAX_POSIBILIY_OF_SHOT_FROM_INVADERS;
    probUfo = ((MIN_POSIBILIY_OF_APPEAR_UFO - MAX_POSIBILIY_OF_APPEAR_UFO) - (MIN_POSIBILIY_OF_APPEAR_UFO - MAX_POSIBILIY_OF_APPEAR_UFO)*newSpeed/maxSpeed ) + MAX_POSIBILIY_OF_APPEAR_UFO;
}

int checkWin(void)
{
    int win = 1;
    int i = 0;
    while( i < FIL_INVADERS && win)
    {
        int j = 0;
        while(j < COL_INVADERS && win)
        {
            win = invaders[i][j].invaderState ? 0 : 1;   //Si hay un vivo no puede haber ganado => win = 0
            j++;
        }
        i++;
    }
    return win;
}
/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/**
 * @brief Ejecuta un disparo del invader
 */


static void invaderShot(int i, int j)
{       
    float x_shot = invaders[i][j].blocks[0].x; 
    float y_shot = invaders[i][j].blocks[0].y + 1;
    
    shot_t shot = { .x = x_shot,
                    .y = y_shot,
                    .shotState = 1
                    };

    int k = 0;
    while (invaderShotList[k].shotState != 0 && k < MAX_INVADERS_SHOT) {
        k++;        // Busco un lugar en la lista (donde el disparo no este activo)
    }
    if (k < MAX_INVADERS_SHOT) {
        invaderShotList[k] = shot;
        actualInvadersShots++;
                                    //ALLEGRO DIBUJA AHORA NO DIBUJA MAS ACA !!!!!!!!!!!!!!
               // TODO: Cambiar por codigo OK
    }
    // ARRAY OVERFLOW
               // TODO: Cambiar por codigo de error
}

/**
 * @brief Ve si hubo una colision del disparo ejecutado por algun invader
*/
static void getInvaderShotCollison(void)
{
    if(actualInvadersShots > 0)
    {
        int i = 0;
        int foundShots = 0;
        int colisionDetected = 0;
        while (i < MAX_INVADERS_SHOT && foundShots < actualInvadersShots) 
        {
            if (invaderShotList[i].shotState == 1) {
                foundShots++;
                //Aca en allegro dibujaba la bala:
                dcoord_t coord = { .x = invaderShotList[i].x, .y = invaderShotList[i].y  }
                disp_write( coord, D_ON);       // REVISAR si hay que dibujarla aca

                invaderShotList[i].y += TASA_DE_CAMBIO_BALA;


                collBoxShot_t collBoxShotFromInvader = {  .x = invaderShotList[i].x ,
                                                          .y = invaderShotList[i].y ,
                                                          .height = 0 , //Dimensiones 0 (es un punto)
                                                          .width = 0
                                                       };
                for(int k = 0; k < CANON_BLOCKS; k++)   // seria k < CANON_BLOCKS - 1 porque el bloque de abajo en el medio no choca nunca
                {
                    collBoxShot_t canonBlockBox = {   .x = canon.blocks[k].x,
                                                      .y = canon.blocks[k].y,
                                                      .height = 0,
                                                      .width = 0
                                                  };
                    if( isCollision( &collBoxShotFromInvader, &canonBlockBox ) )     
                    {
                        invaderShotList[i].shotState = 0;
                        colisionDetected++;
                        add_event(CANNON_COLL_EV);        // Agrego evento de colision con cannon
                        reviveCanon();
                    }
                }
                if( getCollisionOnBlock( &collBoxShotFromInvader )  && !colisionDetected )   // Choque con algun shield ?
                {
                    invaderShotList[i].shotState = 0;
                    colisionDetected++;
                }
                else if( invaderShotList[i].y > D_HEIGHT )
                {
                    invaderShotList[i].shotState = 0;
                    colisionDetected++;
                }
            }
            i++;
        }
        actualInvadersShots -= colisionDetected;
    }
}

/**
 * @brief Ve si hubo una colision del disparo ejecutado por el canon
*/
static void getCanonShotCollision(void)
{
    if(actualCanonShots > 0)
    {
        int iCont = 0;
        int foundShots = 0;
        int colisionDetected = 0;
        while (iCont < MAX_CANON_SHOT && foundShots < actualCanonShots) 
        {
            if (canonShotList[iCont].shotState == 1) 
            {
                foundShots++;

                //Aca en allegro dibuja la bala:

                dcoord_t coord = { .x = canonShotList[iCont].x, .y = canonShotList[iCont].y  }
                disp_write( coord, D_ON);

                canonShotList[iCont].y -= TASA_DE_CAMBIO_BALA;

                collBoxShot_t collBoxShotFromCanon =   {  .x = canonShotList[iCont].x ,
                                                          .y = canonShotList[iCont].y ,
                                                          .height = 0 , // Dimensiones 0 (es un punto)
                                                          .width = 0
                                                       };
                if( canonShotList[iCont].y <= 0 )
                {
                    canonShotList[iCont].shotState = 0;
                    colisionDetected++;
                }
                else if( getCollisionOnBlock( &collBoxShotFromCanon ) )
                {
                    canonShotList[iCont].shotState = 0;
                    colisionDetected++;
                }
                else if( getColisionOnUFO( &collBoxShotFromCanon )  )
                {
                    canonShotList[iCont].shotState = 0;
                    colisionDetected++;
                    add_event(UFO_COLL_EV);
                }
                else      // getColisonOnInvaders();
                {
                    for(int i = 0; i < FIL_INVADERS; i++)
                    {
                        for (int j = 0; j < COL_INVADERS; j++)
                        {
                            if( invaders[i][j].invaderState  )
                            {
                                collBoxShot_t invaderBox = {  .x = invaders[i][j].blocks[0].x ,
                                                              .y = invaders[i][j].blocks[0].y ,           // TODO: Hacer una estructura o constante
                                                              .height = 0,                                // TODO: Cambiar por tamaño invader
                                                              .width = 1
                                                           };
                                                           
                                if( isCollision( &collBoxShotFromCanon, &invaderBox ) )
                                {
                                    canonShotList[iCont].shotState = 0;
                                    invaders[i][j].invaderState = 0;
                                    colisionDetected++;
                                    switch (invaders[i][j].invaderType)
                                    {
                                    case SQUID:
                                        add_event(SQUID_COLL_EV);
                                        break;
                                    case CRAB:
                                        add_event(CRAB_COLL_EV);
                                        break;
                                    case OCTO:
                                        add_event(OCTO_COLL_EV);
                                        break;
                                    default:
                                        break;
                                    }
                                }
                            }
                        }
                    }                    
                }
            }
            iCont++;
        }
        actualCanonShots -= colisionDetected;
    }

    actualCanonShots = 0;
    for (int i = 0; i < MAX_CANON_SHOT; i++)
    {
        if( canonShotList[i].shotState  )
            actualCanonShots++;
    }
}

/**
 * @brief dibuja los invaders
 */
static void drawAliveInvaders(void)
{
    for (int i = 0; i < FIL_INVADERS; i++)
    {
        for (int j = 0; j < COL_INVADERS; j++)
        {
            if( (invaders[i][j].invaderState) )
              {
                   dcoord_t coord = { .x = (int)invaders[i][j].blocks[0].x, .y = (int)invaders[i][j].blocks[0].y };     // Revisar por el tamaño de invaders
                   disp_write(coord, D_ON); 
                   // TODO: Ver de hacer un for para dibujar rectangulos.   
              }  
        }
    }

    if (UFO_invader.invaderState) 
    {
        if( UFO_invader.x >= ( (-1)*AL_GET_UFO_WIDTH(UFO_invader.invadersPointer) )  && UFO_invader.x <= (D_WIDTH + AL_GET_UFO_WIDTH(UFO_invader.invadersPointer)) )
        {
            //dcoord_t coord = { .x = (int)invaders[i][j].blocks[0].x, .y = (int)invaders[i][j].blocks[0].y };
            //disp_write(coord, D_ON);     NO PENSE EL UFOOO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
        else
        {
            UFO_invader.invaderState = 0;
        }
    }
}

/**
 * @brief Ve si dos cajas estan chocando o no
 */
static int isCollision(collBoxShot_t* box1, collBoxShot_t* box2)    // Ahora seria <= o >=
{                                                                   // En allegro es lo mismo que este el = o no mas o menos pero aca es importante
    if(box1->x <= box2->x + box2->width &&                          // Algoritmo para ver si dos cajas estan chocando
       box2->x <= box1->x + box1->width &&
       box1->y <= box2->y + box2->height &&
       box2->y <= box1->y + box1->height)
       return 1;

    return 0;
}

/**
 * @brief Mueve el conjunto para abajo
*/
static void moveInvadersDown(void)
{
    for (int i = 0; i < FIL_INVADERS; i++)
    {
        for(int j = 0; j < COL_INVADERS; j++)
        {
            invaders[i][j].y += INVADERS_FALL;          
            // TODO: Hacer un for por cada bloque de invader   updateblockinvader(); 
            //invaders[i][j].block[0].y += INVADERS_FALL;    //Aca es el caso que peor queda lo de los blocks pero bue lo deje asi quedan todos los objetos iguales 
        
        }
    }
}

/**
 * @brief Mueve el conjunto invader
 */
static direction_t moveInvaders(direction_t direction)
{
    direction_t nextDirection = decideWhetherChangeDirectionOrNot(direction); // Me fijo si tengo que mantener la direccion o no, invocando a la funcion
    if(nextDirection != direction)                                    // Si la direccion es distinta a la que se venia llevando => muevo el conjunto 
    {                                                                 // de invaders para abajo
        moveInvadersDown();
    }
    for (int i = 0; i < FIL_INVADERS; i++)
    {
        for(int j = 0; j < COL_INVADERS; j++ )
        {
            if(nextDirection == LEFT)
            {
                invaders[i][j].x -= tasaDeCambioInvaders;
                invaders[i][j].blocks[0].x -= tasaDeCambioInvaders;  // RANCIO TAMBIEN SEGURO LO SAQUE NO SE
            }
            else if(nextDirection == RIGHT)
            {
                invaders[i][j].x += tasaDeCambioInvaders;
                invaders[i][j].blocks[0].x += tasaDeCambioInvaders;
            }
        }
    }
    //INCLUIR: updateblockinvader(); 
    return nextDirection;
}

static direction_t decideWhetherChangeDirectionOrNot(direction_t direction)
{
    direction_t nextDirection = ERROR_DIREC;
    if(direction == LEFT)
    {
        int j = 0;
        while(j < COL_INVADERS && nextDirection == ERROR_DIREC )
        {
            int i = 0;
            while(   i < FIL_INVADERS  && !invaders[i][j].invaderState  ) // Busca en la col, mientras esten muertos, sigo
            {
                i++;
            }
            if( i == FIL_INVADERS  ) // Entonces estaban todos muertos
            {
                j++;                // Voy a la siguiente columna
            }
            else   //Si no, hay al menos uno vivo
            {
                if( invaders[i][j].x < INVADERS_WALL )     //Al menos seguro que el ultimo de todos esta vivo, el ultimo que quedo con el i j, porque si salto por exceso el if te lo asegura, si no, salto por el while
                {
                    nextDirection = RIGHT;
                }
                else
                {
                    nextDirection = LEFT;   //Encontraste un vivo tal que todavia no paso la linea => me mantengo en el sentido
                }
            }
        }    
    }
    else if(direction == RIGHT)
    {
        int j = COL_INVADERS - 1;
        while(j >= 0 && nextDirection == ERROR_DIREC )
        {
            int i = 0;
            while(  i < FIL_INVADERS   &&  !invaders[i][j].invaderState   ) // Busca en la col, mientras esten muertos
            {
                i++;
            }
            if( i == FIL_INVADERS ) // Entonces estaban todos muertos
            {
                j--;
            }
            else   //Si no, hay al menos uno vivo
            {
                if( invaders[i][j].x + INVADER_WIDTH > D_WIDTH - INVADERS_WALL )     //Al menos seguro que el ultimo de todos esta vivo, el ultimo que quedo con el i j, porque si salto por exceso el if te lo asegura, si no, salto por el while
                //!!!!!!!!!! REVISAR: Agregar invader width 
                //!!!!!!!!!! INCAgregar invader width * caca
                {
                    nextDirection = LEFT;
                }
                else
                {
                    nextDirection = RIGHT;   //Encontraste un vivo tal que todavia no paso la linea => me mantengo en el sentido
                }
            }
        }
    }
    return nextDirection;
}


static int is_invadersOnFloor(void)
{
    int i = FIL_INVADERS - 1;
    int state = 0;
    int onFloor = 0;
    while( i >= 0 && !state )                                         //Arranco en la fila de mas abajo, que seria la primera en tocar el piso
    {
        int j = 0;
        while(   j < COL_INVADERS  && !invaders[i][j].invaderState  ) // Busco el primer invader vivo de la columna, 
        {
            j++;
        }
        if( j == COL_INVADERS  ) // Entonces estaban todos muertos
        {
            i--;
        }
        else   //Si no, hay al menos uno vivo
        {
            if( invaders[i][j].y > INVADERS_FLOOR )     //Al menos seguro que el ultimo de todos esta vivo, el ultimo que quedo con el i j, porque si salto por exceso el if te lo asegura, si no, salto por el while
            {
                state = 1;
                onFloor = 1;
            }
            else
            {
                state = 1;   //Encontraste un vivo tal que todavia no paso la linea => me mantengo en el sentido
                onFloor = 0;
            }
        }
    }    
    return onFloor;
}


static void shouldInvaderShot(void)
{
    for (int j = 0; j < COL_INVADERS; j++)
    {
        int i = FIL_INVADERS - 1;
        while( i >= 0  &&   !invaders[i][j].invaderState )  //Busco los invaders (vivos) tales que abajo de ellos no tengan ningun invader vivo
        {
            i--;
        }
        if( i >= 0)          // entonces se encontro algun invader vivo
        {
            if(  !(rand() % probDisparoInvaders) )
                invaderShot(i, j);
        }
    }       
}


static void createShield(int x_shield, int y_shield, shield_t *shield)
{
    shield->block_1.x = x_shield;
    shield->block_1.y = y_shield;     // Algunos pensaran que esta hardcodeado, pues si, cada bloque se debe decidir, no hay patron generico
    shield->block_1.state = STATE_0;
    shield->block_1.color = blockColors[STATE_0];
    shield->block_1.width = B_WIDTH;
    shield->block_1.height = B_HEIGHT;

    shield->block_2.x = x_shield + B_WIDTH;
    shield->block_2.y = y_shield;
    shield->block_2.state = STATE_0;
    shield->block_2.color = blockColors[STATE_0];
    shield->block_2.width = B_WIDTH;
    shield->block_2.height = B_HEIGHT;

    shield->block_3.x = x_shield + 2*B_WIDTH;
    shield->block_3.y = y_shield;
    shield->block_3.state = STATE_0;
    shield->block_3.color = blockColors[STATE_0];
    shield->block_3.width = B_WIDTH;
    shield->block_3.height = B_HEIGHT;

    shield->block_4.x = x_shield;
    shield->block_4.y = y_shield + B_HEIGHT;
    shield->block_4.state = STATE_0;
    shield->block_4.color = blockColors[STATE_0];
    shield->block_4.width = B_WIDTH;
    shield->block_4.height = B_HEIGHT;

    shield->block_5.x = x_shield + 2*B_WIDTH;
    shield->block_5.y = y_shield + B_HEIGHT;
    shield->block_5.state = STATE_0;
    shield->block_5.color = blockColors[STATE_0];
    shield->block_5.width = B_WIDTH;
    shield->block_5.height = B_HEIGHT;


    al_draw_filled_rectangle(shield->block_1.x, shield->block_1.y, shield->block_1.x + B_WIDTH, shield->block_1.y + B_HEIGHT, al_color_name(COLOR_STATE_0)  );
    al_draw_filled_rectangle(shield->block_2.x, shield->block_2.y, shield->block_2.x + B_WIDTH, shield->block_2.y + B_HEIGHT, al_color_name(COLOR_STATE_0)  );
    al_draw_filled_rectangle(shield->block_3.x, shield->block_3.y, shield->block_3.x + B_WIDTH, shield->block_3.y + B_HEIGHT, al_color_name(COLOR_STATE_0)  );
    al_draw_filled_rectangle(shield->block_4.x, shield->block_4.y, shield->block_4.x + B_WIDTH, shield->block_4.y + B_HEIGHT, al_color_name(COLOR_STATE_0)  );
    al_draw_filled_rectangle(shield->block_5.x, shield->block_5.y, shield->block_5.x + B_WIDTH, shield->block_5.y + B_HEIGHT, al_color_name(COLOR_STATE_0)  );
}


static void placeShields(void)
{
    for (int i = 0; i < TOTAL_SHIELDS; i++)
    {
        int x_shield =  i * ( SHIELD_WIDTH + DIST ) + OFFSET_FROM_WALL_ABSOLUTE ;  // Calcula la posicion en x de los shields

        int y_shield = Y1;

        createShield(x_shield, y_shield, &shielders[i] );
    }
}


static void drawShields(void)
{
    for (int i = 0; i < TOTAL_SHIELDS; i++)
    {
        if( shielders[i].block_1.state != DEATH_STATE)   // Si el bloque no esta muerto, lo dibujo. Recordar que el color se lo asocia con el estado de la vida
        {
            al_draw_filled_rectangle(shielders[i].block_1.x, shielders[i].block_1.y, shielders[i].block_1.x + B_WIDTH, shielders[i].block_1.y + B_HEIGHT, al_color_name( shielders[i].block_1.color  )  );
        }
        if( shielders[i].block_2.state != DEATH_STATE)
        {
            al_draw_filled_rectangle(shielders[i].block_2.x, shielders[i].block_2.y, shielders[i].block_2.x + B_WIDTH, shielders[i].block_2.y + B_HEIGHT, al_color_name( shielders[i].block_2.color  )  );
        }
        if( shielders[i].block_3.state != DEATH_STATE)
        {
            al_draw_filled_rectangle(shielders[i].block_3.x, shielders[i].block_3.y, shielders[i].block_3.x + B_WIDTH, shielders[i].block_3.y + B_HEIGHT, al_color_name( shielders[i].block_3.color  )  );
        }
        if( shielders[i].block_4.state != DEATH_STATE)
        {
            al_draw_filled_rectangle(shielders[i].block_4.x, shielders[i].block_4.y, shielders[i].block_4.x + B_WIDTH, shielders[i].block_4.y + B_HEIGHT, al_color_name( shielders[i].block_4.color  )  );
        }
        if( shielders[i].block_5.state != DEATH_STATE)
        {
            al_draw_filled_rectangle(shielders[i].block_5.x, shielders[i].block_5.y, shielders[i].block_5.x + B_WIDTH, shielders[i].block_5.y + B_HEIGHT, al_color_name( shielders[i].block_5.color  )  );
        }
    }
}


static int getCollisionOnBlock(collBoxShot_t *boxOfTheShot)     // NO esta tocada, REVISAR
{
    int colision = 0;
    int i = 0;
    while(i < TOTAL_SHIELDS && !colision)                 //Chequea en cada shield si hubo colision o no
    {
        
        collBoxShot_t boxOfBlock1 = {  .x = shielders[i].block_1.x,
                                       .y = shielders[i].block_1.y,
                                       .height = shielders[i].block_1.height,
                                       .width = shielders[i].block_1.width,           
                                   };            
        collBoxShot_t boxOfBlock2 = {  .x = shielders[i].block_2.x,
                                       .y = shielders[i].block_2.y,
                                       .height = shielders[i].block_2.height,
                                       .width = shielders[i].block_2.width,           
                                   };
        collBoxShot_t boxOfBlock3 = {  .x = shielders[i].block_3.x,
                                       .y = shielders[i].block_3.y,
                                       .height = shielders[i].block_3.height,
                                       .width = shielders[i].block_3.width,           
                                   };
        collBoxShot_t boxOfBlock4 = {  .x = shielders[i].block_4.x,
                                       .y = shielders[i].block_4.y,
                                       .height = shielders[i].block_4.height,
                                       .width = shielders[i].block_4.width,           
                                   };
        collBoxShot_t boxOfBlock5 = {  .x = shielders[i].block_5.x,
                                       .y = shielders[i].block_5.y,
                                       .height = shielders[i].block_5.height,
                                       .width = shielders[i].block_5.width,           
                                   };
        
        if(  shielders[i].block_1.state != DEATH_STATE && isCollision(boxOfTheShot, &boxOfBlock1) )
        {
            colision = 1;
            shielders[i].block_1.state++;
            if( shielders[i].block_1.state != DEATH_STATE )
                shielders[i].block_1.color = blockColors[ shielders[i].block_1.state ];
        }
        else if(  shielders[i].block_2.state != DEATH_STATE && isCollision(boxOfTheShot, &boxOfBlock2) )
        {
            colision = 1;
            shielders[i].block_2.state++;
            if( shielders[i].block_2.state != DEATH_STATE )
                shielders[i].block_2.color = blockColors[ shielders[i].block_2.state ];
        }
        else if(  shielders[i].block_3.state != DEATH_STATE && isCollision(boxOfTheShot, &boxOfBlock3) )
        {
            colision = 1;
            shielders[i].block_3.state++;
            if( shielders[i].block_3.state != DEATH_STATE )
                shielders[i].block_3.color = blockColors[ shielders[i].block_3.state ];
        }
        else if(  shielders[i].block_4.state != DEATH_STATE && isCollision(boxOfTheShot, &boxOfBlock4) )
        {
            colision = 1;
            shielders[i].block_4.state++;
            if( shielders[i].block_4.state != DEATH_STATE )
                shielders[i].block_4.color = blockColors[ shielders[i].block_4.state ];
        }
        else if(  shielders[i].block_5.state != DEATH_STATE && isCollision(boxOfTheShot, &boxOfBlock5) )
        {
            colision = 1;
            shielders[i].block_5.state++;
            if( shielders[i].block_5.state != DEATH_STATE )
                shielders[i].block_5.color = blockColors[ shielders[i].block_5.state ];
        }
        i++;
    }
    return colision;
}