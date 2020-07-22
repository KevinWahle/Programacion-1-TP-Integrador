/***************************************************************************/ /**
  @file     +main.c+
  @brief    +Archivo principal+
  @author   +Grupo 3+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "PORTS.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum BLINK_STATE { NO_BLINK, BLINK_OFF, BLINK_ON };     // Estado del blink

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define D_WIDTH 720
#define D_HEIGHT 480
#define LED_RAD 30.0
#define BLINK_TIME 0.5
#define CANT_LEDS   8

#define POW(x) ((x)*(x)) //macro para calcular cuadrados

#define LED_OFF_COLOR "darkred"
#define LED_ON_COLOR "red"
#define LED_BORDER_COLOR "black"
#define PORT 'A'

#define LOAD_IMAGE  "load_image.jpg"
#define BKGD_IMAGE  "bkgd_image.png"
#define END_IMAGE   "end_image.jpg"

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Mensaje de bienvenida e instrucciones.
*/
static void welcome();

/**
 * @brief Inicializa los recursos a emplear.
 * @return Si hubo o no error.
*/
static int init_all();

/**
 * @brief Muestra imagen de carga.
*/
static void cargando_ando();

/**
 * @brief drawLEDS: Refresca la pantalla con el estado actual de los LED'S.
 * @param ledState[] Arreglo con el estado del los LED's (0 apagado, 1 encendido)
 * @param nLeds Cantidad de LED's
*/
static void drawLEDS(bool ledState[], unsigned int nLeds);

/**
 * @brief Genera un arreglo de 8 bools, dependiendo del puerto pedido.
 * @param port El nombre del puerto a mostrar ('A', 'B' o 'D').
 * @param pointer Puntero al inicio del arreglo donde se guarda el estado de cada bit.
 * @param bits Cantidad de bits.
*/
static void gen_bool(char port, bool *pointer, int bits);

/**
 * @brief Imprime el estado de todos los bits del puerto dado.
 * @param port El nombre del puerto a mostrar ('A', 'B' o 'D').
 * @param port El nombre del puerto a mostrar ('A', 'B' o 'D').
*/
static void estadoBits(char port, bool *ledState);

/**
 * @brief Destruye los recursos empleados.
 **/
static void destroy_all();

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static ALLEGRO_TIMER *timer = NULL;
static ALLEGRO_BITMAP *loadImage = NULL;
static ALLEGRO_BITMAP *bkgdImage = NULL;
static ALLEGRO_BITMAP *endImage = NULL;
static ALLEGRO_DISPLAY *display = NULL;
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
int main(void)
{
    // Inicializacion de Allegro
    if (init_all())
    {
        return -1;
    }

    welcome();      // Instrucciones de uso

    cargando_ando();    // Loading...

    bool redraw = true;     // Para que se muestre la primera vez
    bool do_exit = false;
    bool ledState[CANT_LEDS];
    uint8_t blink = NO_BLINK;
    uint8_t blinkMask = 0x00;

    while (!do_exit)
    {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)     // Presiona cerrar
            {
                do_exit = true;
            }
            else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch (ev.keyboard.keycode)
                {
                case ALLEGRO_KEY_S:
                    maskOn(PORT, 0xFF);     // Enciendo todos los LED's
                    redraw = true;
                    break;

                case ALLEGRO_KEY_C:
                    maskOff(PORT, 0xFF);    // Apago todos los LED's
                    blinkMask = 0x00;
                    redraw = true;
                    break;

                case ALLEGRO_KEY_T:
                    if (blink == NO_BLINK)
                    {
                        maskToggle(PORT, 0xFF); // Invierto todos los leds
                    }
                    else 
                    {
                        maskOff(PORT, 0xFF);    // Apago todos los bits
                        blinkMask = ~blinkMask; // Para blinkearlos despues 
                    }
                    redraw = true;
                    break;

                case ALLEGRO_KEY_B: // Se apretó b, comienza a blinkear
                    
                    if (blink == NO_BLINK)  // Blink apagado? lo enciendo
                    {
                        blink = BLINK_ON;
                        blinkMask = portGet(PORT, CANT_LEDS); // Guardo estado actual como máscara
                        maskOff(PORT, blinkMask);
                        al_start_timer(timer); // Comienza a correr el timer
                    }
                    else
                    {
                        blink = NO_BLINK;
                        al_stop_timer(timer);       // Frena el timer
                        maskOn(PORT, blinkMask);    // Enciendo los que estaban blinkeando
                    }
                    redraw = true;
                    break;

                case ALLEGRO_KEY_0:
                case ALLEGRO_KEY_PAD_0: // Enciendo el led 0
                    bitSet(PORT, 0);
                    redraw = true;
                    break;

                case ALLEGRO_KEY_1:
                case ALLEGRO_KEY_PAD_1: // Enciendo el led 1
                    bitSet(PORT, 1);
                    redraw = true;
                    break;

                case ALLEGRO_KEY_2:
                case ALLEGRO_KEY_PAD_2: // Enciendo el led 2
                    bitSet(PORT, 2);
                    redraw = true;
                    break;

                case ALLEGRO_KEY_3:
                case ALLEGRO_KEY_PAD_3: // Enciendo el led 3
                    bitSet(PORT, 3);
                    redraw = true;
                    break;

                case ALLEGRO_KEY_4:
                case ALLEGRO_KEY_PAD_4: // Enciendo el led 4
                    bitSet(PORT, 4);
                    redraw = true;
                    break;

                case ALLEGRO_KEY_5:
                case ALLEGRO_KEY_PAD_5: // Enciendo el led 5
                    bitSet(PORT, 5);
                    redraw = true;
                    break;

                case ALLEGRO_KEY_6:
                case ALLEGRO_KEY_PAD_6: // Enciendo el led 6
                    bitSet(PORT, 6);
                    redraw = true;
                    break;

                case ALLEGRO_KEY_7:
                case ALLEGRO_KEY_PAD_7:
                    bitSet(PORT, 7); // Enciendo el led 7
                    redraw = true;
                    break;

                case ALLEGRO_KEY_Q:
                    do_exit = true; // Salgo del programa
                    break;
                }
            }
            else if (ev.type == ALLEGRO_EVENT_TIMER && blink != NO_BLINK)   // Timer de blink
            {
                blinkMask |= portGet('A', CANT_LEDS);       // Agrego al blink los leds encendidos
                if (blink==BLINK_ON)
                {
                    maskOn(PORT, blinkMask); 
                    blink = BLINK_OFF;
                }
                else if (blink==BLINK_OFF) 
                {
                    maskOff(PORT, blinkMask); 
                    blink = BLINK_ON;
                }
                redraw = true;
            }
            else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)      // Click del mouse
            {
                for (int i = 1; i <= CANT_LEDS; i++) // Se va fijando si el punto donde se clickeo, pertence al circulo. 
                {                                    // || (X.mouse, Y.mouse) - (X_centro, Y_centro) || <= LED_RAD    ~.~.~ La norma es menor o igual que el radio
                    if( ( POW( ev.mouse.x - (D_WIDTH / (CANT_LEDS+1.0))*i ) + POW(ev.mouse.y - D_HEIGHT/2.0) ) <= POW(LED_RAD) )
                    {
                            if (blink == NO_BLINK) {            // if not blinking
                                bitToggle(PORT, CANT_LEDS-i);   // Toogle LED
                            }
                            else {                              // if blinking
                                bitClr(PORT, CANT_LEDS-i);          // Turn Off and
                                blinkMask ^= 1 << (CANT_LEDS-i);    // Toogle blinkMask  
                            }
                            redraw = true;
                            break;  // Solo puede tocar un LED a la vez
                    }
                }
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            estadoBits(PORT, ledState);
        }
    }
    destroy_all();
    return 0;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/**
 * @brief Mensaje de bienvenida e instrucciones.
*/
void welcome() {
    printf("*****************************************************************************************\n");
    printf("*\t\t\t\t\tBienvenid@!!\t\t\t\t\t*\n");
    printf("* Antes de utilizar el simulador de LED's hay algunas cosas que debe tener en cuenta:\t*\n");
    printf("*\t- Puede pulsar los números del 0 al 7 para prender un LED\t\t\t*\n");
    printf("*\t- Puede hacer click sobre un LED para cambiar su estado\t\t\t\t*\n");
    printf("*\t- Puede pulsar S para encender todos los LED's\t\t\t\t\t*\n");
    printf("*\t- Puede pulsar C para apagar todos los LED's\t\t\t\t\t*\n");
    printf("*\t- Puede pulsar T para cambiar el estado de todos los LED's\t\t\t*\n");
    printf("*\t- Puede pulsar B para entrar o salir del \"modo blink\"\t\t\t\t*\n");
    printf("*\t\t- Si el modo blink está activado, los LED's encendidos comenzarán a\t*\n");
    printf("*\t\tparpadear. Apagar o encender LED's en modo blink hará que parpadeen o\t*\n");
    printf("*\t\tdejen de parpadear. Puede utilizar cualquiera de los comando anteriores\t*\n");
    printf("*\t\tdurante el modo blink. Al salir del modo blink, se encenderán los LED's\t*\n");
    printf("*\t\tque estaban parpadeando.\t\t\t\t\t\t*\n");
    printf("*****************************************************************************************\n");
}

/**
 * @brief Inicializa los recursos a emplear.
 * @return Si hubo o no error.
*/
static int init_all()       // Inicializo y verifico que no falle
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

/**
 * @brief Muestra imagen de carga.
*/
static void cargando_ando()
{
    srand(time(NULL));
    al_draw_scaled_bitmap(loadImage,
                          0, 0, al_get_bitmap_width(loadImage), al_get_bitmap_height(loadImage),    // Imagen de inicio
                          0, 0, al_get_display_width(display), al_get_display_height(display),      // Con que tamaño queres que se dibuje la imagen
                          0);
    al_flip_display();
    al_rest(((rand()%200)/100.0) + 2); // Tiempo de carga random (2-4 seg)
    
    al_draw_scaled_bitmap(bkgdImage,    // Imagen de fondo de los LED's
                          0, 0, al_get_bitmap_width(bkgdImage), al_get_bitmap_height(bkgdImage),    // Imagen de fondo
                          0, 0, al_get_display_width(display), al_get_display_height(display),      // Con que tamaño queres que se dibuje la imagen
                          0);
    al_flip_display();
}

/**
 * @brief drawLEDS: Refresca la pantalla con el estado actual de los LED'S.
 * @param ledState[] Arreglo con el estado del los LED's (0 apagado, 1 encendido)
 * @param nLeds Cantidad de LED's
*/
static void drawLEDS(bool ledState[], unsigned int nLeds)
{
    for (unsigned int n = 1; n <= nLeds; n++)
    {
        ALLEGRO_COLOR color = al_color_name(ledState[nLeds - n] ? LED_ON_COLOR : LED_OFF_COLOR);
        al_draw_filled_circle((D_WIDTH / (CANT_LEDS + 1.0)) * n, D_HEIGHT / 2.0, LED_RAD, color);
        al_draw_circle((D_WIDTH / (CANT_LEDS + 1.0)) * n, D_HEIGHT / 2.0, LED_RAD, al_color_name(LED_BORDER_COLOR), 3.0);
    }
    al_flip_display(); // Actualizamos la pantalla
}

/**
 * @brief Genera un arreglo de 8 bools, dependiendo del puerto pedido.
 * @param port El nombre del puerto a mostrar ('A', 'B' o 'D').
 * @param pointer Puntero al inicio del arreglo donde se guarda el estado de cada bit.
 * @param bits Cantidad de bits.
*/
static void gen_bool(char port, bool *pointer, int bits)
{
    for (int i = 0; i < bits; i++)
    {
        pointer[i] = bitGet(port, i);
    }
}

/**
 * @brief Muestra el estado de todos los bits del puerto dado.
 * @param port El nombre del puerto a mostrar ('A', 'B' o 'D').
 * @param *ledState 
*/
static void estadoBits(char port, bool *ledState)
{
    int bits = 0;
    gen_bool(port, ledState, CANT_LEDS);    // Actualizo el estado de los LED's
    switch (port)
    {
    case 'A':                       // Si se quiere modificar el puerto A
        bits = 8;
        drawLEDS(ledState, bits);
        break;

    case 'B':                       // Si se quiere modificar el puerto B
        bits = 8;
        drawLEDS(ledState, bits);
        break;

    case 'D':                       // Si se quiere modificar el puerto D
        bits = 16;
        drawLEDS(ledState, bits);
        break;

    default:                        // Si no se ingresó un puerto válido
        printf("Error, puerto inválido");
        break;
    }
}

/**
 * @brief Destruye los recursos empleados.
 **/
static void destroy_all()
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