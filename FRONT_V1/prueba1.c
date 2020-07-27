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
#define TASA_DE_CAMBIO_INVADERS 1

#define SHOT_HEIGHT 15
#define SHOT_WIDTH 4

#define FIL_INVADERS 5
#define COL_INVADERS 9

// INVADERS POSITION
#define INVADERS_WIDTH_PERCENT  0.7    // Porcentaje de los invaders a lo ancho de la pantalla (0-1)
#define INVADERS_HEIGHT_PERCENT  0.4    // Porcentaje de los invaders a lo alto de la pantalla (0-1)
#define INVADERS_START_HEIGHT_PERCENT  0.05    // Porcentaje de la pantalla donde inician los invaders (desde arriba)

#define INVADERS_FLOOR D_HEIGHT*0.7         // Espacio desde el techo hasta "piso" de los invasores
#define INVADERS_WALL D_WIDTH*0.01          // Espacio entre el borde derecho e izquierdo en el que van a robotar los invaders
#define INVADERS_FALL D_HEIGHT*0.05         // Espacio de caida de los invaders al llegar a cada tope 

#define CANT_INVADERS FIL_INVADERS*COL_INVADERS

#define CANT_D_POSIBLES_OBJETIVOS CANT_INVADERS // Solo tengo en cuenta disparo del cannon hacia los invaders no al reves.

#define CANT_D_ESCUDOS_POSIBLES 4 // falta para usar esto. No serian 5 habrian como 6 bloquecitos por cada bloque.

#define MAX_INVADERS_SHOT 20

#define MAX_CANON_SHOT 3

#define CANON_FILE "PNGs/Laser_Cannon.png"
#define CRAB_FILE "PNGs/Crab1.png"
#define OCTO_FILE "PNGs/Octopus1.png"
#define SQUID_FILE "PNGs/Squid1.png"

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

enum INVADERS_TYPES {CRAB ,SQUID, OCTO};

enum DIRECTIONS {LEFT, RIGHT, ERROR_DIREC};

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
int invaderShot(int i, int j);

void getInvaderShotCollison(void);

void canonShot(void);

void getCanonShotCollision(void);

int moveInvaders(int direction);

void moveInvadersDown(void);

int is_invadersOnFloor(void);

void shouldInvaderShot(void);

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void placeInvaders(invader_t ptr_to_struct[FIL_INVADERS][COL_INVADERS]);
static void drawAliveInvaders(invader_t ptr_to_struct[FIL_INVADERS][COL_INVADERS]);
static int decideWhetherChangeDirectionOrNot(int direction);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static int initAll(void);

static shot_t invaderShotList[MAX_INVADERS_SHOT];
// Lista de los disparos de los invaders

static int isCollision( collBoxShot_t * box1, collBoxShot_t * box2);
static int actualInvadersShots; 
static int actualCanonShots;


/************ALLEGRO VARIABLES DEFINITION***************/
static ALLEGRO_DISPLAY * display = NULL;
static ALLEGRO_BITMAP *canonPointer = NULL;
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;
static ALLEGRO_TIMER *timer = NULL;

// El cañón
static cannonPosition_t cannonXpos = 0;

// Invaders matrix
static invader_t invaders[FIL_INVADERS][COL_INVADERS];


static shot_t canonShotList[MAX_CANON_SHOT];

static int proxDir = LEFT;


static const int invadersDistribution [FIL_INVADERS] = {
                                                        SQUID,
                                                        CRAB,
                                                        CRAB,
                                                        OCTO,
                                                        OCTO,
                                                       };

// static int CONTEOREAL;

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

            //if(  !(rand() % 60)  )
            //{
            //    invaderShot(FIL_INVADERS - 1 , rand()  % (COL_INVADERS )  );
            //
            //getInvaderShotCollison();
            
            getCanonShotCollision();

            shouldInvaderShot();
            getInvaderShotCollison();
            
            if( !is_invadersOnFloor()  )
                proxDir = moveInvaders(proxDir);

            drawAliveInvaders(invaders);
            al_draw_bitmap(canonPointer, cannonXpos, D_HEIGHT - al_get_bitmap_height(canonPointer) , 0); //flags(normalmente en cero, ver doc. para rotar etc)
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
    for (int i = 0; i < FIL_INVADERS; i++)
    {
        for (int j = 0; j < COL_INVADERS; j++)
        {
            int inv_width = al_get_bitmap_width(ptr_to_struct[i][j].invadersPointer);
            int inv_height = al_get_bitmap_height(ptr_to_struct[i][j].invadersPointer);
            int x_pos =  j * (D_WIDTH*INVADERS_WIDTH_PERCENT-inv_width)/(COL_INVADERS-1) + D_WIDTH*(1-INVADERS_WIDTH_PERCENT)/2 ;
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
    while( i >= 0 && !state )
    {
        int j = 0;
        while(   j < COL_INVADERS  && !invaders[i][j].invaderState  ) // Busca en la col, mientras esten muertos
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
        while( i >= 0  &&   !invaders[i][j].invaderState )  //mientras esten muertos los invaders
        {
            i--;
        }
        if( i >= 0)          // entonces se encotnro algun invader vivo
        {
            if(  !(rand() % 350) )
                invaderShot(i, j);
        }
    }       
}