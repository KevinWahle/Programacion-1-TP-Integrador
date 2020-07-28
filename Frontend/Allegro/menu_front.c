/***************************************************************************/ /**
  @file     +menu_front.c+
  @brief    +Archivo con recursos principales de allegro para menu y teclado+
  @author   +Grupo 3+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "headall.h"
#include "../../const.h"
#include "../../Backend/scoretable.h" //Se necesita libreria para reconocer la estructura SCORE
#include "../../Backend/event_queue/event_queue.h" //Se necesita libreria para reconocer las funcion add_event

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define NUMOFFSET   '0' //Offset de numero entero a char
#define MSCORE       5  //Cantidad maxima a imprimir de puntaje 

#define CANON_FILE  "PNGs/Laser_Cannon.png"
#define CRAB_FILE   "PNGs/Crab1.png"
#define OCTO_FILE   "PNGs/Octopus1.png"
#define SQUID_FILE  "PNGs/Squid1.png"

#define MENU_FILE   "BMPs/menu-sp.bmp"
#define FIRST_FILE  "BMPs/first-image.bmp"
#define SCORE_FILE  "BMPs/puntaje-sp.bmp"
#define INST_FILE   "BMPs/instruction-sp.bmp"
#define END_FILE    "BMPs/bye-image.bmp"

#define FONT1_FILE  "Fonts/SP-font-menu.ttf"
#define FONT2_FILE  "Fonts/SP-font-menu.ttf"

#define SAMPLE_FILE "Songs/audio.wav"

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
ALLEGRO_BITMAP *cannon = NULL;
// Invaders matrix
invader_t invaders[FIL_INVADERS][COL_INVADERS];

const int invadersDistribution [FIL_INVADERS] = {
                                                OCTO,
                                                OCTO,
                                                SQUID,
                                                CRAB,
                                                CRAB,
                                                };

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Transforma un entero no signado a un string para luego imprimir.
 * @param num Recibe el numero a transformar.
 * @param chscore[] Recibe el string dode transformara el numero a char
 * @return Devulve el string ya transformado.
*/
static void intochar(int num, char chscore[MSCORE]);

/**
 * @brief Destruye todos los invaders cargados.
 */
static void destroy_invaders();

/**
 * @brief Carga la imagenes, fuentes y sonidos para el menu.
*/
int loadim_menu();

/**
 * @brief Carga la imagenes para el juego.
*/
int loadim_game();

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static ALLEGRO_BITMAP *menuImage = NULL;
static ALLEGRO_BITMAP *firstImage = NULL;
static ALLEGRO_BITMAP *endImage = NULL;
static ALLEGRO_BITMAP *instImage = NULL;
static ALLEGRO_BITMAP *scoreImage = NULL;

static ALLEGRO_TIMER *timer = NULL;
static ALLEGRO_DISPLAY *display = NULL;
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;
static ALLEGRO_EVENT_QUEUE *timer_event = NULL;

static ALLEGRO_SAMPLE *sample1 = NULL;
static ALLEGRO_FONT * fontmu = NULL;
static ALLEGRO_FONT * fontsc = NULL;

//static ALLEGRO_KEYBOARD_STATE ks;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
int init_front()       // Inicializo y verifico que no falle
{
    if (al_init()) {
        if (al_init_primitives_addon()) {
			timer = al_create_timer(1.0 / FPS); //crea el timer pero NO empieza a correr
			if (timer) {
				if (al_init_image_addon()) {    //Imagen
                    if (al_init_font_addon()) {     //Fuente
                        if(al_init_ttf_addon()) { // initialize the ttf (True Type Font) addon    
                            if (al_install_audio()) {               //INICIALIZACIÓN
                                if (al_init_acodec_addon()) {       //      DE
                                    if (al_reserve_samples(1)) {    //     AUDIO
                                        display = al_create_display(D_WIDTH, D_HEIGHT);
                                        if (display) {
                                            if (al_install_keyboard()) {
                                                event_queue = al_create_event_queue();
                                                if (event_queue) {
                                                    al_register_event_source(event_queue, al_get_display_event_source(display));
                                                    al_register_event_source(event_queue, al_get_keyboard_event_source());
                                                    
                                                    timer_event = al_create_event_queue();
                                                    if (timer_event) {
                                                        al_register_event_source(timer_event, al_get_timer_event_source(timer));
                                                        if (loadim_menu()){
                                                            return true;
                                                        } else 
                                                            fprintf(stderr, "ERROR: failed to add thing!\n");
                                                        al_destroy_event_queue(timer_event);
                                                    } else
                                                        fprintf(stderr, "ERROR: failed to create timer_event!\n");
                                                    al_destroy_event_queue(event_queue);
                                                } else
                                                    fprintf(stderr, "ERROR: failed to create event_queue!\n");
                                                al_uninstall_keyboard();
                                            } else
                                                fprintf(stderr, "ERROR: failed to install keyboard\n");
                                            al_destroy_display(display);
                                        } else
                                            fprintf(stderr, "ERROR: failed to create display!\n");
                                    } else 
                                        fprintf(stderr, "ERROR: failed to reserve samples!\n");
                                 } else 
                                    fprintf(stderr, "ERROR: failed to initialize audio codecs!\n");
                                al_uninstall_audio(); 
                            } else 
                                fprintf(stderr, "ERROR: failed to initialize audio!\n"); 
                        } else            
                            fprintf(stderr, "ERROR: failed to initialize TTF!\n");
                        al_shutdown_font_addon();
                    } else 
                        fprintf(stderr, "ERROR: failed to initialize fonts!\n");
                    al_shutdown_image_addon();
                } else 
					fprintf(stderr, "ERROR: failed to initialize image addon !\n");
				al_destroy_timer(timer);
			} else
				fprintf(stderr, "ERROR: failed to create timer!\n");
			al_shutdown_primitives_addon();
		} else
			fprintf(stderr, "ERROR: failed to load primitives addon \n");
    } else
        fprintf(stderr, "ERROR: failed to initialize allegro system\n");
    return false;
}


/**
 * @brief Carga la imagenes, fuentes y sonidos.
*/
int loadim_menu()
{
    menuImage = al_load_bitmap(MENU_FILE);
		if (menuImage) {
			firstImage = al_load_bitmap(FIRST_FILE);
            if (firstImage) {
                scoreImage = al_load_bitmap(SCORE_FILE);
                if (scoreImage) {   
                    instImage = al_load_bitmap(INST_FILE);
                    if (instImage) {
                        endImage = al_load_bitmap(END_FILE);
                        if (endImage) {
                            fontmu = al_load_ttf_font(FONT1_FILE, 50, 0);   //50 es el tamaño de la letra
                            if(fontmu){
                                fontsc = al_load_ttf_font(FONT2_FILE, 28, 0);   //28 es el tamaño de la letra
                                if(fontsc){
                                    sample1 = al_load_sample(SAMPLE_FILE);
                                    if(sample1) {
                                        if (loadim_game()){
                                            return true;
                                        } else 
                                            fprintf(stderr, "ERROR: failed to add game images!\n");
                                        al_destroy_sample(sample1);
                                    } else
                                        fprintf(stderr, "ERROR: Audio clip sample not loaded!\n");
                                    al_destroy_font(fontsc);
                                } else 
                                    fprintf(stderr, "ERROR: Could not load score font!\n");
                                al_destroy_font(fontmu);
                            } else 
                                fprintf(stderr, "ERROR: Could not load menu font!\n");  
                            al_destroy_bitmap(endImage);   
                        } else 
                            fprintf(stderr, "ERROR: failed to load endImage!\n");
                        al_destroy_bitmap(instImage);
                    } else 
                        fprintf(stderr, "ERROR: failed to load instImage!\n");
                    al_destroy_bitmap(scoreImage);
                } else 
                    fprintf(stderr, "ERROR: failed to load scoreImage!\n"); 
                al_destroy_bitmap(firstImage);
            } else 
                fprintf(stderr, "ERROR: failed to load firtsImage!\n");            
            al_destroy_bitmap(menuImage);	
        } else 
    		fprintf(stderr, "ERROR: failed to load menuImage!\n");
    return false;
}

int loadim_game () 
{
    cannon = al_load_bitmap(CANON_FILE);
    if(cannon){
        for (int i = 0; i < FIL_INVADERS; i++)
        {
            for (int j = 0; j < COL_INVADERS; j++)      //Cargo el bitmap a todas las invaders
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
                    fprintf(stderr, "failed to load invader image \"%s\"!\n", file);
                    destroy_invaders();
                    al_destroy_bitmap(cannon);
                    return false;
                }
            }
            return true;
        }
    } else
        fprintf(stderr, "ERROR: failed to load cannon image!\n");    
    return false;
}


/**
 * @brief Muestra el splash.
*/
void splash_front() 
{
    al_draw_scaled_bitmap(firstImage,    // Imagen de bienvenida la juego
                            0, 0, al_get_bitmap_width(firstImage), al_get_bitmap_height(firstImage),
                            0, 0, al_get_display_width(display), al_get_display_height(display),      // Con que tamaño queres que se dibuje la imagen
                            0);
    al_rest(1.5);
    shows_inst ();
    al_draw_text(fontsc, al_map_rgb(255, 255, 255), (D_WIDTH / 2), 500, ALLEGRO_ALIGN_CENTER, "Presione la tecla espacio para continuar...");
    al_flip_display();
}


/**
 * @brief Muestra imagen de menu y coloca palabras que recibe y colorea la palabra que se indica.
*/
void show_menu (MENU_ITEM *menu_to_show, int size, int item)
{
    al_draw_scaled_bitmap(menuImage,    // Imagen de fondo del menu
                          0, 0, al_get_bitmap_width(menuImage), al_get_bitmap_height(menuImage),
                          0, 0, al_get_display_width(display), al_get_display_height(display),      // Con que tamaño queres que se dibuje la imagen
                          0);
    for(int i=0;i<size;i++) {
        al_draw_text(fontmu, al_map_rgb(255, 255, 255), (D_WIDTH / 2), 220+(i*80), ALLEGRO_ALIGN_CENTER, texto[i].option);  //Imprime en pantalla todas las palabras
    }
    al_draw_text(fontmu, al_map_rgb(255, 165, 0), (D_WIDTH / 2), 220+(item*80), ALLEGRO_ALIGN_CENTER, texto[item].option);
    al_flip_display();
}


/**
 * @brief Muestra los mejores puntajes, máximo 10.
*/
void show_score (SCORE* score ,int size) 
{
    char chscore[MSCORE]; //Variable temporal para convertir int a char
    int num=0;
    char position[2];   //Variable que indica la posición
    position[1]=167; //Es el circulo arriba del número
    al_draw_scaled_bitmap(scoreImage,    // Imagen de fondo de los puntajes
                            0, 0, al_get_bitmap_width(scoreImage), al_get_bitmap_height(scoreImage),   
                            0, 0, al_get_display_width(display), al_get_display_height(display),      // Con que tamaño queres que se dibuje la imagen
                            0);
    al_flip_display();
    
    if (size>10)
        size=10;

    for(int i=0;i<size;i++) {
        position[0] = i+1+NUMOFFSET;    
        al_draw_text(fontsc, al_map_rgb(255, 255, 255), 50, 220+(i*40), ALLEGRO_ALIGN_CENTER, position);
        al_draw_text(fontsc, al_map_rgb(255, 255, 255), (D_WIDTH / 2), 220+(i*40), ALLEGRO_ALIGN_CENTER, score[i].name);
        num=score[i].pts;
        intochar(num,chscore);
        al_draw_text(fontsc, al_map_rgb(255, 255, 255), (D_WIDTH / 4)*3, 220+(i*40), ALLEGRO_ALIGN_CENTER, chscore);
    }

}


/**
 * @brief Muestra las instrucciones.
*/
void shows_inst () 
{
    al_draw_scaled_bitmap(instImage,    // Imagen de instrucciones
                            0, 0, al_get_bitmap_width(instImage), al_get_bitmap_height(instImage),
                            0, 0, al_get_display_width(display), al_get_display_height(display),      // Con que tamaño queres que se dibuje la imagen
                            0);
    al_flip_display();
}


/**
 * @brief Lee el teclado y carga el evento segun la libreria "event_queue.h".
 **/
void update_front_event ()  //VER SI DEJARLO ASI O HACERLO CON EVENTOS DE ALLEGRO "ALLEGRO_EVENT ev;"
{
    ALLEGRO_EVENT ev;

    if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
    {
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            add_event(EXIT_EVENT);  //No se si end game termina el juego o termina todo

        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN )
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                add_event(PAUSE_BTN);
                break;
            case ALLEGRO_KEY_SPACE:
                add_event(CLICK_BTN);
                break;
            case ALLEGRO_KEY_UP:
                add_event(MOVE_UP);
                break;
            case ALLEGRO_KEY_DOWN:
                add_event(MOVE_DOWN);
                break;
            case ALLEGRO_KEY_LEFT:
                add_event(MOVE_LEFT);
                break;
            case ALLEGRO_KEY_RIGHT:
                add_event(MOVE_RIGHT);
                break;
            default:
                break;
            }
        }
    }

    // Ver esto en lugar de al_get_next_event() (Devuelve evento sin sacar de la cola) 
    // bool al_peek_next_event(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT *ret_event)

    /*al_get_keyboard_state(&ks);

    if(al_key_down(&ks,ALLEGRO_KEY_ESCAPE)) {
        add_event(PAUSE_BTN);
    }
    else if(al_key_down(&ks,ALLEGRO_KEY_SPACE)) {
        add_event(CLICK_BTN);
    }
    else if(al_key_down(&ks,ALLEGRO_KEY_UP)) {
        add_event(MOVE_UP);
    }
    else if(al_key_down(&ks,ALLEGRO_KEY_DOWN)) {
        add_event(MOVE_DOWN);
    }
    else if(al_key_down(&ks,ALLEGRO_KEY_LEFT)) {
        add_event(MOVE_LEFT);
    }
    else if(al_key_down(&ks,ALLEGRO_KEY_RIGHT)) {
        add_event(MOVE_RIGHT);
    }*/
}


/**
 * @brief Redraw dependiendo del timer.
 **/
/*void redraw ()          //VER SI PONER EN GAME_FRONT
{
    ALLEGRO_EVENT ev1;
    if (al_get_next_event(timer_event, &ev1)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
    {
        if (ev1.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            
            getCanonShotCollision();

            shouldInvaderShot();

            getInvaderShotCollison();
            
            if( !is_invadersOnFloor()  )
                proxDir = moveInvaders(proxDir);

            placeShields();

            drawAliveInvaders(invaders);

            al_draw_bitmap(canonPointer, cannonXpos, D_HEIGHT - al_get_bitmap_height(canonPointer) , 0);
            al_flip_display();
        }
    }

}
*/


/**
 * @brief Destruye los recursos empleados por allegro.
 **/
void destroy_front()
{
    al_draw_scaled_bitmap(endImage,     // Imagen de despedida
                          0, 0, al_get_bitmap_width(endImage), al_get_bitmap_height(endImage),     //imagen de finalizacion
                          0, 0, al_get_display_width(display), al_get_display_height(display), //a que tamaño queres que se dibuje la imagen
                          0);
    al_flip_display();
    al_rest(2.0); // Tiempo de duracion random
    // Destrucción de recursos empleados

    destroy_invaders();         //Destruye la parte de loadim_game
    al_destroy_bitmap(cannon);

    al_destroy_bitmap(menuImage);   //Destruye la parte de loadim_menu
    al_destroy_bitmap(firstImage);
    al_destroy_bitmap(endImage);
    al_destroy_sample(sample1);
    al_destroy_font(fontmu);
    al_destroy_font(fontsc);

    al_destroy_timer(timer);        //Destruye la parte de inicialización
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    al_uninstall_audio();
    al_uninstall_keyboard();
    
    al_shutdown_font_addon();
    al_shutdown_image_addon();
    al_shutdown_primitives_addon();
    
    printf("See you next time...\n\n");
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
/**
 * @brief Transforma un entero no signado a un string.
 */
static void intochar(int num, char chscore[MSCORE])
{
    int a = 0;
    for(int i=MSCORE-1;i>=0;i--) {
        a = num % 10;
        chscore[i]=a+NUMOFFSET;
        num = num / 10;
    }
}


/**
 * @brief Destruye todos los invaders cargados.
 */
static void destroy_invaders() 
{
    for (int i = 0; i < FIL_INVADERS; i++) {
        for (int j = 0; j < COL_INVADERS; j++) {
            al_destroy_bitmap(invaders[i][j].invadersPointer);
        }
    }
}