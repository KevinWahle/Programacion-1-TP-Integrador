/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define FPS 60.0 
#define D_WIDTH 800
#define D_HEIGHT 600
#define TASA_DE_CAMBIO 3
#define TASA_DE_CAMBIO_BALA 4
#define TASA_DE_CAMBIO_INVADERS 0.5
#define TASA_DE_CAMBIO_NODRIZA 2

#define SHOT_HEIGHT 15
#define SHOT_WIDTH 4


#define FIL_INVADERS 5
#define COL_INVADERS 9

// INVADERS POSITION
#define INVADERS_WIDTH_PERCENT  0.7    // Porcentaje de los invaders a lo ancho de la pantalla (0-1)
#define INVADERS_HEIGHT_PERCENT  0.4    // Porcentaje de los invaders a lo alto de la pantalla (0-1)
#define INVADERS_START_HEIGHT_PERCENT  0.15    // Porcentaje de la pantalla donde inician los invaders (desde arriba)

#define INVADERS_FLOOR (D_HEIGHT*0.65)        // Espacio desde el techo hasta "piso" de los invasores
#define INVADERS_WALL (D_WIDTH*0.01)          // Espacio entre el borde derecho e izquierdo en el que van a robotar los invaders
#define INVADERS_FALL (D_HEIGHT*0.02)         // Espacio de caida de los invaders al llegar a cada tope 

#define CANT_INVADERS (FIL_INVADERS*COL_INVADERS)

#define CANT_D_POSIBLES_OBJETIVOS CANT_INVADERS // Solo tengo en cuenta disparo del cannon hacia los invaders no al reves.

#define CANT_D_ESCUDOS_POSIBLES 3 // falta para usar esto. No serian 5 habrian como 6 bloquecitos por cada bloque.

#define MAX_INVADERS_SHOT 20         

#define MAX_CANON_SHOT 3

#define CANON_FILE "PNGs/Laser_Cannon.png"
#define CRAB_FILE "PNGs/Crab1.png"
#define OCTO_FILE "PNGs/Octopus1.png"
#define SQUID_FILE "PNGs/Squid1.png"
#define UFO_FILE "PNGs/UFO.png"

//##### CUBOS SHIELDS #####

#define B_WIDTH    (D_WIDTH * 0.03)
#define B_HEIGHT   (D_WIDTH * 0.03)
#define X_PERCENT  0.1
#define Y_PERCENT  0.76

#define X1  (D_WIDTH * X_PERCENT )
#define Y1  (D_HEIGHT * Y_PERCENT)

#define X2  (X1 + B_WIDTH)
#define Y2  (Y1 + B_HEIGHT)

//##### RANCIEDAD

#define TOTAL_SHIELDS 3

#define SHIELDERS_WIDTH_PERCENT   0.8   // Porcentaje de los shielders a lo ancho de la pantalla (0-1)
#define OFFSET_FROM_WALL_PERCENT  ((1 - SHIELDERS_WIDTH_PERCENT)/2)
#define SHIELD_WIDTH  (B_WIDTH * 3)
#define SHIELDERS_WIDTH_ABSOLUTE  (SHIELDERS_WIDTH_PERCENT * D_WIDTH)
#define OFFSET_FROM_WALL_ABSOLUTE  (OFFSET_FROM_WALL_PERCENT * D_WIDTH)

#define DIST   ((SHIELDERS_WIDTH_ABSOLUTE - TOTAL_SHIELDS * SHIELD_WIDTH)/(TOTAL_SHIELDS - 1) )

#define BLOCK_LIVES 4

//TOPES MAXIMOS Y MINIMOS DE VELOCIDAD DE INVADERS Y 
#define MAX_SPEED_INVADER  5
#define MIN_SPEED_INVADER  0.25

#define MAX_POSIBILIY_OF_SHOT_FROM_INVADERS  50
#define MIN_POSIBILIY_OF_SHOT_FROM_INVADERS  900


#define MAX_POSIBILIY_OF_APPEAR_UFO  500
#define MIN_POSIBILIY_OF_APPEAR_UFO  1200

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

enum blockStates {STATE_0, STATE_1, STATE_2, STATE_3, STATE_4};

#define DEATH_STATE STATE_4

// Color de los escudos, PARA SALIR DEL PASO
#define COLOR_STATE_0 "green"
#define COLOR_STATE_1 "yellow"
#define COLOR_STATE_2 "orange"
#define COLOR_STATE_3 "red"

char *blockColors[BLOCK_LIVES] = {  COLOR_STATE_0,
                                    COLOR_STATE_1,
                                    COLOR_STATE_2,
                                    COLOR_STATE_3,
                                 };


enum INVADERS_TYPES {CRAB ,SQUID, OCTO, UFO};

enum DIRECTIONS {LEFT, RIGHT, ERROR_DIREC};

enum SHOT_TYPES {CANON_SHOT, INVADER_SHOT};

enum MYKEYS {
    KEY_SPACE, KEY_DOWN, KEY_LEFT, KEY_RIGHT //arrow keys
};

typedef unsigned char SHOT_TYPE;


typedef struct 
{
    float x;
    float y;
    int shotState;
    SHOT_TYPE type;
}shot_t;

typedef struct 
{
    int x;
    int y;
    int height;
    int width;
}collBoxShot_t;

typedef struct 
{
    float x;
    float y;
    int invaderState;
    int invaderType;
    ALLEGRO_BITMAP *invadersPointer;
}invader_t;

typedef struct 
{
    float x;
    float y;
    int invaderState;
    int invaderType;
    int direction;      //  El UFO puede aparecer desde la izquierda o desde la derecha
    ALLEGRO_BITMAP *invadersPointer;
} UFO_t;

typedef struct 
{
    int x;
    int y;
    int height;
    int width;
    int state;
    char *color;
}block_t;

typedef struct
{
    block_t block_1;
    block_t block_2;
    block_t block_3;
    block_t block_4;
    block_t block_5;
}shield_t;


typedef int cannonPosition_t;

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
int invaderShot(int i, int j);

void getInvaderShotCollison(void);

void canonShot(void);

void getCanonShotCollision(void);

int moveInvaders(int direction);

void moveInvadersDown(void);

int is_invadersOnFloor(void);

void shouldInvaderShot(void);


void createShield(int x_shield, int y_shield, shield_t *shield);
void placeShields(void);
void drawShields(void);
static int isCollision( collBoxShot_t * box1, collBoxShot_t * box2);
int getCollisionOnBlock(collBoxShot_t *boxOfTheShot);

void update_speed_front(int newSpeed);

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void placeInvaders(invader_t ptr_to_struct[FIL_INVADERS][COL_INVADERS]);
static void drawAliveInvaders(invader_t ptr_to_struct[FIL_INVADERS][COL_INVADERS]);
static int decideWhetherChangeDirectionOrNot(int direction);

void moveUFO(void);

int getColisionOnUFO(collBoxShot_t *boxOfTheShot);

void shouldUFOappear(void);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static int initAll(void);

static shot_t invaderShotList[MAX_INVADERS_SHOT];
// Lista de los disparos de los invaders


static int actualInvadersShots; 
static int actualCanonShots;


/************ALLEGRO VARIABLES DEFINITION***************/
static ALLEGRO_DISPLAY * display = NULL;
static ALLEGRO_BITMAP *canonPointer = NULL;
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;
static ALLEGRO_TIMER *timer = NULL;

#define UFO_HEIGHT_PERCENT  0.05
#define UFO_HEIGHT  (UFO_HEIGHT_PERCENT * D_HEIGHT)

UFO_t UFO_invader = {   .y = UFO_HEIGHT,
                        .invaderType = UFO,
                        .invaderState = 0     //Arranca muerta
                    };

// El cañón
static cannonPosition_t cannonXpos = 0;

// Invaders matrix
static invader_t invaders[FIL_INVADERS][COL_INVADERS];


static shot_t canonShotList[MAX_CANON_SHOT];

static int proxDir = LEFT;

//TASAS DE CAMBIO VARIABLES:

static float dxInvader;
static float shotFromInvaderFrec;
 


static const int invadersDistribution [FIL_INVADERS] = {
                                                        SQUID,
                                                        CRAB,
                                                        CRAB,
                                                        OCTO,
                                                        OCTO,
                                                       };

shield_t shielders[TOTAL_SHIELDS];

#define BIG_INVADER OCTO

int main(void) {
    
    srand (time(NULL));

    bool redraw = false;
    bool display_close = false;

    bool key_pressed[4] = {false, false, false, false}; //Estado de teclas, true cuando esta apretada


    if(initAll())
    {
        return -1;
    }
    
    while (!display_close) {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_TIMER)
            {
                int cannon_width = al_get_bitmap_width(canonPointer);
                if(key_pressed[KEY_RIGHT] && (cannonXpos +  cannon_width + TASA_DE_CAMBIO) < D_WIDTH){
                    cannonXpos += TASA_DE_CAMBIO;
                }
                else if(key_pressed[KEY_LEFT] && (cannonXpos - TASA_DE_CAMBIO) > 0) {
                    cannonXpos -= TASA_DE_CAMBIO;
                }
                redraw = true;
            }

            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                display_close = true;

            else if(ev.type == ALLEGRO_EVENT_KEY_DOWN )
            {
                switch (ev.keyboard.keycode)
                {
                case ALLEGRO_KEY_LEFT:
                    key_pressed[KEY_LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key_pressed[KEY_RIGHT] = true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    key_pressed[KEY_SPACE] = true;
                default:
                    break;
                }
            }
            else if(ev.type == ALLEGRO_EVENT_KEY_UP )
            {
                switch (ev.keyboard.keycode)
                {
                case ALLEGRO_KEY_LEFT:
                    key_pressed[KEY_LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key_pressed[KEY_RIGHT] = false;
                    break;
                case ALLEGRO_KEY_SPACE:
                    canonShot();
                default:
                    break;
                }
            }
        }
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            //if(  !(rand() % 60)  )
            //{
            //    invaderShot(FIL_INVADERS - 1 , rand()  % (COL_INVADERS )  );
            //
            //getInvaderShotCollison();
            
            shouldUFOappear();
            moveUFO();

            getCanonShotCollision();

            shouldInvaderShot();
            getInvaderShotCollison();
            

            
            if( !is_invadersOnFloor()  )
                proxDir = moveInvaders(proxDir);


            drawShields();

            drawAliveInvaders(invaders);
            //al_draw_bitmap(canonPointer, cannonXpos, D_HEIGHT - al_get_bitmap_height(canonPointer) , 0); //flags(normalmente en cero, ver doc. para rotar etc)
            al_draw_scaled_bitmap(canonPointer,    // Imagen de fondo del menu
                          0, 0, al_get_bitmap_width(menuImage), al_get_bitmap_height(menuImage),
                          0, 0, al_get_display_width(display), al_get_display_height(display),      // Con que tamaño queres que se dibuje la imagen
                          0);
            
            al_flip_display(); 
        }
    }

    al_shutdown_primitives_addon();
    al_destroy_display(display); //IMPORTANTE: Destruir recursor empleados
    al_destroy_bitmap(canonPointer);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    for (int i = 0; i < FIL_INVADERS; i++) {
        for (int j = 0; j < COL_INVADERS; j++) {
            al_destroy_bitmap(invaders[i][j].invadersPointer);
        }
    }

    return 0;
}

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

//
//void update_speed_front(int newSpeed) {
//    static const int maxSpeed = 100; // Pasarlo a constante segun el back
//    dxInvader = MIN_SPEED_INVADER + (MAX_SPEED_INVADER-MIN_SPEED_INVADER)*newSpeed/maxSpeed;
//    shotFromInvaderFrec = MIN_POSIBILIY_OF_SHOT_FROM_INVADERS + (MAX_POSIBILIY_OF_SHOT_FROM_INVADERS-MIN_POSIBILIY_OF_SHOT_FROM_INVADERS)*newSpeed/maxSpeed;
//    //TODO: Frecuencia de aparicion de UFO
//}


int invaderShot(int i, int j)
{
    invader_t invader = invaders[i][j];
    
    int ship_width = al_get_bitmap_width( invader.invadersPointer );
    int ship_height = al_get_bitmap_height( invader.invadersPointer );
    
    int x_shot = (ship_width + 2* invaders[i][j].x  )/2;
    int y_shot = invaders[i][j].y + ship_height;
    
    shot_t shot = { .x = x_shot,
                    .y = y_shot,
                    .type = INVADER_SHOT,
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
void getInvaderShotCollison(void)
{
    if(actualInvadersShots > 0)
    {

        collBoxShot_t canonBox = {  .x = cannonXpos ,
                                    .y = D_HEIGHT - al_get_bitmap_height(canonPointer),           // TODO: Hacer una estructura o constante
                                    .height = al_get_bitmap_height(canonPointer),
                                    .width = al_get_bitmap_width(canonPointer)
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

                if( isCollision( &collBoxShotFromInvader, &canonBox ) )
                {
                    invaderShotList[i].shotState = 0;
                    colisionDetected++;
                }
                else if( getCollisionOnBlock( &collBoxShotFromInvader ) )
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
void canonShot(void)
{   
    int ship_width = al_get_bitmap_width( canonPointer );
    int ship_height = al_get_bitmap_height( canonPointer );
    
    int x_shot = (ship_width + 2* cannonXpos  )/2;
    int y_shot = D_HEIGHT - ship_height;
    
    shot_t shot = { .x = x_shot,
                    .y = y_shot,
                    .type = INVADER_SHOT,
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
void getCanonShotCollision(void)
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
                                                              .height = al_get_bitmap_height(invaders[i][j].invadersPointer),
                                                              .width = al_get_bitmap_width(invaders[i][j].invadersPointer)
                                                           };

                                if( isCollision( &collBoxShotFromCanon, &invaderBox ) )
                                {
                                    canonShotList[iCont].shotState = 0;
                                    invaders[i][j].invaderState = 0;
                                    colisionDetected++;
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

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void placeInvaders(invader_t ptr_to_struct[FIL_INVADERS][COL_INVADERS])
{
    // Guardo el ancho del invader más grande, que será el de la última fila
    int max_inv_width = al_get_bitmap_width(ptr_to_struct[FIL_INVADERS-1][0].invadersPointer);

    for (int i = 0; i < FIL_INVADERS; i++)
    {
        for (int j = 0; j < COL_INVADERS; j++)
        {
            int inv_width = al_get_bitmap_width(ptr_to_struct[i][j].invadersPointer);
            int inv_height = al_get_bitmap_height(ptr_to_struct[i][j].invadersPointer);
            
            // Cáclulo del centro en x de los invasores
            int x_mid =  j * (D_WIDTH*INVADERS_WIDTH_PERCENT-max_inv_width)/(COL_INVADERS-1) + max_inv_width/2 + D_WIDTH*(1-INVADERS_WIDTH_PERCENT)/2 ;
            
            int x_pos =  x_mid - inv_width/2;
            int y_pos = i * (D_HEIGHT*INVADERS_HEIGHT_PERCENT-inv_height)/(FIL_INVADERS-1) + D_HEIGHT*INVADERS_START_HEIGHT_PERCENT;
            al_draw_bitmap( ptr_to_struct[i][j].invadersPointer, x_pos, y_pos, 0 );
            ptr_to_struct[i][j].x = x_pos;
            ptr_to_struct[i][j].y = y_pos;
            ptr_to_struct[i][j].invaderState = 1; //Ademas de colocar las naves, tambien les doy vida en el juego 
        }
    }
}

static void drawAliveInvaders(invader_t ptr_to_invaders[FIL_INVADERS][COL_INVADERS])
{
    for (int i = 0; i < FIL_INVADERS; i++)
    {
        for (int j = 0; j < COL_INVADERS; j++)
        {
            if( (ptr_to_invaders[i][j].invaderState) )
                al_draw_bitmap( ptr_to_invaders[i][j].invadersPointer, ptr_to_invaders[i][j].x, ptr_to_invaders[i][j].y, 0);  //Dibujo solo los vivos        
        }
    }

    if (UFO_invader.invaderState) 
    {
        if( UFO_invader.x >= ( (-1)*al_get_bitmap_width(UFO_invader.invadersPointer) )  && UFO_invader.x <= (D_WIDTH + al_get_bitmap_width(UFO_invader.invadersPointer)) )
        {
            al_draw_bitmap( UFO_invader.invadersPointer, UFO_invader.x, UFO_invader.y, 0);
        }
        else
        {
            UFO_invader.invaderState = 0;
            printf("F UFO!!\n");
        }
    }

}
static int isCollision(collBoxShot_t* box1, collBoxShot_t* box2){

    if(box1->x < box2->x + box2->width &&
       box2->x < box1->x + box1->width &&
       box1->y < box2->y + box2->height &&
       box2->y < box1->y + box1->height)
       return 1;

    return 0;
}
static int initAll(void)
{
    if (!al_init()) { //Primera funcion a llamar antes de empezar a usar allegro.
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }


    if (!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }

    if (!al_init_image_addon()) { // ADDON necesario para manejo(no olvidar el freno de mano) de imagenes 
        fprintf(stderr, "failed to initialize image addon !\n");
        return -1;
    }


    timer = al_create_timer(1.0 / FPS); //crea el timer pero NO empieza a correr
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_timer(timer);
        return -1;
    }

    canonPointer = al_load_bitmap(CANON_FILE);
    if (!canonPointer) {
        fprintf(stderr, "failed to load image !\n");
        return -1;
    }

    UFO_invader.invadersPointer = al_load_bitmap(UFO_FILE);
    if (!UFO_invader.invadersPointer) {
        fprintf(stderr, "failed to load UFO !\n");
        return -1;
    }
   
    for (int i = 0; i < FIL_INVADERS; i++)
    {
        for (int j = 0; j < COL_INVADERS; j++)                         //Cargo el bitmap a todas las invaders
        {
            invaders[i][j].invaderType = invadersDistribution[i]; //Ademas defino el tipo según la fila 
            const char *file;
            switch(invaders[i][j].invaderType)
            {
                case CRAB:
                    file = CRAB_FILE;
                    break;
                case OCTO:
                    file = OCTO_FILE;
                    break;
                case SQUID:
                    file = SQUID_FILE;
                    break;
                default:
                    file = NULL;
                    break;
            }
            invaders[i][j].invadersPointer = al_load_bitmap(file);
            if (!invaders[i][j].invadersPointer) {
                fprintf(stderr, "failed to load image \"%s\"!\n", file);
                return -1;
            }

        }
    }


    // printf("TERMINE DE CARGAR IMAGENES DE INVADERS\n");

    display = al_create_display(D_WIDTH, D_HEIGHT); // Intenta crear display de 640x480 de fallar devuelve NULL
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source()); //REGISTRAMOS EL TECLADO

    placeInvaders( invaders );

    placeShields();
    

    //void al_draw_bitmap(ALLEGRO_BITMAP *bitmap, float dx, float dy, int flags) 
    al_draw_bitmap(canonPointer, 0, 450, 0); //flags(normalmente en cero, ver doc. para rotar etc)

    al_flip_display(); //Flip del backbuffer, pasa a verse a la pantalla

    al_start_timer(timer); //Recien aca EMPIEZA el timer

    return 0;
}
/*############################################
############################################*/


int moveInvaders(int direction)
{
    int nextDirection = decideWhetherChangeDirectionOrNot(direction); // Me fijo si tengo que mantener la direccion o no, invocando a la funcion
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

static int decideWhetherChangeDirectionOrNot(int direction)
{
    int nextDirection = ERROR_DIREC;
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
                if( invaders[i][j].x + al_get_bitmap_width(invaders[i][j].invadersPointer) > D_WIDTH - INVADERS_WALL )     //Al menos seguro que el ultimo de todos esta vivo, el ultimo que quedo con el i j, porque si salto por exceso el if te lo asegura, si no, salto por el while
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

void moveInvadersDown(void)
{
    for (int i = 0; i < FIL_INVADERS; i++)
    {
        for(int j = 0; j < COL_INVADERS; j++)
        {
            invaders[i][j].y += INVADERS_FALL; 
        }
    }
}
int is_invadersOnFloor(void)
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

void shouldInvaderShot(void)
{
    for (int j = 0; j < COL_INVADERS; j++)
    {
        int i = FIL_INVADERS - 1;
        while( i >= 0  &&   !invaders[i][j].invaderState )  //Busco los invaders (vivos) tales que abajo de ellos no tengan ninguna invader vivo
        {
            i--;
        }
        if( i >= 0)          // entonces se encontro algun invader vivo
        {
            if(  !(rand() % 900) )
                invaderShot(i, j);
        }
    }       
}

void createShield(int x_shield, int y_shield, shield_t *shield)
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

    //al_draw_filled_rectangle(x_shield, y_shield, x_shield + B_WIDTH, y_shield + B_HEIGHT, al_color_name("green")  );
    //al_draw_filled_rectangle(x_shield + B_WIDTH, y_shield, x_shield + B_WIDTH + B_WIDTH, y_shield + B_HEIGHT, al_color_name("green")  );
    //al_draw_filled_rectangle(x_shield + 2*B_WIDTH, y_shield, x_shield + B_WIDTH + 2*B_WIDTH, y_shield + B_HEIGHT, al_color_name("green")  );
    //al_draw_filled_rectangle(x_shield, y_shield + B_HEIGHT, x_shield + B_WIDTH, y_shield + B_HEIGHT + B_HEIGHT, al_color_name("green")  );
    //al_draw_filled_rectangle(x_shield + 2*B_WIDTH, y_shield + B_HEIGHT, x_shield + B_WIDTH + 2*B_WIDTH, y_shield + B_HEIGHT + B_HEIGHT, al_color_name("green")  );

    al_draw_filled_rectangle(shield->block_1.x, shield->block_1.y, shield->block_1.x + B_WIDTH, shield->block_1.y + B_HEIGHT, al_color_name(COLOR_STATE_0)  );
    al_draw_filled_rectangle(shield->block_2.x, shield->block_2.y, shield->block_2.x + B_WIDTH, shield->block_2.y + B_HEIGHT, al_color_name(COLOR_STATE_0)  );
    al_draw_filled_rectangle(shield->block_3.x, shield->block_3.y, shield->block_3.x + B_WIDTH, shield->block_3.y + B_HEIGHT, al_color_name(COLOR_STATE_0)  );
    al_draw_filled_rectangle(shield->block_4.x, shield->block_4.y, shield->block_4.x + B_WIDTH, shield->block_4.y + B_HEIGHT, al_color_name(COLOR_STATE_0)  );
    al_draw_filled_rectangle(shield->block_5.x, shield->block_5.y, shield->block_5.x + B_WIDTH, shield->block_5.y + B_HEIGHT, al_color_name(COLOR_STATE_0)  );

}
void placeShields(void)
{
    for (int i = 0; i < TOTAL_SHIELDS; i++)
    {
        int x_shield =  i * ( SHIELD_WIDTH + DIST ) + OFFSET_FROM_WALL_ABSOLUTE ;

        int y_shield = Y1;

        createShield(x_shield, y_shield, &shielders[i] );
    }
}

void drawShields(void)
{
    for (int i = 0; i < TOTAL_SHIELDS; i++)
    {
        if( shielders[i].block_1.state != DEATH_STATE)
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



int getCollisionOnBlock(collBoxShot_t *boxOfTheShot)
{
    int colision = 0;
    int i = 0;
    while(i < TOTAL_SHIELDS && !colision)
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


void shouldUFOappear(void)
{
    if(  !(rand() % MIN_POSIBILIY_OF_APPEAR_UFO ) && !UFO_invader.invaderState )
    {
        printf("UFO SHOULD APPEAR!!\n");
        UFO_invader.invaderState = 1;
        UFO_invader.direction = rand()%2 ? RIGHT : LEFT ;
        UFO_invader.x = (UFO_invader.direction == RIGHT) ? (-1)*al_get_bitmap_width(UFO_invader.invadersPointer) : D_WIDTH + al_get_bitmap_width(UFO_invader.invadersPointer);
    }
}

int getColisionOnUFO(collBoxShot_t *boxOfTheShot)
{
    int colision = 0;
    if(UFO_invader.invaderState)
    {
        collBoxShot_t boxOfUFO = {  .x = UFO_invader.x,
                                    .y = UFO_invader.y,
                                    .width = al_get_bitmap_width(UFO_invader.invadersPointer),
                                    .height = al_get_bitmap_height(UFO_invader.invadersPointer),
                                 };
        if(colision = isCollision( &boxOfUFO, boxOfTheShot ) )
        {
            UFO_invader.invaderState = 0;
        }
    
    }
    return colision;
}

void moveUFO(void)
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