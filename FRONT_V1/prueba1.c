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

#define FPS    60.0 
#define D_WIDTH 640
#define D_HEIGHT 480
#define TASA_DE_CAMBIO 3
#define TASA_DE_CAMBIO_BALA 2

#define SHOT_HEIGHT 15
#define SHOT_WIDTH 4

#define COLA_DE_DISPARO (450 - SHOT_HEIGHT)
#define POS_EN_Y_DEL_CANNON 450

#define FIL_INVADERS 5
#define COL_INVADERS 9


#define CANT_INVADERS FIL_INVADERS*COL_INVADERS

#define HIGH_INVADERS_SEPARATION 15

#define CANT_D_POSIBLES_OBJETIVOS CANT_INVADERS // Solo tengo en cuenta disparo del cannon hacia los invaders no al reves.

#define CANT_D_ESCUDOS_POSIBLES 5 // falta para usar esto. No serian 5 habrian como 6 bloquecitos por cada bloque.

#define MAX_INVADERS_SHOT 20

#define MAX_CANON_SHOT 3


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

enum SHOT_TYPES {CANON_SHOT, INVADER_SHOT};

enum MYKEYS {
    KEY_SPACE, KEY_DOWN, KEY_LEFT, KEY_RIGHT //arrow keys
};

typedef unsigned char SHOT_TYPE;

typedef struct 
{
    int x;
    int y;
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
    int x;
    int y;
    int invaderState;
    int invaderType;
    ALLEGRO_BITMAP *invadersPointer;
}invader_t;


typedef int cannonPosition_t;

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

int initAll(void);

int isCollision( collBoxShot_t * box1, collBoxShot_t * box2);

int invaderShot(int i, int j);

void getInvaderShotCollison(void);

void canonShot(void);

void getCanonShotCollision(void);
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void placeInvaders(invader_t ptr_to_struct[FIL_INVADERS][COL_INVADERS]);
static void drawAliveInvaders(invader_t ptr_to_struct[FIL_INVADERS][COL_INVADERS]);


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static shot_t invaderShotList[MAX_INVADERS_SHOT];
// Lista de los disparos de los invaders

static int actualInvadersShots; 
static int actualCanonShots;

static shot_t shotCanon;

static shot_t canonShotList[MAX_CANON_SHOT];

/************ALLEGRO VARIABLES DEFINITION***************/
static ALLEGRO_DISPLAY * display = NULL;
static ALLEGRO_BITMAP *image = NULL;
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;
static ALLEGRO_TIMER *timer = NULL;

// El cañón
cannonPosition_t cannonXpos = 0;

// Invaders matrix
static invader_t invaders[FIL_INVADERS][COL_INVADERS];


int main(void) {

    srand (time(NULL));

    bool redraw = false;
    bool display_close = false;

    bool key_pressed[4] = {false, false, false, false}; //Estado de teclas, true cuando esta apretada

    shot_t shot1 = {0,0,0};
    collBoxShot_t collBoxShot = {0,0,0,0};

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
                if(key_pressed[KEY_RIGHT])
                    cannonXpos += TASA_DE_CAMBIO;
                else if(key_pressed[KEY_LEFT] )
                    cannonXpos -= TASA_DE_CAMBIO ;

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

            if(  !(rand() % 60)  )
            {
                invaderShot(FIL_INVADERS - 1 , rand()  % (COL_INVADERS )  );
            }

            /*if(key_pressed[KEY_SPACE] && !shot1.shotState) 
            {
                int ship_width = al_get_bitmap_width(image);
                int ship_height = al_get_bitmap_height(image);

                al_draw_line((ship_width + 2*cannonXpos)/2, POS_EN_Y_DEL_CANNON , (ship_width + 2*cannonXpos)/2, COLA_DE_DISPARO, al_color_name("white"), 0);

                shot1.shotState = 1;
                shot1.x = (ship_width + 2*cannonXpos)/2;
                shot1.y = 450;
                collBoxShot.x = shot1.x - SHOT_WIDTH/2;
                collBoxShot.y = shot1.y - SHOT_HEIGHT;
                collBoxShot.width = SHOT_WIDTH;
                collBoxShot.height = SHOT_HEIGHT;
            }
            if(shot1.shotState)
            {
                al_draw_line(shot1.x, shot1.y , shot1.x,  shot1.y - 15, al_color_name("white"), 0);
                shot1.y -= TASA_DE_CAMBIO_BALA;
                collBoxShot.y = shot1.y - SHOT_HEIGHT;

                for (int i = 0; i < FIL_INVADERS; i++)
                {
                    for (int j = 0; j < COL_INVADERS; j++)
                    {
                        if( invaders[i][j].invaderState  )
                        {
                            collBoxShot_t invaderBox = {.x = invaders[i][j].x,
                                                        .y = invaders[i][j].y,
                                                        .height = al_get_bitmap_height(invaders[i][j].invadersPointer),
                                                        .width = al_get_bitmap_width(invaders[i][j].invadersPointer)};
                            if( isCollision( &invaderBox, &collBoxShot))
                            {
                                printf("COLISION!!!!!\n");
                                shot1.shotState = 0;
                                invaders[i][j].invaderState = 0;
                            }
                        }
                    }
                }

                //TODO: Chequear colision con escudos

                if( collBoxShot.y <= 0)
                {
                    shot1.shotState = 0;
                }
            }*/



            getCanonShotCollision();


            getInvaderShotCollison();
            
            drawAliveInvaders(invaders);
            al_draw_bitmap(image, cannonXpos, 450, 0); //flags(normalmente en cero, ver doc. para rotar etc)
            al_flip_display(); 
        }
    }

    al_shutdown_primitives_addon();
    al_destroy_display(display); //IMPORTANTE: Destruir recursor empleados
    al_destroy_bitmap(image);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
  
      //al_init es "destruido automaticamente" ver documentacion 

    for (int i = 0; i < FIL_INVADERS; i++) {
        for (int j = 0; j < COL_INVADERS; j++) {
            al_destroy_bitmap(invaders[i][j].invadersPointer);
        }
    }

    return 0;
}

int isCollision(collBoxShot_t* box1, collBoxShot_t* box2){

    if(box1->x < box2->x + box2->width &&
       box2->x < box1->x + box1->width &&
       box1->y < box2->y + box2->height &&
       box2->y < box1->y + box1->height)
       return 1;

    return 0;
}

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int initAll(void)
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

    image = al_load_bitmap("Laser_Cannon.png");
    if (!image) {
        fprintf(stderr, "failed to load image !\n");
        return -1;
    }

    for (int i = 0; i < FIL_INVADERS; i++)
    {
        for (int j = 0; j < COL_INVADERS; j++)                         //Cargo el bitmap a todas las invaders
        {
            invaders[i][j].invadersPointer = al_load_bitmap("Laser_Cannon.png");
            if (!invaders[i][j].invadersPointer) {
                fprintf(stderr, "failed to load image !\n");
                return -1;
            }

            //TODO: Switch case segun el tipo de invader
        }
    }

    display = al_create_display(D_WIDTH, D_HEIGHT); // Intenta crear display de 640x480 de fallar devuelve NULL
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source()); //REGISTRAMOS EL TECLADO

    placeInvaders( invaders );

    //void al_draw_bitmap(ALLEGRO_BITMAP *bitmap, float dx, float dy, int flags) 
    al_draw_bitmap(image, 0, 450, 0); //flags(normalmente en cero, ver doc. para rotar etc)

    al_flip_display(); //Flip del backbuffer, pasa a verse a la pantalla

    al_start_timer(timer); //Recien aca EMPIEZA el timer

    return 0;
}

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

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void placeInvaders(invader_t ptr_to_struct[FIL_INVADERS][COL_INVADERS])
{
    for (int i = 1; i <= FIL_INVADERS; i++)
    {
        for (int j = 1; j <= COL_INVADERS; j++)
        {
            int x_pos =  j * D_WIDTH/(COL_INVADERS + 1);
            int y_pos = i * al_get_bitmap_height( ptr_to_struct[i-1][j-1].invadersPointer ) + i*30;
            al_draw_bitmap( ptr_to_struct[i-1][j-1].invadersPointer, x_pos, y_pos, 0 );
            ptr_to_struct[i-1][j-1].x = x_pos;
            ptr_to_struct[i-1][j-1].y = y_pos;
            ptr_to_struct[i-1][j-1].invaderState = 1; //Ademas de colocar las naves, tambien les doy vida en el juego 
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
}

/*############################################
############################################*/

void getInvaderShotCollison(void)
{
    if(actualInvadersShots > 0)
    {

        collBoxShot_t canonBox = {  .x = cannonXpos ,
                                    .y = 450,           // TODO: Hacer una estructura o constante
                                    .height = al_get_bitmap_height(image),
                                    .width = al_get_bitmap_width(image)
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
                    printf("COOOOOLLL\n");
                }
                else if( invaderShotList[i].y > D_HEIGHT )
                {
                    invaderShotList[i].shotState = 0;
                    //actualInvadersShots++;
                    colisionDetected++;
                }
            }
            i++;
        }
        actualInvadersShots -= colisionDetected;
    }
}
/*
void canonShot(void)
{
    int ship_width = al_get_bitmap_width(image);
    int ship_height = al_get_bitmap_height(image);
    al_draw_line((ship_width + 2*cannonXpos)/2, POS_EN_Y_DEL_CANNON , (ship_width + 2*cannonXpos)/2, COLA_DE_DISPARO, al_color_name("white"), 0);

    shotCanon.x = (ship_width + 2*cannonXpos)/2;   
    shotCanon.y = POS_EN_Y_DEL_CANNON;
    shotCanon.type = INVADER_SHOT;                   
    shotCanon.shotState = 1;                       
}

void getCanonShotCollision(void)
{
            if(shotCanon.shotState)
            {
                al_draw_line(shotCanon.x, shotCanon.y , shotCanon.x,  shotCanon.y - 15, al_color_name("white"), 0);
                shotCanon.y -= TASA_DE_CAMBIO_BALA;

                collBoxShot_t collBoxShotFromCanon = {  .x = shotCanon.x - SHOT_WIDTH/2,
                                                        .y = shotCanon.y - SHOT_HEIGHT,
                                                        .width = SHOT_WIDTH,
                                                        .height = SHOT_HEIGHT
                                                     };

                for (int i = 0; i < FIL_INVADERS; i++)
                {
                    for (int j = 0; j < COL_INVADERS; j++)
                    {
                        if( invaders[i][j].invaderState  )
                        {
                            collBoxShot_t invaderBox = {.x = invaders[i][j].x,
                                                        .y = invaders[i][j].y,
                                                        .height = al_get_bitmap_height(invaders[i][j].invadersPointer),
                                                        .width = al_get_bitmap_width(invaders[i][j].invadersPointer)};
                            if( isCollision( &invaderBox, &collBoxShotFromCanon))
                            {
                                printf("COLISION!!!!!\n");
                                shotCanon.shotState = 0;
                                invaders[i][j].invaderState = 0;
                            }
                        }
                    }
                }

                //TODO: Chequear colision con escudos
                if( collBoxShotFromCanon.y <= 0)
                {
                    shotCanon.shotState = 0;
                }
            }
}
*/

void canonShot(void)
{   
    int ship_width = al_get_bitmap_width( image );
    int ship_height = al_get_bitmap_height( image );
    
    int x_shot = (ship_width + 2* cannonXpos  )/2;
    int y_shot = POS_EN_Y_DEL_CANNON;
    
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
                                    printf("ENTRO EL DISPARO\n");
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
}



