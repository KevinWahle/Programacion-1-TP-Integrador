/***************************************************************************/ /**
  @file     +resouces.c+
  @brief    +Archivo principal+
  @author   +Grupo 3+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "hallegro.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



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

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static ALLEGRO_TIMER *timer = NULL;
static ALLEGRO_BITMAP *menuImage = NULL;
static ALLEGRO_BITMAP *firstImage = NULL;
static ALLEGRO_BITMAP *endImage = NULL;
static ALLEGRO_BITMAP *cannon = NULL;
static ALLEGRO_DISPLAY *display = NULL;
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;
// Invaders matrix
static invader_t invaders[FIL_INVADERS][COL_INVADERS];

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
int init_all()       // Inicializo y verifico que no falle
{
    if (al_init()) {
        if (al_init_primitives_addon()) {
			timer = al_create_timer(1.0 / FPS); //crea el timer pero NO empieza a correr
			if (timer) {
				if (al_init_image_addon()) {
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
                            fprintf(stderr, "ERROR: Failed to install keyboard\n");
                        al_destroy_display(display);
                    } else
						fprintf(stderr, "ERROR: failed to create display!\n");
					al_shutdown_image_addon();     
				} else 
					fprintf(stderr, "ERROR: failed to initialize image addon !\n");
				al_destroy_timer(timer);
			} else
				fprintf(stderr, "ERROR: failed to create timer!\n");
			al_shutdown_primitives_addon();
		} else
			fprintf(stderr, "ERROR: Failed to load primitives addon \n");
        al_uninstall_system();
    } else
        fprintf(stderr, "ERROR: Failed to initialize allegro system\n");
	return false;
}

/**
 * @brief Carga la imagenes, fuentes y sonidos.
*/
int load_all()
{
    menuImage = al_load_bitmap("BMPs/menu1-sp.bmp");
		if (menuImage) {
			firstImage = al_load_bitmap("BMPs/first-image.bmp");
			if (firstImage) {
                endImage = al_load_bitmap("BMPs/bye-image.bmp");
			    if (endImage) {
                    cannon = al_load_bitmap("PNGs/Laser_Cannon.png");
                    if(cannon){
///////////////////////////////////////
                        for (int i = 0; i < FIL_INVADERS; i++) {    //revisar como destruir todo esto 
                            for (int j = 0; j < COL_INVADERS; j++) {          //Cargo el bitmap a todas las invader
                                invaders[i][j].invadersPointer = al_load_bitmap("Laser_Cannon.png");
                                    if (!invaders[i][j].invadersPointer) {
                                    fprintf(stderr, "ERROR: failed to load enemy image !\n");
                                    return -1;
                                }
                            }
                        }
//////////////////////////////////////
                        return true;     
                    } else
                      fprintf(stderr, "ERROR: failed to load cannon image !\n");
			        al_destroy_bitmap(endImage);   
                } else 
    			    fprintf(stderr, "ERROR: failed to load endImage !\n");
			    al_destroy_bitmap(firstImage);
			} else 
				fprintf(stderr, "ERROR: failed to load firstImage !\n");
			al_destroy_bitmap(menuImage);	
		} else 
    		fprintf(stderr, "ERROR: failed to load menuImage !\n");
    return false;
}

/**
 * @brief Muestra imagen de carga.
*/
void cargando_ando()
{
    srand(time(NULL));
    al_draw_scaled_bitmap(firstImage,    // Imagen de fondo de los LED's
                          0, 0, al_get_bitmap_width(firstImage), al_get_bitmap_height(firstImage),    // Imagen de fondo
                          0, 0, al_get_display_width(display), al_get_display_height(display),      // Con que tamaño queres que se dibuje la imagen
                          0);
    al_flip_display();
    al_rest(((rand()%200)/100.0) +1); // Tiempo de carga random (1-3 seg)
    
    al_draw_scaled_bitmap(menuImage,    // Imagen de fondo de los LED's
                          0, 0, al_get_bitmap_width(menuImage), al_get_bitmap_height(menuImage),    // Imagen de fondo
                          0, 0, al_get_display_width(display), al_get_display_height(display),      // Con que tamaño queres que se dibuje la imagen
                          0);
    al_flip_display();
}


/**
 * @brief Destruye los recursos empleados.
 **/
void destroy_all()
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

    al_uninstall_keyboard();
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_shutdown_image_addon();
    al_shutdown_primitives_addon();
    al_destroy_event_queue(event_queue);
    al_uninstall_system();
    printf("See you next time...\n\n");
}
/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
