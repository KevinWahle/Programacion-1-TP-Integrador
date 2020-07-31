#include <stdio.h>


//###################                     ###################
//###################      DISPLAY        ###################
//###################                     ###################
/*
La librería que usaremos para la matriz de LEDs se llama disdrv. Ustedes cuentan con el
código objeto (disdrv.o) y con el header (disdrv.h).
 La matriz de LEDs es de 16 x 16. Es importante tener en cuenta que el origen (0,0) está el
extremo superior izquierdo.
 En el header están definidas algunas constantes de interés, como los valores máximo y
mínimo de las coordenadas x e y.
 En disdrv.h pueden ver que la librería proporciona cuatro funciones.
*/


/**
* @brief Sirve para inicializar el display.
* Debe ser llamada únicamente una vez antes de empezar a usarlo 
*/
void disp_init(void);


/**
* @brief Permite, al mismo tiempo, borrar todo el contenido del buffer y apagar todos los LEDS
* Nota: en el buffer se van almacenando los cambios hechos con disp_write(). 
*/
void disp_clear(void);


/**
* @brief Prende o apaga (según val) el LED indicado en coord.
* @param dcoord_t es una estructura que contiene las coordenadas x e y. 
* @param dlevel_t tiene dos valores posibles: D_OFF o D_ON, para apagado o prendido. 
* Nota:  disp_write() escribe en el buffer. Por lo tanto, las llamadas a disp_write() no se ven
automáticamente en el display. Para eso debemos usar disp_update().
 Ejemplo:
dcoord_t myPoint = {1,5};
disp_write(myPoint, D_ON); 
*/
void disp_write(dcoord_t coord, dlevel_t val);


/**
* @brief Actualiza el display con el contenido del buffer. 
* Nota: Notemos que con múltiples llamadas a disp_write() podemos modificar muchos LEDS y
* luego mostrar el resultado con una llamada a disp_update().
*/
void disp_update(void);



//###################                     ###################
//###################      JOYSTICK       ###################
//###################                     ###################

/*
El joystick se puede mover en el plano XY. Las coordenadas toman valores entre
JOY_MAX_NEG (-127) y JOY_MAX_POS (128), constantes útiles y definidas en el header.
Además, tiene un interruptor (switch), que se activa al presionarlo.
*/


/**
* @brief Sirve para inicializar el joystick. 
* Nota: Por lo tanto, debe llamarse únicamente una vez antes de empezar a usarlo.
*/
void joy_init(void);


/**
* @brief  Cuando se llama se miden las coordenadas del joystick en ese momento. 
* Nota: Luego podemos obtener esas coordenadas usando joy_get_coord() o joy_get_switch().
*/
void joy_update(void);


/**
* @brief Devuelve las coordenadas del joystick medidas en la última llamada a joy_update(). 
* Nota: La estructura jcoord_t contiene las coordenadas x e y para el joystick. No confundir con el
* tipo de datos dcoord_t que se usa para las coordenadas en el display.
*/
jcoord_t joy_get_coord(void);

/**
* @brief Devuelve el estado del switch medido en la última llamada a joy_update().  
* Nota: jswitch_t tiene dos valores posibles: J_NOPRESS o J_PRESS. 
*/
jswitch_t joy_get_switch(void);


//###################                     ###################
//###################      AUDIO          ###################
//###################                     ###################
/*
 La librería que usamos para el audio se llama libaudio. Ustedes cuentan con el código
objeto (libaudio.o) y el header (libaudio.h).
 Permite reproducir audio de forma no bloqueante. Los archivos deben ser .wav.
 En libaudio.h pueden ver que la librería proporciona seis funciones.
*/

/**
* @brief Inicializa la librería. Por lo tanto, debe llamarse una sola vez al principio.
*/
int init_sound(void);


/**
* @brief Abre el archivo a reproducir indicado por music_path (no lo reproduce).
* Nota: Recordemos que el formato de audio debe ser .wav.
* formato de audio: WAV (Microsoft) signed 16 bit PCM
*/
int set_file_to_play(const char *music_path);

/**
* @brief Inicia la reproducción del archivo de audio. Como ya dijimos, no es bloqueante.
*/
int play_sound(void);


/**
* @brief Pausa la reproducción del archivo de audio
*/
int pause_sound(void);


/**
* @brief Se detiene la reproducción del archivo de audio y se cierra el mismo.
* Se usa para terminar la reproducción.
*/
int stop_sound(void);

/**
* @brief Devuelve el estado del sistema. Hay seis estados posibles:
* NO_INIT: sistema no inicializado, es decir, no se invocó init_sound().
* READY: sistema inicializado, listo para usar.
* STOPPED: archivo de audio listo para ser reproducido.
* PLAYING: reproduciendo audio.
* PAUSED: reproducción pausada.
* FINISHED: el archivo terminó de ser reproducido.
*/
int player_status(void);

/*
##################### Extra: control de volumen                                                   #####################
#####################  El volumen del audio se puede modificar mediante consola, entre 0% y 90%. #####################
#####################  Ejemplo:                                                                  #####################
##################### amixer sset PCM,0 90%                                                       #####################
*/