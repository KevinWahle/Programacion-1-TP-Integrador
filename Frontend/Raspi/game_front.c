// https://www.tutorialspoint.com/c_standard_library/time_h.htm
/***************************************************************************//**
  @file     +game_front+
  @brief    +Todos los reCcursos para el funcionamiento del juego+
  @author   +Grupo3+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "headall.h"
#include "../../Backend/event_queue/event_queue.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define D_WIDTH 16
#define D_HEIGHT 16

#define CANON_BLOCKS 4
#define UFO_BLOCKS 3
#define INVADER_BLOCK 2  // Es al pedo porque para evaluar la colision solo hay que ver si tienen la misma posicion, pero para no confundir 
                         // Es al pedo que la estructura de invader tenga un bloque
#define SHIELDS_BLOCKS 4

#define FIL_INVADERS 4                   // Cantidad de filas de invaders
#define COL_INVADERS 3                   // Cantidad de columnas de invaders

#define CANON_WIDTH 2
#define CANON_HEIGHT 1

#define CANON_Y_POS  D_HEIGHT-CANON_HEIGHT-1 // ESE 1 ES PORQUE 16-1-1 ES 14 QUE ES DONDE DEBERIA ESTAR YA QUE 0 <= Y <= 15

#define UFO_WIDTH 2
#define UFO_HEIGHT 0
#define INVADER_WIDTH 1

#define UFO_Y_POS 0

#define TOTAL_SHIELDS 4

//*********************************REVISAR CONSTANTES************************  

#define PPS_NODRIZA         7         // Pixeles por segundo (velocidad) de la nave nodriza
#define PPS_CANON           20         // Pixeles por segundo (velocidad) del canon   
#define PPS_BALA            28         // Pixeles por segundo (velocidad) de la bala
#define MAX_PPS_INVADERS    14         // Máximos PPS (velocidad) de invaders
#define MIN_PPS_INVADERS    7        // Mínimos PPS (velocidad) de invaders
#define FPS 60.0

#define TASA_DE_CAMBIO_CANON (PPS_CANON/FPS)           // Pixeles por refresco (velocidad) del canon   
#define TASA_DE_CAMBIO_BALA (PPS_BALA/FPS)            // Pixeles por refresco (velocidad) de la bala
#define TASA_DE_CAMBIO_NODRIZA (PPS_NODRIZA/FPS)         // Pixeles por refresco (velocidad) de la nave nodriza

//#define TASA_DE_CAMBIO_INCVADERS 0.5      // NO SIRVE, es fija, SACAR

#define SHOT_HEIGHT 15                   // Tamanio del disparo, sirve para hacer la caja de colision
#define SHOT_WIDTH 4                     // idem

// INVADERS POSITION
#define INVADERS_WIDTH  2           // Ancho de los invaders en pixeles
#define INVADERS_HEIGHT  1          // Alto de los invaders en pixeles
#define INVADERS_START_HEIGHT 1      // Pixel inician los invaders (desde arriba)

//#define INVADERS_FLOOR  9.5  // Espacio desde el techo hasta "piso" de los invasores
//#define INVADERS_WALL 0.1                  // Espacio entre el borde derecho e izquierdo en el que van a robotar los invaders
//#define INVADERS_FALL 0.34           // Espacio de caida de los invaders al llegar a cada tope 
//#define INVADERS_WIDTH_BETWEEN  1        // Cantiad de pixeles entre invaders (horizontal)
//#define INVADERS_HEIGHT_BETWEEN  1        // Cantiad de pixeles entre invaders (vertical)

#define INVADERS_FLOOR (D_HEIGHT*0.65)   // Espacio desde el techo hasta "piso" de los invasores
#define INVADERS_WALL 0.2                    // Espacio entre el borde derecho e izquierdo en el que van a robotar los invaders
#define INVADERS_FALL (D_HEIGHT*0.02)    // Espacio de caida de los invaders al llegar a cada tope 
#define INVADERS_WIDTH_BETWEEN  1        // Cantiad de pixeles entre invaders (horizontal)
#define INVADERS_HEIGHT_BETWEEN  1        // Cantiad de pixeles entre invaders (vertical)


#define MAX_INVADERS_SHOT 20             // Es la mayor cantidad de disparos de los invaders que puede llegar a haber en el juego

#define MAX_CANON_SHOT 3                 // Es la mayor cantidad de disparos del canon que puede haber en el juego. Es decir la max cant. de balas visibles


//##### Shields ####

#define TOTAL_SHIELDS 4                  // Para todo n, en particular n = 4


//TOPES MAXIMOS Y MINIMOS DE VELOCIDAD DE INVADERS Y PROBABILIDADES
#define MAX_SPEED_INVADER  (MAX_PPS_INVADERS/FPS)
#define MIN_SPEED_INVADER  (MIN_PPS_INVADERS/FPS)

#define MAX_POSIBILIY_OF_SHOT_FROM_INVADERS  5     
#define MIN_POSIBILIY_OF_SHOT_FROM_INVADERS  150


#define MAX_POSIBILIY_OF_APPEAR_UFO  50
#define MIN_POSIBILIY_OF_APPEAR_UFO  70  

#define DEATH_STATE STATE_1

//********************CONSTANTES DE RASPI, EN PARTICULAR LA DE BLOQUES****************************/

#define PIXELS_B2IN_SHIELDS 2       // Cantidad de pixeles entre los escudos
#define PIXELS_MARGIN 1
#define SHIELD_PIXELS_WIDTH 2

#define SHIELDS_Y1 11               // Posicion en y donde van los shields

#define DIST_2 (SHIELD_PIXELS_WIDTH + PIXELS_B2IN_SHIELDS)


//***********************************FIN REVISAR CONSTANTES*****************************************/


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

enum blockStates {STATE_0, STATE_1};   // STATE_0 seria el estado del bloque sin danios. STATE_4 en este caso es el ultimo estado

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
} canon_t;

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


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE (SOLO PARA SHARED_RES)
 ******************************************************************************/

/************ALLEGRO VARIABLES DEFINITION***************/

// Invaders matrix
invader_t invaders[FIL_INVADERS][COL_INVADERS];

const int invadersDistribution [FIL_INVADERS] = {
                                                  OCTO,
                                                  OCTO,
                                                  OCTO,
                                                  OCTO,
                                                  };
        /// VER SI TODOS VALEN LO MISMO O NO


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Ejecuta unC disparo del invader
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

/* *B_WIDTH_PERCENTnvadersDown(void); */

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
static void drawCanon(void);

// /**
//  * @brief Muestra en pantalla los puntos de la partida.
//  **/
// void update_points(int score);

// /**
//  * @brief Muestra en pantalla las vidas restantes de la partida.
//  **/
// void update_lives(int lives);

// /**
//  * @brief Muestra en pantalla el nivel actual.
//  **/
// void update_level (int level);

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

// CONTINUAR:
static void updateCanonPos(canon_t *canonPointer);

//######################################################
//############## FUNCIONES ONLY RASPBERRY ##############
//######################################################

static void updateCanonBlocksPos(canon_t *canonPointer);
static void cleanDisplay(void);

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

static canon_t canon;    // Creo el canon
                          // Lo pongo al costado de todo a la izquierda
                          // Lo seteo en el piso
                          // Al principio arranca parado

static shot_t canonShotList[MAX_CANON_SHOT];
static direction_t proxDir = LEFT;
// El UFO

UFO_t UFO_invader = {   .y = UFO_Y_POS,
                        .invaderType = 7,   // ACA IBA UN "UFO" EN LUGAR DEL 7, QUIEN CARAJO HIZO ESO NO ENTIENDO
                        .invaderState = 0     //Arranca muerta
                    };

//TASAS DE CAMBIO VARIABLES:



static shield_t shielders[TOTAL_SHIELDS];

// Velocidades y probabilidades variables
static float tasaDeCambioInvaders = MIN_SPEED_INVADER;
static int probDisparoInvaders = MIN_POSIBILIY_OF_SHOT_FROM_INVADERS;
static int probUfo = MIN_POSIBILIY_OF_APPEAR_UFO;

static own_timer_t fpsTimer;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void init_game(void) {

    srand(time(0));
    
    disp_clear();

    canon.x = 4;  // MAGIC NUMBER
    canon.y = CANON_Y_POS;

    restartTasas();

    placeInvaders();

    placeShields();
  
    clean_shoots();

    drawCanon();

    disp_update();

    setTimer(&fpsTimer, 1/FPS);     // Aca declaro el timer y el tiempo
    
    startTimer(&fpsTimer);      // Recien aca empieza el timer

}


void redraw(unsigned long int score, int lives, int level)
{ 
    if (checkTimer(&fpsTimer))   // NOMBRE EVENTOOOO
    {
        cleanDisplay();
        shouldUFOappear();
        moveUFO();
        getCanonShotCollision();
        shouldInvaderShot();
        getInvaderShotCollison();
        if( !is_invadersOnFloor()  )
        {
            proxDir = moveInvaders(proxDir);
        }
        else
        {
            add_event(END_GAME_EVENT);
        }
        drawShields();
        drawAliveInvaders();  
        drawCanon();
        disp_update();
    }
    
}


/**
 * @brief Ubica a los invaders en la posición inicial
*/
void placeInvaders(void)
{
    int x_init = D_WIDTH/2-(INVADERS_WIDTH*COL_INVADERS)/2; // Donde empiezo a colocar los invaders (calcular)
    int y_init = INVADERS_START_HEIGHT;

    for (int i = 0; i < FIL_INVADERS; i++)
    {
        for (int j = 0; j < COL_INVADERS; j++)
        {
            int x_inv = x_init + j*(INVADERS_WIDTH+INVADERS_WIDTH_BETWEEN);
            int y_inv = y_init + i*(INVADERS_HEIGHT+INVADERS_HEIGHT_BETWEEN);
            invaders[i][j].x = x_inv;
            invaders[i][j].y = y_inv;
            invaders[i][j].invaderState = 1; //Ademas de colocar las naves, tambien les doy vida en el juego 
        }
    }
    proxDir = RIGHT;
    UFO_invader.invaderState = 0;
}


/**
 * @brief Actualiza la velocidad del juego
 * @param newSpeed El nuevo valor de velocidad para el juego
*/
void update_speed_front(int newSpeed, int maxSpeed) 
{
    //Si MIN speed es 0
    tasaDeCambioInvaders = (MAX_SPEED_INVADER - MIN_SPEED_INVADER)*newSpeed/maxSpeed + MIN_SPEED_INVADER;
    probDisparoInvaders =  ((MIN_POSIBILIY_OF_SHOT_FROM_INVADERS - MAX_POSIBILIY_OF_SHOT_FROM_INVADERS) - (MIN_POSIBILIY_OF_SHOT_FROM_INVADERS - MAX_POSIBILIY_OF_SHOT_FROM_INVADERS)*newSpeed/maxSpeed ) + MAX_POSIBILIY_OF_SHOT_FROM_INVADERS;
    probUfo = ((MIN_POSIBILIY_OF_APPEAR_UFO - MAX_POSIBILIY_OF_APPEAR_UFO) - (MIN_POSIBILIY_OF_APPEAR_UFO - MAX_POSIBILIY_OF_APPEAR_UFO)*newSpeed/maxSpeed ) + MAX_POSIBILIY_OF_APPEAR_UFO;
}


/**
 * @brief Coloca el cannon en la posición al revivir, debajo de un shield
*/
void reviveCanon(void)
{
    if(TOTAL_SHIELDS > 0)
    {
        canon.x = shielders[0].blocks[0].x;
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

/// //SOLUCION RANCIA Y POCO ESCALABLE QUE SOLO LA USAMOS PORQUE SE ROMPIO TODO /////////////////
    //if (canonShotList[0].shotState == 0) {
    //    canonShotList[0] = shot;
    //}
///////////////////////////////////////////////////////////

    // unsigned int k = 0;
    // //printf("WATAFAKK MAN ESTOY A PUNTO DE CHEQUIAR LA LISTA Y EL ESTADO DE LA BALA ES: %d  !!!\n", canonShotList[0].shotState );
    // while( (canonShotList[k].shotState != 0) && (k < MAX_CANON_SHOT) ) 
    // {
    //     k++;        // Busco un lugar en la lista (donde el disparo no este activo)
    //     //printf("ENTRO AL WHILE!! k =%d\n", k);
    // }
    // //printf("Between el while y el if, k=%d\n", k);
    // if(k < MAX_CANON_SHOT) {       // Si hay lugar, creo la bala
    //     // //printf("Creo nuevo disparo en k=%d\n", k);
    //     // printf("El estado antes de crear el disparo era %d:\n", canonShotList[k].shotState);
    //     canonShotList[k] = shot;
    //     actualCanonShots++;
    //     //En allegro la dibuja, PERO NO VOY A PRENDER LEDS, ESTA MAL QUE EL BACK DRAWEE 
    // }

    // OTRA FORMA DE RECORRER LA LISTA DE DISPAROS:

    for (int i = 0; i < MAX_CANON_SHOT; i++) {
        if (!canonShotList[i].shotState) {
            canonShotList[i] = shot;
            actualCanonShots++;
            break;
        }
    }
    

//// MIDO TIEMPO
//    own_timer_t temp;
//    setTimer(&temp, 10.0);
//    startTimer(&temp);
//
//    end_play();
//    stop_sound();
//    if( !(player_status() == PLAYING ) )
//    {
//        char mySong[] = "Frontend/Sounds/shoot.wav";
//	    set_file_to_play(mySong);       				
//	    play_sound();
//    }
//
//    printf("EL TIEMPO PASADO ES DE: %f\n", getElapsedTime(&temp));


}


/**
 * @brief Solicita un movimiento continuo del cannon en la direccion indicada
 * @param dir la direccion a la que se desea mover. STOP si se desea parar
*/
void move_cannon(direction_t dir)
{
    canon.direction = dir;
}


/**
 * @brief Elimina los disparos actuales
*/
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


/**
 * @brief Imprime estadísticas de final de partida
*/
void game_score_front(unsigned long int score, int level, int killed_crabs, int killed_octo, int killed_squid, int killed_ufo) {

    // No se hace nada, el puntaje se muestra al cargar el nombre

}


void pause_game_front(void) 
{
    stopTimer(&fpsTimer);   // Para que deje de generar eventos durante la pausa
    move_cannon(STOP);      // Dejo de mover wl canon
}

void resume_game_front(void) 
{
    startTimer(&fpsTimer);   // Para que vuelva a generar eventos
}


void initCanon(void)
{
    for (int i = 0; i < CANON_BLOCKS; i++)   // La altura y ancho de los bloques son 0, porque cada bloque es realidad son puntos 
    {
        canon.blocks[i].width = 0;            // Un punto es un caso particular de un bloque
        canon.blocks[i].height = 0;
        canon.blocks[i].state = 1;    // No creo que importe mucho el state
    }
    updateCanonBlocksPos(&canon);       //Siempre que se actualize la posicion, hay que actualizar la posicion de todos los bloques que forman el objeto
}


static void updateCanonBlocksPos(canon_t *canon)
{
    canon->blocks[0].x = canon->x + 1;
    canon->blocks[0].y = canon->y;

    canon->blocks[1].x = canon->x;
    canon->blocks[1].y = canon->y + 1;

    canon->blocks[2].x = canon->x + 1;
    canon->blocks[2].y = canon->y + 1;

    canon->blocks[3].x = canon->x + 2;
    canon->blocks[3].y = canon->y + 1;
}


static void updateInvadersBlocksPos(int i, int j)
{
    // Actualizo el primer bloque de la estructura.
    invaders[i][j].blocks[0].x = invaders[i][j].x;
    invaders[i][j].blocks[0].y = invaders[i][j].y;

    // Actualizo el segundo bloque de la estructura.
    invaders[i][j].blocks[1].x = invaders[i][j].x + 1;
    invaders[i][j].blocks[1].y = invaders[i][j].y;
}


static void updateUfoBlocksPos(void)
{   
    UFO_invader.blocks[0].x = UFO_invader.x;
    UFO_invader.blocks[0].y = UFO_invader.y;

    UFO_invader.blocks[1].x = UFO_invader.x + 1;
    UFO_invader.blocks[1].y = UFO_invader.y;

    UFO_invader.blocks[2].x = UFO_invader.x + 2;
    UFO_invader.blocks[2].y = UFO_invader.y;
}


static void updateCanonPos(canon_t *canonPointer)
{
    switch(canonPointer->direction)
    {
      case LEFT:
        if((canonPointer->x - TASA_DE_CAMBIO_CANON) >= 0)
        {
          canonPointer->x -= TASA_DE_CAMBIO_CANON;
        }
        break;

      case RIGHT:
        if((canonPointer->x  +  CANON_WIDTH + TASA_DE_CAMBIO_CANON) < D_WIDTH)
        {
          canonPointer->x += TASA_DE_CAMBIO_CANON;
        }
        break;

      case STOP:
      default:
        break;
    }
    updateCanonBlocksPos(canonPointer);
}


static void drawCanon(void)
{
    updateCanonPos(&canon);
    canon_t canonAux = canon;
    canonAux.x = (int)canon.x;      // Para castear a int
    updateCanonBlocksPos(&canonAux);
    for (int i = 0; i < CANON_BLOCKS; i++)
    {
      dcoord_t coord = { .x = canonAux.blocks[i].x, .y = canonAux.blocks[i].y};   // Casteo a int, en realidad a uint8_t deberia ser
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
    }
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
                dcoord_t coord = { .x = invaderShotList[i].x, .y = invaderShotList[i].y  };
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

                dcoord_t coord = { .x = (int)canonShotList[iCont].x, .y = (int)canonShotList[iCont].y  };  // Castia bien pa
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
                    if( coord.x >=0 && coord.x <= (D_WIDTH -1) )
                        disp_write(coord, D_ON);
                    coord.x++;
                    if( coord.x >=0 && coord.x <= (D_WIDTH -1) )  
                        disp_write(coord, D_ON);
                   // TODO: Ver de hacer un for para dibujar rectangulos.   
              }
        }
    }

    if (UFO_invader.invaderState) 
    {    
        if( UFO_invader.x >= ( (-1)*(UFO_WIDTH + 1) )  && UFO_invader.x < D_WIDTH )  // MAGIC NUMBERS
        {
            //dcoord_t coord = { .x = (int)invaders[i][j].blocks[0].x, .y = (int)invaders[i][j].blocks[0].y };
            //disp_write(coord, D_ON);     NO PENSE EL UFOOO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            for (int i = 0; i < UFO_BLOCKS; i++)
            {
                dcoord_t coord = { .x = (int)UFO_invader.blocks[i].x, .y = (int)UFO_invader.blocks[i].y };
                if(coord.x >=0 && coord.x <= (D_WIDTH -1) )
                    disp_write(coord, D_ON);
            }
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
            updateInvadersBlocksPos(i, j);
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
    else {
        for (int i = 0; i < FIL_INVADERS; i++)
        {
            for(int j = 0; j < COL_INVADERS; j++ )
            {
                if(nextDirection == LEFT)
                {
                    invaders[i][j].x -= tasaDeCambioInvaders;
                    updateInvadersBlocksPos(i, j);
                }
                else if(nextDirection == RIGHT)
                {
                    invaders[i][j].x += tasaDeCambioInvaders;
                    updateInvadersBlocksPos(i, j);
                }
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
                if( (invaders[i][j].x + INVADER_WIDTH) > D_WIDTH - INVADERS_WALL )     //Al menos seguro que el ultimo de todos esta vivo, el ultimo que quedo con el i j, porque si salto por exceso el if te lo asegura, si no, salto por el while
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
    shield->blocks[0].x = x_shield;
    shield->blocks[0].y = y_shield;
    shield->blocks[0].height = 0;
    shield->blocks[0].width = 0;
    shield->blocks[0].state = STATE_0;

    shield->blocks[1].x = x_shield + 1;
    shield->blocks[1].y = y_shield;
    shield->blocks[1].height = 0;
    shield->blocks[1].width = 0;
    shield->blocks[1].state = STATE_0;

    shield->blocks[2].x = x_shield;
    shield->blocks[2].y = y_shield + 1;
    shield->blocks[2].height = 0;
    shield->blocks[2].width = 0;
    shield->blocks[2].state = STATE_0;

    shield->blocks[3].x = x_shield + 1;
    shield->blocks[3].y = y_shield + 1;
    shield->blocks[3].height = 0;
    shield->blocks[3].width = 0;
    shield->blocks[3].state = STATE_0;
}

static void placeShields(void)
{
    for (int i = 0; i < TOTAL_SHIELDS; i++)
    {
        int x_shield =  i * DIST_2 + PIXELS_MARGIN ;  // Calcula la posicion en x de los shields

        int y_shield = SHIELDS_Y1;                     // OJO QUE POR LA CUENTA EL USUARIO LA PUEDE CAGAR Y DIBUJAR AFUERA DEL MAPA

        createShield(x_shield, y_shield, &shielders[i] );
    }
}


static void drawShields(void)
{
    for (int i = 0; i < TOTAL_SHIELDS; i++)
    {
        if( shielders[i].blocks[0].state != DEATH_STATE)   // Si el bloque no esta muerto, lo dibujo. Recordar que el color se lo asocia con el estado de la vida
        {
            dcoord_t coord = { .x = shielders[i].blocks[0].x, .y = shielders[i].blocks[0].y };     // Revisar por el tamaño de invaders
            disp_write(coord, D_ON);
        }
        if( shielders[i].blocks[1].state != DEATH_STATE)
        {
            dcoord_t coord = { .x = shielders[i].blocks[1].x, .y = shielders[i].blocks[1].y };     // Revisar por el tamaño de invaders
            disp_write(coord, D_ON);
        }
        if( shielders[i].blocks[2].state != DEATH_STATE)
        {
            dcoord_t coord = { .x = shielders[i].blocks[2].x, .y = shielders[i].blocks[2].y };     // Revisar por el tamaño de invaders
            disp_write(coord, D_ON);
        }
        if( shielders[i].blocks[3].state != DEATH_STATE)
        {
            dcoord_t coord = { .x = shielders[i].blocks[3].x, .y = shielders[i].blocks[3].y };     // Revisar por el tamaño de invaders
            disp_write(coord, D_ON);
        }
    }
}


static int getCollisionOnBlock(collBoxShot_t *boxOfTheShot)     // NO esta tocada, REVISAR
{
    int colision = 0;
    int i = 0;
    while(i < TOTAL_SHIELDS && !colision)                 //Chequea en cada shield si hubo colision o no
    {

        collBoxShot_t boxOfBlock1 = {  .x = shielders[i].blocks[0].x,
                                       .y = shielders[i].blocks[0].y,
                                       .height = 0,
                                       .width = 0,           
                                   };            
        collBoxShot_t boxOfBlock2 = {  .x = shielders[i].blocks[1].x,
                                       .y = shielders[i].blocks[1].y,
                                       .height = 0,
                                       .width = 0,           
                                   };
        collBoxShot_t boxOfBlock3 = {  .x = shielders[i].blocks[2].x,
                                       .y = shielders[i].blocks[2].y,
                                       .height = 0,
                                       .width = 0,           
                                   };
        collBoxShot_t boxOfBlock4 = {  .x = shielders[i].blocks[3].x,
                                       .y = shielders[i].blocks[3].y,
                                       .height = 0,
                                       .width = 0,           
                                   };

        if(  shielders[i].blocks[0].state != DEATH_STATE && isCollision(boxOfTheShot, &boxOfBlock1) )
        {
            colision = 1;
            shielders[i].blocks[0].state++;
        }
        else if(  shielders[i].blocks[1].state != DEATH_STATE && isCollision(boxOfTheShot, &boxOfBlock2) )
        {
            colision = 1;
            shielders[i].blocks[1].state++;
        }
        else if(  shielders[i].blocks[2].state != DEATH_STATE && isCollision(boxOfTheShot, &boxOfBlock3) )
        {
            colision = 1;
            shielders[i].blocks[2].state++;
        }
        else if(  shielders[i].blocks[3].state != DEATH_STATE && isCollision(boxOfTheShot, &boxOfBlock4) )
        {
            colision = 1;
            shielders[i].blocks[3].state++;
        }
        i++;
    }
    return colision;
}

static void shouldUFOappear(void)
{
    if(  !(rand() % probUfo) && !UFO_invader.invaderState )   // Podria aparecer UFO o no. Si ya hay un UFO, no puede haber otro
    {
        UFO_invader.invaderState = 1;
        UFO_invader.direction = rand()%2 ? RIGHT : LEFT ;                          //Aparece, pero quiero saber si por derecha o izquierda
        UFO_invader.x = (UFO_invader.direction == RIGHT) ? (-1)*(UFO_WIDTH + 1) : D_WIDTH; // Se le calcula la posicion en X inicial, dependiendo de si viene por derecha o izq.
    }                                                     // MAGIC NUMBER EN EL 2 IBA EL UFO WIDTH. MAY START WITH LEDS OUT OF THE DISP
}

static int getColisionOnUFO(collBoxShot_t *boxOfTheShot)
{
    int colision = 0;
    if(UFO_invader.invaderState)                            // Si hay un ufo entonces puede llegar a haber una colsion, entonces chequeo
    {
        collBoxShot_t boxOfUFO = {  .x = UFO_invader.x,
                                    .y = UFO_invader.y,
                                    .width = UFO_WIDTH,           // MAGIC NUMBER, OMG SUENA MAL 1 
                                    .height = UFO_HEIGHT,          // MAGIC NUMBER, OMG SUENA MAL 1  SHOULDNT IT BE 2?
                                 };
        if( (colision = isCollision( &boxOfUFO, boxOfTheShot )) )
        {
            UFO_invader.invaderState = 0;
        }
    }
    return colision;
}

static void moveUFO(void)
{
    if (UFO_invader.invaderState) 
    {
        if (UFO_invader.direction == RIGHT) 
        {
            UFO_invader.x += TASA_DE_CAMBIO_NODRIZA;
        }
        else
        {
            UFO_invader.x -= TASA_DE_CAMBIO_NODRIZA;
        }
    }
    updateUfoBlocksPos();
}

static void restartTasas(void)
{
    tasaDeCambioInvaders = MIN_SPEED_INVADER;
    probDisparoInvaders = MIN_POSIBILIY_OF_SHOT_FROM_INVADERS;
    probUfo = MIN_POSIBILIY_OF_APPEAR_UFO;
}