#include <stdio.h>


//###################                     ###################
//###################      DISPLAY        ###################
//###################                     ###################
/*



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