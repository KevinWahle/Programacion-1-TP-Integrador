/***************************************************************************/ /**
  @file     +resouces.c+
  @brief    +Archivo principal+
  @author   +Grupo 3+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "allhead.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define NUMOFFSET    48  //Offset de numero entero a char
#define MSCORE       5 //Cantidad maxima a imprimir de puntaje 

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Transforma un entero no signado a un string para luego imprimir.
 * @param num Recibe el numero a transformar.
 * @return Devulve el string ya transformado.
*/
static void intochar(int num, char chscore[MSCORE]);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static ALLEGRO_BITMAP *menuImage = NULL;
static ALLEGRO_BITMAP *firstImage = NULL;
static ALLEGRO_BITMAP *endImage = NULL;
static ALLEGRO_BITMAP *instImage = NULL;
static ALLEGRO_BITMAP *scoreImage = NULL;
static ALLEGRO_BITMAP *cannon = NULL;

static ALLEGRO_TIMER *timer = NULL;
static ALLEGRO_DISPLAY *display = NULL;
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;

static ALLEGRO_SAMPLE *sample1 = NULL;
static ALLEGRO_FONT * fontmu = NULL;
static ALLEGRO_FONT * fontsc = NULL;

// Invaders matrix
static invader_t invaders[FIL_INVADERS][COL_INVADERS];

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
                        if(al_init_ttf_addon()) { // initialize the ttf (True Type Font) addon)    
                            if (al_install_audio()) {               //INICIALIZACION
                                if (al_init_acodec_addon()) {       //      DE
                                    if (al_reserve_samples(1)) {    //     AUDIO
                                        display = al_create_display(D_WIDTH, D_HEIGHT);
                                        if (display) {
                                            if (al_install_keyboard()) {
                                                event_queue = al_create_event_queue();
                                                if (event_queue) {
                                                    al_register_event_source(event_queue, al_get_display_event_source(display));
                                                    al_register_event_source(event_queue, al_get_timer_event_source(timer));
                                                    al_register_event_source(event_queue, al_get_keyboard_event_source());
                                                    return true;
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
        fprintf(stderr, "ERROR: Failed to initialize allegro system\n");
	
    return false;
}


/**
 * @brief Carga la imagenes, fuentes y sonidos.
*/
int load_all()
{
    menuImage = al_load_bitmap("BMPs/menu-sp.bmp");
		if (menuImage) {
			firstImage = al_load_bitmap("BMPs/first-image.bmp");
            if (firstImage) {
                scoreImage = al_load_bitmap("BMPs/puntaje-sp.bmp");
                if (scoreImage) {   
                    instImage = al_load_bitmap("BMPs/instruction-sp.bmp");
                    if (instImage) {
                            endImage = al_load_bitmap("BMPs/bye-image.bmp");
                            if (endImage) {
                                cannon = al_load_bitmap("PNGs/Laser_Cannon.png");
                                if(cannon){
                                    fontmu = al_load_ttf_font("Fonts/SP-font-menu.ttf", 50, 0);
                                    if(fontmu){
                                        fontsc = al_load_ttf_font("Fonts/SP-font-menu.ttf", 20, 0);
                                        if(fontsc){
                                            sample1 = al_load_sample("Songs/audio.wav");
                                            if(sample1) {
                //////////////////////////////////////////////////////////////
                                                for (int i = 0; i < FIL_INVADERS; i++) {    //revisar como destruir todo esto 
                                                    for (int j = 0; j < COL_INVADERS; j++) {          //Cargo el bitmap a todas las invader
                                                        invaders[i][j].invadersPointer = al_load_bitmap("PNGs/Laser_Cannon.png");
                                                            if (!invaders[i][j].invadersPointer) {
                                                            fprintf(stderr, "ERROR: failed to load enemy image !\n");
                                                            al_destroy_sample(sample1);
                                                            return false;
                                                        }
                                                    }
                                                }
                                                return true; 
                ///////////////////////////////////////////////////////////////
                                        } else
                                            fprintf(stderr, "ERROR: Audio clip sample not loaded!\n");
                                        al_destroy_font(fontsc);
                                    } else 
                                        fprintf(stderr, "ERROR: Could not load score font!\n");
                                    al_destroy_font(fontmu);
                                } else 
                                    fprintf(stderr, "ERROR: Could not load menu font!\n");
                                al_destroy_bitmap(cannon);
                            } else
                                fprintf(stderr, "ERROR: failed to load cannon image!\n");
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


/**
 * @brief Muestra imagen de menu y coloca palabras que recibe y colorea la palabra que se indica.
*/
void show_menu (char* texto[], int size, int option)
{
    al_draw_scaled_bitmap(menuImage,    // Imagen de fondo del menu
                          0, 0, al_get_bitmap_width(menuImage), al_get_bitmap_height(menuImage),
                          0, 0, al_get_display_width(display), al_get_display_height(display),      // Con que tamaño queres que se dibuje la imagen
                          0);
    for(int i=0;i<size;i++) {
        al_draw_text(fontmu, al_map_rgb(255, 255, 255), (D_WIDTH / 2), 220+(i*80), ALLEGRO_ALIGN_CENTER, texto[i]);  //Imprime en pantalla todas las palabras
    }
    al_draw_text(fontmu, al_map_rgb(255, 165, 0), (D_WIDTH / 2), 220+(option*80), ALLEGRO_ALIGN_CENTER, texto[option]);
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
    al_draw_scaled_bitmap(scoreImage,    // Imagen de fondo puntaje
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
void shows_inst (void) 
{
    al_draw_scaled_bitmap(instImage,    // Imagen de instrucciones
                            0, 0, al_get_bitmap_width(instImage), al_get_bitmap_height(instImage),
                            0, 0, al_get_display_width(display), al_get_display_height(display),      // Con que tamaño queres que se dibuje la imagen
                            0);
    al_flip_display();
}


/**
 * @brief Destruye los recursos empleados.
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
    al_destroy_bitmap(menuImage);
    al_destroy_bitmap(firstImage);
    al_destroy_bitmap(endImage);
    al_destroy_bitmap(cannon);
    al_destroy_sample(sample1);
    al_destroy_font(fontmu);
    al_destroy_font(fontsc);

    al_destroy_timer(timer);
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

static void intochar(int num, char chscore[MSCORE])
{
    int a = 0;
    for(int i=MSCORE-1;i>=0;i--) {
        a = num % 10;
        chscore[i]=a+NUMOFFSET;
        num = num / 10;
    }
}