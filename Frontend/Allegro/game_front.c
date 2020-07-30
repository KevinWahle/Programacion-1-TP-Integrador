/***************************************************************************//**
  @file     +gameall+
  @brief    +Todos ls recursos para el funcionamiento del juego+
  @author   +Grupor3+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdio.h>    // SOLO PARA DEBUGEAR
// #include <time.h>
// #include <allegro5/allegro.h>
// #include <allegro5/allegro_color.h>
// #include <allegro5/allegro_image.h>
// #include <allegro5/allegro_primitives.h>
#include <string.h>

#include "headall.h"
#include "shared_res.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TASA_DE_CAMBIO_CANON 3           // Velocidad del canon   
#define TASA_DE_CAMBIO_BALA 4            // Velocidad de la bala
#define TASA_DE_CAMBIO_INVADERS 0.5      // MAL!!! ES VARIABLE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define TASA_DE_CAMBIO_NODRIZA 2         // Velocidad de la nave nodriza

#define SHOT_HEIGHT 15                   // Tamanio del disparo, sirve para hacer la caja de colision
#define SHOT_WIDTH 4                     // idem

// INVADERS POSITION
#define INVADERS_WIDTH_PERCENT  0.6      // Porcentaje de los invaders a lo ancho de la pantalla (0-1)
#define INVADERS_HEIGHT_PERCENT  0.3     // Porcentaje de los invaders a lo alto de la pantalla (0-1)
#define INVADERS_START_HEIGHT_PERCENT  0.15    // Porcentaje de la pantalla donde inician los invaders (desde arriba)

#define INVADERS_FLOOR (D_HEIGHT*0.65)   // Espacio desde el techo hasta "piso" de los invasores
#define INVADERS_WALL (D_WIDTH*0.01)     // Espacio entre el borde derecho e izquierdo en el que van a robotar los invaders
#define INVADERS_FALL (D_HEIGHT*0.02)    // Espacio de caida de los invaders al llegar a cada tope 


#define MAX_INVADERS_SHOT 20             // Es la mayor cantidad de disparos de los invaders que puede llegar a haber en el juego

#define MAX_CANON_SHOT 8                 // Es la mayor cantidad de disparos del canon que puede haber en el juego. Es decir la max cant. de balas visibles


#define CANNON_RESIZE_PERCENT    1.5     // Factor de ajuste de tamanio del bitmap, > 1 => se agranda el bitmap
#define UFO_RESIZE_PERCENT    0.4        // idem anterior pero para la nodriza
#define INVADERS_RESIZE_PERCENT  0.6     // idem anterior pero para los invaders

//MACROS. Tienen el objetivo de facilitar la lectura en codigo del ancho y alto de los bitmap. Como el ancho y alto del bitmap no siempre es el que viene por default
#define AL_GET_CANNON_WIDTH(x)    (al_get_bitmap_width(x)*CANNON_RESIZE_PERCENT)  
#define AL_GET_CANNON_HEIGHT(x)   (al_get_bitmap_height(x)*CANNON_RESIZE_PERCENT)
#define AL_GET_UFO_WIDTH(x)       (al_get_bitmap_width(x)*UFO_RESIZE_PERCENT)
#define AL_GET_UFO_HEIGHT(x)      (al_get_bitmap_height(x)*UFO_RESIZE_PERCENT)
#define AL_GET_INVADER_WIDTH(x)   (al_get_bitmap_width(x)*INVADERS_RESIZE_PERCENT)
#define AL_GET_INVADER_HEIGHT(x)  (al_get_bitmap_height(x)*INVADERS_RESIZE_PERCENT)
// Recordar que al_get_bitmap_???(??) se basa en la imagen cargada con al_load_bitmap

#define UFO_HEIGHT_PERCENT  0.05
#define UFO_HEIGHT  (UFO_HEIGHT_PERCENT * D_HEIGHT)

//##### Blocks #####                              // Cada block seria justamente cada bloque que compone a un shield.
#define B_WIDTH_PERCENT  0.03                     // Porcentaje que ocupa el block por sobre el tamanio del display
#define B_HEIGHT_PERCENT  0.03                    // 
#define B_WIDTH    (D_WIDTH * B_WIDTH_PERCENT)
#define B_HEIGHT   (D_WIDTH * B_HEIGHT_PERCENT)
#define Y_PERCENT  0.76

#define Y1  (D_HEIGHT * Y_PERCENT)                // Posicion en y en la que van a estar alineados los shields
#define BLOCK_LIVES 4                             //Vidas del bloque, se puede modificar, pero si se la modifica se debe modificar la cantidad de colores
                                                  // y todos los estados posibles de los bloques
//##### Shields ####

#define TOTAL_SHIELDS 4                  // Para todo n, en particular n = 4

#define SHIELDERS_WIDTH_PERCENT   0.8   // Porcentaje de los shielders a lo ancho de la pantalla (0-1)
#define OFFSET_FROM_WALL_PERCENT  ((1 - SHIELDERS_WIDTH_PERCENT)/2)   // Offset se refiere a la distancia en x que queda entre los puntos (0, y) y el shield que esta mas a la izquierda
#define SHIELD_WIDTH  (B_WIDTH * 3) // Ancho del shield. No es un parametro para cambiar, pues no se pueden agregar blockes al shield asi porque si, porque a cada bloque se le debe hardcodear su posicion relativa a los demas bloques del shield
#define SHIELDERS_WIDTH_ABSOLUTE  (SHIELDERS_WIDTH_PERCENT * D_WIDTH)
#define OFFSET_FROM_WALL_ABSOLUTE  (OFFSET_FROM_WALL_PERCENT * D_WIDTH)

#define DIST   ((SHIELDERS_WIDTH_ABSOLUTE - TOTAL_SHIELDS * SHIELD_WIDTH)/(TOTAL_SHIELDS - 1) )    // Cuenta que se usa en void placeShields(void), justamente para ubicarlos adecuadamente


//TOPES MAXIMOS Y MINIMOS DE VELOCIDAD DE INVADERS Y 
#define MAX_SPEED_INVADER  5
#define MIN_SPEED_INVADER  0.25

#define MAX_POSIBILIY_OF_SHOT_FROM_INVADERS  50
#define MIN_POSIBILIY_OF_SHOT_FROM_INVADERS  900


#define MAX_POSIBILIY_OF_APPEAR_UFO  500
#define MIN_POSIBILIY_OF_APPEAR_UFO  1200

#define DEATH_STATE STATE_4

// Color de los escudos                     //Aca se deberian agregar los colores si se agregan vidas por ejemplo
#define COLOR_STATE_0 "green"
#define COLOR_STATE_1 "yellow"
#define COLOR_STATE_2 "orange"
#define COLOR_STATE_3 "red" 

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

enum blockStates {STATE_0, STATE_1, STATE_2, STATE_3, STATE_4};   // STATE_0 seria el estado del bloque sin danios. STATE_4 en este caso es el ultimo estado


static char *blockColors[BLOCK_LIVES] = {   COLOR_STATE_0,               
                                            COLOR_STATE_1,
                                            COLOR_STATE_2,
                                            COLOR_STATE_3,          // Despues, agregar aca, en el arreglo
                                        };


// enum SHOT_TYPES {CANON_SHOT, INVADER_SHOT};                 // Esto avria que eliminarlo

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
    char *color;         // Apunta al string del color que deberia tener dependiendo el estado en que este
}block_t;

//Objeto shield
typedef struct
{
    block_t block_1;     //Aclaracion: El shield tiene 5 blocks. Por eso no se puede hacer un shields con mas o menos blocks
    block_t block_2;     // No se pueden agregar bloques asi porque si al shield porque cada blocke debe ser codiado su posicion
    block_t block_3;     // LO QUE SI SE PUEDE HACER, es poner N shields, y modificar su altura, ancho, esparcion en el mapa.
    block_t block_4;     
    block_t block_5;
}shield_t;


typedef int cannonPosition_t;


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE (SOLO PARA SHARED_RES)
 ******************************************************************************/

/************ALLEGRO VARIABLES DEFINITION***************/
ALLEGRO_BITMAP *canonPointer = NULL;
ALLEGRO_EVENT_QUEUE *timer_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_FONT * fontsc = NULL;

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
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Ejecuta un disparo del invader
 * @param i fila de la matriz de invader
 * @param j columan de la matriza de invader
 * @return ???????????????????????????????????????????????????????????????????
*/
static int invaderShot(int i, int j);

/**
 * @brief Ve si hubo una colision del disparo ejecutado por algun invader
 * @return ???????????????????????????????????????????????????????????????????
*/
static void getInvaderShotCollison(void);

/**
 * @brief Ve si hubo una colision del disparo ejecutado por el canon
 * @return ???????????????????????????????????????????????????????????????????
*/
static void getCanonShotCollision(void);

/**
 * @brief mueve el conjunto invader
 * @param direction la ultima direccion con la que se movio el conjunto invader
 * @return la direccion con la que se movio
*/
static direction_t moveInvaders(direction_t direction);

/**
 * @brief mueve el conjunto para abajo
 * @return ????????????????????????????????????????????????????????????????????
*/
static void moveInvadersDown(void);

/**
 * @brief dice si toco piso o no algun invader
 * @return si algun invader toco la linea horizontal que se considere como "piso"
*/
static int is_invadersOnFloor(void);

/**
 * @brief ejecuta o no un disparo de los invaders
 * @return ?????????????????????????????????????????????????????????????????????
*/
static void shouldInvaderShot(void);

/**
 * @brief Crea un shield
 * @param direction la ultima direccion con la que se movio el conjunto invader
 * @param x_shield  la coord en x
 * @param y_shield  la coord en y
 * @param shield_t* shield: ?????????????????????????????????????????????//????
 * @return lon la que se movio
*/
static void createShield(int x_shield, int y_shield, shield_t *shield);

/**
 * @brief Ubica los shields en el mapa
 * @return ?????????????????????????????????????????????????????????????????????
*/
static void placeShields(void);

/**
 * @brief Dibuja los shields
 * @return ????????????????????????????????????????????????????????????????????
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
 * @param collBox_t*  la direccion de la caja 1 
 * @param collBox_t* la direccion de la caja 2
 * @return 1 si chocan 0 si no
*/
static int isCollision( collBoxShot_t * box1, collBoxShot_t * box2);

/**
 * @brief dibuja los invaders
 * @param invader_t recibe la matriz de los invaders 
 * @return ?????????????????????????????????????????????????????????????????????????
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
 * @return ?????????????????????????????????????????????????????????????????????????
*/
static void moveUFO(void);

/**
 * @brief dice si hubo colision o no de alguna caja con la nodriza
 * @param collBoxShot_t *boxOfTheShot: Direccion de la caja 
 * @return ?????????????????????????????????????????????????????????????????????????
*/
static int getColisionOnUFO(collBoxShot_t *boxOfTheShot);

/**
 * @brief hace aparecer o no a UFO 
 * @return ?????????????????????????????????????????????????????????????????????????
*/
static void shouldUFOappear(void);

/**
 * @brief Actualiza la posicion y dibuja el cannon
*/
static void drawCannon(void);



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
// #define PRUEBA
#ifdef PRUEBA
int main() {
  if (init_front())
    return -1;

  int running = 1;

  init_game();

  while (running) {
    update_front_event();
    event_t event = get_next_event();
    switch (event) {
      case MOVE_LEFT:
        move_cannon(LEFT);
        break;

      case MOVE_RIGHT:
        move_cannon(RIGHT);
        break;

      case MOVE_LEFT_REL:
      case MOVE_RIGHT_REL:
        move_cannon(STOP);
        break;

      case MOVE_UP:
        break;

      case MOVE_DOWN:
        break;

      case CLICK_BTN:
        shoot_cannon();
        break;

      case PAUSE_BTN:
        break;

      case EXIT_EVENT:
        running = 0;
        break;
    }
    redraw();
  }

  destroy_front();
  return 0;
}
#endif //PRUEBA
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void init_game(void) {

  placeInvaders();

  placeShields();
  
  clean_shoots();

  drawCannon();

  al_flip_display(); //Flip del backbuffer, pasa a verse a la pantalla

  al_start_timer(timer); //Recien aca EMPIEZA el timer

}

void redraw(void)
{
    ALLEGRO_EVENT ev;
    if (al_get_next_event(timer_queue, &ev)) //Toma un evento de la timer_queue
    {
        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

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

            drawCannon();

            //game_score_front(30 , 25, 20, 15, 3, 7);      // ESTA LA LLAMA EL BACK, DESCOMENTAR PARA DEBUG


            al_flip_display(); 
        }
    }
}

void move_cannon(direction_t dir)
{
  cannonDir = dir;
}

void reviveCanon(void)
{
    if(TOTAL_SHIELDS > 0)
    {
        cannonXpos = shielders[0].block_1.x;
    }
    else
    {
        cannonXpos = D_WIDTH/2;
    }
}

void shoot_cannon(void)
{   
    int ship_width = AL_GET_CANNON_WIDTH(canonPointer);
    int ship_height = AL_GET_CANNON_HEIGHT(canonPointer);
    
    int x_shot = (ship_width + 2* cannonXpos  )/2;
    int y_shot = D_HEIGHT - ship_height;
    
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
        al_draw_line(x_shot, y_shot, x_shot, y_shot - 15 , al_color_name("white"), 0);
               // TODO: Cambiar por codigo OK
    }
    // ARRAY OVERFLOW
                  // TODO: Cambiar por codigo de error
}

void game_score_front(unsigned long int score, int level, int killed_crabs, int killed_octo, int killed_squid, int killed_ufo)
{   
    al_clear_to_color(al_map_rgb(0, 0, 0));
    char scoreText[] = "Score: ";
    char stringScore[10];
    sprintf(stringScore, "%d", (int)score);
    strcat (scoreText, stringScore );

    al_draw_text(fontsc, al_map_rgb(255, 255, 255), D_WIDTH / 2,  (D_HEIGHT / 8)*1 , ALLEGRO_ALIGN_CENTER, scoreText);

    char levelText[] = "Level: ";
    char stringLevel[10];
    sprintf(stringLevel, "%d", level);
    strcat (levelText, stringLevel ); 
    al_draw_text(fontsc, al_map_rgb(255, 255, 255), D_WIDTH / 2,  (D_HEIGHT / 8)*2, ALLEGRO_ALIGN_CENTER, levelText); 

    char killedCrabsText[] = "Killed crabs: ";
    char stringCrabs[28];
    sprintf(stringCrabs, "%d", killed_crabs);
    strcat (killedCrabsText, stringCrabs ); 
    al_draw_text(fontsc, al_map_rgb(255, 255, 255), D_WIDTH / 2,  (D_HEIGHT / 8)*4, ALLEGRO_ALIGN_CENTER, killedCrabsText); 
    
    char killedOctoText[] = "Killed octo: ";
    char stringOcto[30];
    sprintf(stringOcto, "%d", killed_octo);
    strcat (killedOctoText, stringOcto ); 
    al_draw_text(fontsc, al_map_rgb(255, 255, 255), D_WIDTH / 2,  (D_HEIGHT / 8)*5, ALLEGRO_ALIGN_CENTER, killedOctoText);

    char killedSquidText[] = "Killed squid: ";
    char stringSquid[30];
    sprintf(stringSquid, "%d", killed_squid);
    strcat (killedSquidText, stringSquid ); 
    al_draw_text(fontsc, al_map_rgb(255, 255, 255), D_WIDTH / 2,  (D_HEIGHT / 8)*6, ALLEGRO_ALIGN_CENTER, killedSquidText);

    char killedUfoText[] = "Killed UFO: ";
    char stringUfo[30];
    sprintf(stringUfo, "%d", killed_ufo);
    strcat (killedUfoText, stringUfo ); 
    al_draw_text(fontsc, al_map_rgb(255, 255, 255), D_WIDTH / 2,  (D_HEIGHT / 8)*7, ALLEGRO_ALIGN_CENTER, killedUfoText);

    al_flip_display();
}

void update_speed_front(int newSpeed, int maxSpeed) {
    //TODO
    return;
}

void pause_game_front(void) {
    al_stop_timer(timer);   // Para que deje de generar eventos durante la pausa
}

void resume_game_front(void) {
    al_resume_timer(timer);   // Para que vuelva a generar eventos
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static int invaderShot(int i, int j)
{
    invader_t invader = invaders[i][j];
    
    int ship_width = AL_GET_INVADER_WIDTH( invader.invadersPointer );
    int ship_height = AL_GET_INVADER_HEIGHT( invader.invadersPointer );
    
    int x_shot = (ship_width + 2* invaders[i][j].x)/2;
    int y_shot = invaders[i][j].y + ship_height;
    
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
        al_draw_line(x_shot, y_shot, x_shot, y_shot + 15 , al_color_name("white"), 0);
        return 0;       // TODO: Cambiar por codigo OK
    }
    // ARRAY OVERFLOW
    return 1;           // TODO: Cambiar por codigo de error
}

static void getInvaderShotCollison(void)
{
    if(actualInvadersShots > 0)
    {

        collBoxShot_t canonBox = {  .x = cannonXpos ,
                                    .y = D_HEIGHT - AL_GET_CANNON_HEIGHT(canonPointer),           // TODO: Hacer una estructura o constante
                                    .height = AL_GET_CANNON_HEIGHT(canonPointer),
                                    .width = AL_GET_CANNON_WIDTH(canonPointer)
                                 };

        int i = 0;
        int foundShots = 0;
        int colisionDetected = 0;
        while (i < MAX_INVADERS_SHOT && foundShots < actualInvadersShots) 
        {
            if (invaderShotList[i].shotState == 1) {
                foundShots++;

                al_draw_line( invaderShotList[i].x, invaderShotList[i].y, invaderShotList[i].x , invaderShotList[i].y + 15, al_color_name("white"), 0 );
                invaderShotList[i].y += TASA_DE_CAMBIO_BALA;


                collBoxShot_t collBoxShotFromInvader = {  .x = invaderShotList[i].x - SHOT_WIDTH/2 ,
                                                          .y = invaderShotList[i].y ,
                                                          .height = SHOT_HEIGHT , 
                                                          .width = SHOT_WIDTH
                                                       };

                if( isCollision( &collBoxShotFromInvader, &canonBox ) )     // Choque con Cannon
                {
                    invaderShotList[i].shotState = 0;
                    colisionDetected++;
                    add_event(CANNON_COLL_EV);        // Agrego evento de colision con cannon
                    reviveCanon();
                }
                else if( getCollisionOnBlock( &collBoxShotFromInvader ) )   // Choque con bloque
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

                al_draw_line( canonShotList[iCont].x, canonShotList[iCont].y, canonShotList[iCont].x , canonShotList[iCont].y - SHOT_HEIGHT, al_color_name("white"), 0 );
                canonShotList[iCont].y -= TASA_DE_CAMBIO_BALA;

                collBoxShot_t collBoxShotFromCanon =   {  .x = canonShotList[iCont].x - SHOT_WIDTH/2 ,
                                                          .y = canonShotList[iCont].y - SHOT_HEIGHT ,
                                                          .height = SHOT_HEIGHT , 
                                                          .width = SHOT_WIDTH
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
                else
                {
                    for(int i = 0; i < FIL_INVADERS; i++)
                    {
                        for (int j = 0; j < COL_INVADERS; j++)
                        {
                            if( invaders[i][j].invaderState  )
                            {
                                collBoxShot_t invaderBox = {  .x = invaders[i][j].x ,
                                                              .y = invaders[i][j].y ,           // TODO: Hacer una estructura o constante
                                                              .height = AL_GET_INVADER_HEIGHT(invaders[i][j].invadersPointer),
                                                              .width = AL_GET_INVADER_WIDTH(invaders[i][j].invadersPointer)
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

void placeInvaders(void)
{
    // Guardo el ancho del invader más grande, que será el de la última fila
    int max_inv_width = AL_GET_INVADER_WIDTH(invaders[FIL_INVADERS-1][0].invadersPointer);

    for (int i = 0; i < FIL_INVADERS; i++)
    {
        for (int j = 0; j < COL_INVADERS; j++)
        {
            int inv_width = AL_GET_INVADER_WIDTH(invaders[i][j].invadersPointer);
            int inv_height = AL_GET_INVADER_HEIGHT(invaders[i][j].invadersPointer);
            
            // Cáclulo del centro en x de los invasores
            int x_mid =  j * (D_WIDTH*INVADERS_WIDTH_PERCENT-max_inv_width)/(COL_INVADERS-1) + max_inv_width/2 + D_WIDTH*(1-INVADERS_WIDTH_PERCENT)/2 ;
            
            int x_pos =  x_mid - inv_width/2;
            int y_pos = i * (D_HEIGHT*INVADERS_HEIGHT_PERCENT-inv_height)/(FIL_INVADERS-1) + D_HEIGHT*INVADERS_START_HEIGHT_PERCENT;
            al_draw_scaled_bitmap(invaders[i][j].invadersPointer,
                          0, 0, al_get_bitmap_width(invaders[i][j].invadersPointer), al_get_bitmap_height(invaders[i][j].invadersPointer),
                          x_pos, y_pos, AL_GET_INVADER_WIDTH(invaders[i][j].invadersPointer), AL_GET_INVADER_HEIGHT(invaders[i][j].invadersPointer),      // Con que tamaño queres que se dibuje la imagen
                          0);
            invaders[i][j].x = x_pos;
            invaders[i][j].y = y_pos;
            invaders[i][j].invaderState = 1; //Ademas de colocar las naves, tambien les doy vida en el juego 
        }
    }
}

static void drawAliveInvaders(void)
{
    for (int i = 0; i < FIL_INVADERS; i++)
    {
        for (int j = 0; j < COL_INVADERS; j++)
        {
            if( (invaders[i][j].invaderState) )
                al_draw_scaled_bitmap(invaders[i][j].invadersPointer,
                          0, 0, al_get_bitmap_width(invaders[i][j].invadersPointer), al_get_bitmap_height(invaders[i][j].invadersPointer),
                          invaders[i][j].x, invaders[i][j].y, AL_GET_INVADER_WIDTH(invaders[i][j].invadersPointer), AL_GET_INVADER_HEIGHT(invaders[i][j].invadersPointer),      // Con que tamaño queres que se dibuje la imagen
                          0);
        }
    }

    if (UFO_invader.invaderState) 
    {
        if( UFO_invader.x >= ( (-1)*AL_GET_UFO_WIDTH(UFO_invader.invadersPointer) )  && UFO_invader.x <= (D_WIDTH + AL_GET_UFO_WIDTH(UFO_invader.invadersPointer)) )
        {
            al_draw_scaled_bitmap(UFO_invader.invadersPointer,
                          0, 0, al_get_bitmap_width(UFO_invader.invadersPointer), al_get_bitmap_height(UFO_invader.invadersPointer),
                          UFO_invader.x, UFO_invader.y, AL_GET_UFO_WIDTH(UFO_invader.invadersPointer), AL_GET_UFO_HEIGHT(UFO_invader.invadersPointer),      // Con que tamaño queres que se dibuje la imagen
                          0);
        }
        else
        {
            UFO_invader.invaderState = 0;
        }
    }

}

static int isCollision(collBoxShot_t* box1, collBoxShot_t* box2){

    if(box1->x < box2->x + box2->width &&                          // Algoritmo para ver si dos cajas estan chocando
       box2->x < box1->x + box1->width &&
       box1->y < box2->y + box2->height &&
       box2->y < box1->y + box1->height)
       return 1;

    return 0;
}

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
                invaders[i][j].x -= TASA_DE_CAMBIO_INVADERS;
            }
            else if(nextDirection == RIGHT)
            {
                invaders[i][j].x += TASA_DE_CAMBIO_INVADERS;
            }
        }
    }
    return nextDirection;
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
  al_draw_scaled_bitmap(canonPointer,
                0, 0, al_get_bitmap_width(canonPointer), al_get_bitmap_height(canonPointer),
                cannonXpos, D_HEIGHT - AL_GET_CANNON_HEIGHT(canonPointer), AL_GET_CANNON_WIDTH(canonPointer), AL_GET_CANNON_HEIGHT(canonPointer),      // Con que tamaño queres que se dibuje la imagen
                0);
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
                if( invaders[i][j].x + AL_GET_INVADER_WIDTH(invaders[i][j].invadersPointer) > D_WIDTH - INVADERS_WALL )     //Al menos seguro que el ultimo de todos esta vivo, el ultimo que quedo con el i j, porque si salto por exceso el if te lo asegura, si no, salto por el while
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

static void moveInvadersDown(void)
{
    for (int i = 0; i < FIL_INVADERS; i++)
    {
        for(int j = 0; j < COL_INVADERS; j++)
        {
            invaders[i][j].y += INVADERS_FALL; 
        }
    }
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
            if(  !(rand() % MIN_POSIBILIY_OF_SHOT_FROM_INVADERS) )
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

static int getCollisionOnBlock(collBoxShot_t *boxOfTheShot)
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

static void shouldUFOappear(void)
{
    if(  !(rand() % MIN_POSIBILIY_OF_APPEAR_UFO) && !UFO_invader.invaderState )   // Podria aparecer UFO o no. Si ya hay un UFO, no puede haber otro
    {
        UFO_invader.invaderState = 1;
        UFO_invader.direction = rand()%2 ? RIGHT : LEFT ;                          //Aparece, pero quiero saber si por derecha o izquierda
        UFO_invader.x = (UFO_invader.direction == RIGHT) ? (-1)*AL_GET_UFO_WIDTH(UFO_invader.invadersPointer) : D_WIDTH + AL_GET_UFO_WIDTH(UFO_invader.invadersPointer); // Se le calcula la posicion en X inicial, dependiendo de si viene por derecha o izq.
    }
}

static int getColisionOnUFO(collBoxShot_t *boxOfTheShot)
{
    int colision = 0;
    if(UFO_invader.invaderState)                            // Si hay un ufo entonces puede llegar a haber una colsion, entonces chequeo
    {
        collBoxShot_t boxOfUFO = {  .x = UFO_invader.x,
                                    .y = UFO_invader.y,
                                    .width = AL_GET_UFO_WIDTH(UFO_invader.invadersPointer),
                                    .height = AL_GET_UFO_HEIGHT(UFO_invader.invadersPointer),
                                 };
        if(colision = isCollision( &boxOfUFO, boxOfTheShot ) )
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
}

void clean_shoots(void)
{
  for(int i = 0; i < MAX_CANON_SHOT; i++)
  {
    canonShotList[i].shotState = 0;
  }
  for(int i = 0; i < MAX_INVADERS_SHOT; i++)
  {
    invaderShotList[i].shotState = 0;
  }
}