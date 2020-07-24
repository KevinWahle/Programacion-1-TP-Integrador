

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
#define TASA_DE_CAMBIO_BALA 5

#define SHOT_HEIGHT 15
#define SHOT_WIDTH 4

#define COLA_DE_DISPARO (450 - SHOT_HEIGHT)
#define POS_EN_Y_DEL_CANNON 450

#define CANT_INVADERS 10
#define HEIGHT_INAVDERS_SEPARATION 15


#define CANT_D_POSIBLES_OBJETIVOS CANT_INVADERS // Solo tengo en cuenta disparo del cannon hacia los invaders no al reves.

#define CANT_D_ESCUDOS_POSIBLES 5 // falta para usar esto. No serian 5 habrian como 6 bloquecitos por cada bloque.

int initAll(void);

int isCollision(int x1,int y1,int h1,int w1,int x2,int y2,int h2,int w2);

enum MYKEYS {
    KEY_SPACE, KEY_DOWN, KEY_LEFT, KEY_RIGHT //arrow keys
};

typedef struct 
{
    int x;
    int y;
    int shotState;
}cannonShot_t;

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
}invader_t;

typedef int cannonPosition_t;


void placeInvaders(ALLEGRO_BITMAP **ptr_to_invaders, invader_t *ptr_to_struct);
void drawAliveInvaders(ALLEGRO_BITMAP **ptr_to_invaders, invader_t *ptr_to_struct);

int main(void) {
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_BITMAP *image = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL; 

    ALLEGRO_BITMAP *invadersPointer[CANT_INVADERS];

    bool redraw = false;
    bool display_close = false;

    bool key_pressed[4] = {false, false, false, false}; //Estado de teclas, true cuando esta apretada

    if(initAll())
        return -1;

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
        return 0;
    }


    for (int i = 0; i < CANT_INVADERS; i++)                         //Cargo el bitmap a cada puntero
    {
        invadersPointer[i] = al_load_bitmap("Laser_Cannon.png");
        if (!image) {
            fprintf(stderr, "failed to load image !\n");
            return 0;
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



    invader_t invaders[CANT_INVADERS];
    placeInvaders(invadersPointer, invaders );

    ALLEGRO_BITMAP* cuadrado = al_load_bitmap("Laser_Cannon.png");
    al_draw_bitmap(cuadrado, 100, 100, 0);

    //void al_draw_bitmap(ALLEGRO_BITMAP *bitmap, float dx, float dy, int flags) 
    al_draw_bitmap(image, 0, 450, 0); //flags(normalmente en cero, ver doc. para rotar etc)

    al_flip_display(); //Flip del backbuffer, pasa a verse a la pantalla


    al_start_timer(timer); //Recien aca EMPIEZA el timer


    //al_rest(5.0); ######################################################


    cannonPosition_t cannonXpos = 0;
    cannonShot_t shot1 = {0,0,0};
    collBoxShot_t collBoxShot = {0,0,0,0};

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
                    key_pressed[KEY_SPACE] = false;
                default:
                    break;
                }
            }
            
        }
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));
            if(key_pressed[KEY_SPACE] && !shot1.shotState) 
            {
                int ship_width = al_get_bitmap_width(image);
                int ship_height = al_get_bitmap_height(image);

                al_draw_line((ship_width + 2*cannonXpos)/2, POS_EN_Y_DEL_CANNON , (ship_width + 2*cannonXpos)/2, COLA_DE_DISPARO, al_color_name("white"), 0);

                shot1.shotState = 1;
                shot1.x = (ship_width + 2*cannonXpos)/2;
                shot1.y = 450;
                collBoxShot.x = shot1.x - SHOT_WIDTH/2;
                //collBoxShot.x = cannonXpos; ESTO ES RARO
                collBoxShot.y = shot1.y - SHOT_HEIGHT;
            }
            if(shot1.shotState)
            {
                al_draw_line(shot1.x, shot1.y , shot1.x,  shot1.y - 15, al_color_name("white"), 0);
                shot1.y -= TASA_DE_CAMBIO_BALA;
                collBoxShot.y = shot1.y - SHOT_HEIGHT;

                for (int i = 0; i < CANT_D_POSIBLES_OBJETIVOS; i++)
                {
                    if( (invaders[i]).invaderState  )
                    {
                        if( isCollision((invaders[i]).x, (invaders[i]).y,al_get_bitmap_height(invadersPointer[i]), al_get_bitmap_width(invadersPointer[i]), collBoxShot.x, collBoxShot.y, SHOT_HEIGHT, SHOT_WIDTH) )
                        {
                            printf("COLISION!!!!!\n");
                            shot1.shotState = 0;
                            (invaders[i]).invaderState = 0;
                        }
                    }
                }
                if( collBoxShot.y <= 0)
                {
                    shot1.shotState = 0;
                }
            }
            //al_draw_bitmap(cuadrado, 100, 100, 0);
            drawAliveInvaders(invadersPointer, invaders);
            al_draw_bitmap(image, cannonXpos, 450, 0); //flags(normalmente en cero, ver doc. para rotar etc)
            al_flip_display(); 
        }
    }

    al_shutdown_primitives_addon();
    al_destroy_display(display); //IMPORTANTE: Destruir recursor empleados
    al_destroy_bitmap(image);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_bitmap(cuadrado);
    //al_init es "destruido automaticamente" ver documentacion 

    for (int i = 0; i < CANT_INVADERS; i++)
    {
        al_destroy_bitmap(invadersPointer[i]);
    }

    return 0;
}

int isCollision(int x1,int y1,int h1,int w1,int x2,int y2,int h2,int w2){

    if(x1 < x2 + w2 &&
       x2 < x1 + w1 &&
       y1 < y2 + h2 &&
       y2 < y1 + h1)
       return 1;

    return 0;
}
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
    return 0;
}
void placeInvaders(ALLEGRO_BITMAP **ptr_to_invaders, invader_t *ptr_to_struct)
{
    int enesimoInvader = 0;
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= CANT_INVADERS/2; j++)
        {
            int x_pos =  j * D_WIDTH/(CANT_INVADERS/2 + 1);
            int y_pos = i * al_get_bitmap_height( ptr_to_invaders[j-1] ) + i*30;
            al_draw_bitmap( ptr_to_invaders[enesimoInvader], x_pos, y_pos,0 );
            (ptr_to_struct[enesimoInvader]).x = x_pos;
            (ptr_to_struct[enesimoInvader]).y = y_pos;
            (ptr_to_struct[enesimoInvader]).invaderState = 1; //Ademas de colocar las naves, tambien les doy vida en el juego 
            enesimoInvader++;
        }
    }
}

void drawAliveInvaders(ALLEGRO_BITMAP **ptr_to_invaders, invader_t *ptr_to_struct)
{
    int enesimoInvader = 0;

    for (int i = 0; i < CANT_INVADERS; i++)
    {
        if( (ptr_to_struct[enesimoInvader].invaderState) )
            al_draw_bitmap( ptr_to_invaders[enesimoInvader], ptr_to_struct[enesimoInvader].x, ptr_to_struct[enesimoInvader].y,0 );  //Dibujo solo los vivos
        enesimoInvader++;
    }

}