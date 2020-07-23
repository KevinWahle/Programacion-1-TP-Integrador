/***************************************************************************/ /**
  @file     +resouces.c+
  @brief    +Archivo principal+
  @author   +Grupo 3+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

// +Incluir el header propio (ej: #include "template.h")+


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

// +ej: static int temperaturas_actuales[4];+


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
/**
 * @brief Inicializa los recursos a emplear.
 * @return Si hubo o no error.
*/
int init_all()       // Inicializo y verifico que no falle
{
    if (!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }

    timer = al_create_timer(BLINK_TIME); //crea el timer pero NO empieza a correr
    if (!timer)
    {
        al_shutdown_primitives_addon();
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    if (!al_init_image_addon())
    {
        al_shutdown_primitives_addon();
        al_destroy_timer(timer);
        fprintf(stderr, "failed to initialize image addon !\n");
        return -1;
    }

    loadImage = al_load_bitmap(LOAD_IMAGE);
    if (!loadImage)
    {
        al_shutdown_primitives_addon();
        al_destroy_timer(timer);
        al_shutdown_image_addon();
        fprintf(stderr, "failed to load loadImage !\n");
        return -1;
    }
    
    bkgdImage = al_load_bitmap(BKGD_IMAGE);
    if (!bkgdImage)
    {
        al_shutdown_primitives_addon();
        al_destroy_timer(timer);
        al_shutdown_image_addon();
        al_destroy_bitmap(loadImage);
        fprintf(stderr, "failed to load loadImage !\n");
        return -1;
    }

    endImage = al_load_bitmap(END_IMAGE);
    if (!endImage)
    {
        al_shutdown_primitives_addon();
        al_destroy_timer(timer);
        al_shutdown_image_addon();
        al_destroy_bitmap(loadImage);
        al_destroy_bitmap(bkgdImage);
        fprintf(stderr, "failed to load endImage !\n");
        return -1;
    }

    display = al_create_display(D_WIDTH, D_HEIGHT);
    if (!display)
    {
        al_shutdown_primitives_addon();
        al_destroy_timer(timer);
        al_shutdown_image_addon();
        al_destroy_bitmap(loadImage);
        al_destroy_bitmap(bkgdImage);
        al_destroy_bitmap(endImage);
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    event_queue = al_create_event_queue();
    if (!event_queue)
    {
        al_shutdown_primitives_addon();
        al_destroy_timer(timer);
        al_shutdown_image_addon();
        al_destroy_bitmap(loadImage);
        al_destroy_bitmap(bkgdImage);
        al_destroy_bitmap(endImage);
        al_destroy_display(display);
        fprintf(stderr, "failed to create event_queue!\n");
        return -1;
    }

    if (!al_install_keyboard())
    {
        al_shutdown_primitives_addon();
        al_destroy_timer(timer);
        al_shutdown_image_addon();
        al_destroy_bitmap(loadImage);
        al_destroy_bitmap(bkgdImage);
        al_destroy_bitmap(endImage);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }

    if (!al_install_mouse())
    {
        al_shutdown_primitives_addon();
        al_destroy_timer(timer);
        al_shutdown_image_addon();
        al_destroy_bitmap(loadImage);
        al_destroy_bitmap(bkgdImage);
        al_destroy_bitmap(endImage);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_uninstall_keyboard();
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }

    // Registro de eventos
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    return 0;
}


void destroy_all()
{
    al_draw_scaled_bitmap(endImage,     // Imagen de despedida
                          0, 0, al_get_bitmap_width(endImage), al_get_bitmap_height(endImage),     //imagen de finalizacion
                          0, 0, al_get_display_width(display), al_get_display_height(display), //a que tamaño queres que se dibuje la imagen
                          0);
    al_flip_display();
    al_rest(2.0); // Tiempo de duracion 
    // Destrucción de recursos empleados
    al_destroy_display(display);
    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_bitmap(loadImage);
    al_destroy_bitmap(bkgdImage);
    al_destroy_bitmap(endImage);
    al_uninstall_keyboard();
    al_uninstall_mouse();
    printf("See you next time...\n\n");
}
/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
