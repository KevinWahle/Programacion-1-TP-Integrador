/***************************************************************************/ /**
  @file     +menu_front.c+
  @brief    +Archivo con recursos principales de allegro para menu y teclado+
  @author   +Grupo 3+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "headall.h"
#include "shared_res.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define NUMOFFSET   '0' //Offset de numero entero a char 

#define CANON_FILE  "Frontend/Allegro/PNGs/Laser_Cannon.png"

#define CRAB1_FILE   "Frontend/Allegro/PNGs/Crab1.png"
#define OCTO1_FILE   "Frontend/Allegro/PNGs/Octopus1.png"
#define SQUID1_FILE  "Frontend/Allegro/PNGs/Squid1.png"

#define CRAB2_FILE   "Frontend/Allegro/PNGs/Crab2.png"
#define OCTO2_FILE   "Frontend/Allegro/PNGs/Octopus2.png"
#define SQUID2_FILE  "Frontend/Allegro/PNGs/Squid2.png"

#define UFO_FILE    "Frontend/Allegro/PNGs/UFO.png"
#define ARROW_FILE  "Frontend/Allegro/PNGs/arrows.png"

#define ENGAME_FILE "Frontend/Allegro/BMPs/endgame-sp.bmp"
#define MENU_FILE   "Frontend/Allegro/BMPs/menu-sp.bmp"
#define FIRST_FILE  "Frontend/Allegro/BMPs/first-image.bmp"
#define SCORE_FILE  "Frontend/Allegro/BMPs/puntaje-sp.bmp"
#define INST_FILE   "Frontend/Allegro/BMPs/instruction-sp.bmp"
#define END_FILE    "Frontend/Allegro/BMPs/bye-image.bmp"

#define FONTMU_FILE "Frontend/Allegro/Fonts/SP-font-menu.ttf"
#define FONTSC_FILE "Frontend/Allegro/Fonts/SP-font-menu.ttf"

#define SAMPLE_FILE "Frontend/Allegro/Songs/audio.wav"

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

ALLEGRO_DISPLAY *display = NULL;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
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

static ALLEGRO_BITMAP *arrowpng = NULL;
static ALLEGRO_BITMAP *endgmImage = NULL;

static ALLEGRO_EVENT_QUEUE *event_queue = NULL;

static ALLEGRO_SAMPLE *sample1 = NULL;
static ALLEGRO_FONT * fontmu = NULL;

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
                                                    
                                                    timer_queue = al_create_event_queue();
                                                    if (timer_queue) {
                                                        al_register_event_source(timer_queue, al_get_timer_event_source(timer));
                                                        if (loadim_menu() == NO_ERROR){
                                                            return NO_ERROR;
                                                        } else 
                                                            fprintf(stderr, "ERROR: failed to add thing!\n");
                                                        al_destroy_event_queue(timer_queue);
                                                    } else
                                                        fprintf(stderr, "ERROR: failed to create timer_queue!\n");
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
    return ERROR;
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
                    endgmImage = al_load_bitmap(ENGAME_FILE);
                    if (endgmImage) {
                        arrowpng = al_load_bitmap(ARROW_FILE);
                        if(arrowpng){
                            endImage = al_load_bitmap(END_FILE);
                            if (endImage) {
                                fontmu = al_load_ttf_font(FONTMU_FILE, SIZE_FMU, 0);
                                if(fontmu){
                                    fontsc = al_load_ttf_font(FONTSC_FILE, SIZE_FSC, 0);
                                    if(fontsc){
                                        fontgm = al_load_ttf_font(FONTSC_FILE, SIZE_FGM, 0);
                                        if(fontgm){
                                            sample1 = al_load_sample(SAMPLE_FILE);
                                            if(sample1) {
                                                if (loadim_game()==NO_ERROR){
                                                    return NO_ERROR;
                                                } else 
                                                    fprintf(stderr, "ERROR: failed to add game images!\n");
                                                al_destroy_sample(sample1);
                                            } else
                                                fprintf(stderr, "ERROR: Audio clip sample not loaded!\n");
                                            al_destroy_font(fontgm);
                                        } else
                                            fprintf(stderr, "ERROR: Could not load game font!\n");
                                        al_destroy_font(fontsc);
                                    } else 
                                        fprintf(stderr, "ERROR: Could not load score font!\n");
                                    al_destroy_font(fontmu);
                                } else 
                                    fprintf(stderr, "ERROR: Could not load menu font!\n");  
                                al_destroy_bitmap(endImage);   
                            } else 
                                fprintf(stderr, "ERROR: failed to load endImage!\n");
                            al_destroy_bitmap(arrowpng);
                        } else
                            fprintf(stderr, "ERROR: failed to load arrow png!\n");
                        al_destroy_bitmap(endgmImage);
                    } else
                        fprintf(stderr, "ERROR: failed to load end game Image!\n");
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
    return ERROR;
}

/**
 * @brief Carga la imagenes para el juego.
*/
int loadim_game () 
{
    canonPointer = al_load_bitmap(CANON_FILE);
    if(canonPointer){
        UFO_invader.invadersPointer = al_load_bitmap(UFO_FILE);
        if (UFO_invader.invadersPointer) {
            squidPointer[0] = al_load_bitmap(SQUID1_FILE);
            if (squidPointer[0]) {
                squidPointer[1] = al_load_bitmap(SQUID2_FILE);
                if (squidPointer[1]) {
                    crabPointer[0] = al_load_bitmap(CRAB1_FILE);
                    if (crabPointer[0]) {
                        crabPointer[1] = al_load_bitmap(CRAB2_FILE);
                        if (crabPointer[1]) {
                            octoPointer[0] = al_load_bitmap(OCTO1_FILE);
                            if (octoPointer[0]) {
                                octoPointer[1] = al_load_bitmap(OCTO2_FILE);
                                if (octoPointer[1]) {
                                    return NO_ERROR;
                                }
                                else
                                    fprintf(stderr, "ERROR: failed to load Octo2 !\n");
                                al_destroy_bitmap(octoPointer[0]);
                            }
                            else
                                fprintf(stderr, "ERROR: failed to load Octo1 !\n");
                            al_destroy_bitmap(crabPointer[1]);
                        }
                        else
                            fprintf(stderr, "ERROR: failed to load Crab2 !\n");
                        al_destroy_bitmap(crabPointer[0]);
                    }
                    else
                        fprintf(stderr, "ERROR: failed to load Crab1 !\n");
                    al_destroy_bitmap(squidPointer[1]);
                }
                else
                    fprintf(stderr, "ERROR: failed to load Squid2 !\n");
                al_destroy_bitmap(squidPointer[0]);
            }
            else
                fprintf(stderr, "ERROR: failed to load Squid1 !\n");
            al_destroy_bitmap(UFO_invader.invadersPointer);
        } else
            fprintf(stderr, "ERROR: failed to load UFO !\n");
        al_destroy_bitmap(canonPointer);
    } else
        fprintf(stderr, "ERROR: failed to load canon !\n");
    return ERROR;
}


/**
 * @brief Muestra el splash.
*/
void splash_front() 
{
    al_draw_scaled_bitmap(firstImage,    // Imagen de bienvenida la juego
                            0, 0, al_get_bitmap_width(firstImage), al_get_bitmap_height(firstImage),
                            0, 0, D_WIDTH, D_HEIGHT,      // Con que tamaño queres que se dibuje la imagen
                            0);
    al_flip_display();
    al_rest(1.5);
    show_inst ();       // REVISAR: ACA DECIA shows_inst()
    al_draw_text(fontsc, al_map_rgb(255, 255, 255), (D_WIDTH / 2), 500, ALLEGRO_ALIGN_CENTER, "Presione la tecla espacio para continuar...");
    al_flip_display();
}


/**
 * @brief Muestra imagen de menu y coloca palabras que recibe y colorea la palabra que se indica.
*/
void show_menu (MENU_ITEM *menu_to_show, int size, int item)
{
    int altin;
    if (size==3) {
        altin = 240;
    } 
    else {
        altin = 220;
    }
    al_draw_scaled_bitmap(menuImage,    // Imagen de fondo del menu
                          0, 0, al_get_bitmap_width(menuImage), al_get_bitmap_height(menuImage),
                          0, 0, D_WIDTH, D_HEIGHT,      // Con que tamaño queres que se dibuje la imagen
                          0);
    for(int i=0;i<size;i++) {
        al_draw_text(fontmu, al_map_rgb(255, 255, 255), (D_WIDTH / 2), altin+(i*80), ALLEGRO_ALIGN_CENTER, menu_to_show[i].option);  //Imprime en pantalla todas las palabras
    }
}


/**
 * @brief Muestra los mejores puntajes, máximo 10.
*/
void show_score (SCORE* score ,int size) 
{  
    char chscore[LENG_SC]; //Variable temporal para convertir int a char
    unsigned long int num = 0; 
    char position[2] = "1";   //Variable que indica la posición
    al_draw_scaled_bitmap(scoreImage,    // Imagen de fondo de los puntajes
                             0, 0, al_get_bitmap_width(scoreImage), al_get_bitmap_height(scoreImage),
                             0, 0, D_WIDTH, D_HEIGHT,    
                             0);

    if (size>LEADERBOARD_SIZE) {
        size=LEADERBOARD_SIZE;
    }
    for(int i=0;i<size;i++) {
        position[0] = i+1+NUMOFFSET;  //Muestra el numero de la posicion del jugador  
        al_draw_text(fontsc, al_map_rgb(255, 255, 255), (D_WIDTH / 4)*1, 180+(i*40), ALLEGRO_ALIGN_CENTER, position);
        al_draw_text(fontsc, al_map_rgb(255, 255, 255), (D_WIDTH / 4)*2, 180+(i*40), ALLEGRO_ALIGN_CENTER, score[i].name);
        num=score[i].pts;
        intochar(num,chscore);
        al_draw_text(fontsc, al_map_rgb(255, 255, 255), (D_WIDTH / 4)*3, 180+(i*40), ALLEGRO_ALIGN_CENTER, chscore);
    }
    al_flip_display();
}


/**
 * @brief Muestra el puntaje al final de la partida y el ingreso del nombre.
*/
void score_name_front(char* actual_name, int size, int letter_counter, unsigned long int score) 
{
    char chscore[LENG_SC];
    al_draw_scaled_bitmap(endgmImage,    // Imagen de fondo de los puntajes
                            0, 0, al_get_bitmap_width(endgmImage), al_get_bitmap_height(endgmImage),   
                            0, 0, D_WIDTH, D_HEIGHT,      // Con que tamaño queres que se dibuje la imagen
                            0);
    al_draw_text(fontsc, al_map_rgb(255, 128, 0), (D_WIDTH / 2),(D_HEIGHT / 2)+200, ALLEGRO_ALIGN_CENTER, "Elija nombre para guardar puntaje");  
    char letter[2];
    for (int i=0; i<NAME_SIZE; i++){
        letter[0]=actual_name[i];
        letter[1]='\0';
        al_draw_text(fontmu, al_map_rgb(255, 255, 255), (D_WIDTH / 2)-(50*(2))+50*i, (D_HEIGHT / 2)+80, ALLEGRO_ALIGN_CENTER, letter);
    }
    letter[0]=actual_name[letter_counter];
    letter[1]='\0';
    al_draw_text(fontmu, al_map_rgb(255, 165, 0), (D_WIDTH / 2)-(50*(2))+50*letter_counter, (D_HEIGHT / 2)+80, ALLEGRO_ALIGN_CENTER, letter); //Imprime la legra a higligtear
    al_draw_bitmap(arrowpng,(D_WIDTH / 2)-(50*(2))+50*letter_counter-20, (D_HEIGHT / 2)+55, 0 );
    intochar(score,chscore);
    al_draw_text(fontmu, al_map_rgb(255, 255, 255), (D_WIDTH / 2), (D_HEIGHT / 2)-100, ALLEGRO_ALIGN_CENTER, "Puntaje final:");
    al_draw_text(fontmu, al_map_rgb(255, 255, 255), (D_WIDTH / 2)-40, (D_HEIGHT / 2)-40, ALLEGRO_ALIGN_CENTER, chscore);
    al_flip_display();
}


/**
 * @brief Muestra las instrucciones.
*/
void show_inst () 
{
    al_draw_scaled_bitmap(instImage,    // Imagen de instrucciones
                            0, 0, al_get_bitmap_width(instImage), al_get_bitmap_height(instImage),
                            0, 0, D_WIDTH, D_HEIGHT,      // Con que tamaño queres que se dibuje la imagen
                            0);
    al_draw_text(fontmu, al_map_rgb(255, 165, 0), (D_WIDTH / 2), altin+(item*80), ALLEGRO_ALIGN_CENTER, menu_to_show[item].option);
    al_flip_display();
}


/**
 * @brief Lee el teclado y carga el evento segun la libreria "event_queue.h".
 **/
void update_front_event (void)
{
    ALLEGRO_EVENT ev;
    if (al_get_next_event(event_queue, &ev))
    {
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)   // Eventos de display
        {
            add_event(EXIT_EVENT);
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN )  // Eventos de press
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                add_event(PAUSE_BTN);
                break;
            case ALLEGRO_KEY_P:             // P también para pausa
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
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)    // Eventos de release
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT:
                add_event(MOVE_LEFT_REL);
                break;
            case ALLEGRO_KEY_RIGHT:
                add_event(MOVE_RIGHT_REL);
                break;
            default:
                break;
            }
        }
    }
}


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
    al_rest(1); // Tiempo de duracion random
    // Destrucción de recursos empleados

    al_destroy_bitmap(canonPointer);    //Destruye la parte de loadim_game
    al_destroy_bitmap(octoPointer[0]);
    al_destroy_bitmap(octoPointer[1]);
    al_destroy_bitmap(crabPointer[0]);
    al_destroy_bitmap(crabPointer[1]);
    al_destroy_bitmap(squidPointer[0]);
    al_destroy_bitmap(squidPointer[1]);    
    al_destroy_bitmap(UFO_invader.invadersPointer); // Destruccion UFO

    al_destroy_bitmap(firstImage);
    al_destroy_bitmap(menuImage);   //Destruye la parte de loadim_menu
    al_destroy_bitmap(scoreImage);
    al_destroy_bitmap(instImage);
    al_destroy_bitmap(endgmImage);
    al_destroy_bitmap(endImage);

    al_destroy_sample(sample1);
    al_destroy_font(fontmu);
    al_destroy_font(fontsc);
    al_destroy_font(fontgm);

    al_destroy_timer(timer);        //Destruye la parte de inicialización
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_event_queue(timer_queue);

    al_uninstall_audio();
    al_uninstall_keyboard();

    al_shutdown_font_addon();
    al_shutdown_image_addon();
    al_shutdown_primitives_addon();
    
    fprintf(stderr, "See you next time...\n\n");
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
/**
 * @brief Transforma un entero no signado a un string.
 */
void intochar(unsigned long int num, char chscore[LENG_SC])
{
    unsigned long int a = 0;
    
    if(num==0){
        for(int i=0;i<LENG_SC-1;i++){
            chscore[i]=' ';
        }
        chscore[LENG_SC/2]='0';           // Escribo el 0 en el medio de la pantalla.
    }

    else{
        for(int i=LENG_SC-2;i>=0;i--) {
            a = num % 10;                   // Tomo un digito a mostrar.
            if(num>0) {
                chscore[i]=a+NUMOFFSET;     // Si sigo teniendo parte del numero disponible para mostrar
                                            //muestro el nuevo digito.
                num = num / 10;             // Recorto el número para mostrar el nuevo digito.    
            }
            else {
            chscore[i]=' ';              // Si el numero que queda es = a 0, muestro espacios.
            }
        }  
    }

    chscore[LENG_SC-1]='\0';          // Agrego el terminador
}