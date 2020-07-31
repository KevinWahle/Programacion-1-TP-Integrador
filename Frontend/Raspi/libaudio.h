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