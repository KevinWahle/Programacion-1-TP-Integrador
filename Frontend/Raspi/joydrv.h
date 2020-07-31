//####################                            #####################
//#################### COPIADO DEL GIT DEL PIBE   #####################
//####################                            #####################
#ifndef joydrv_h
#define joydrv_h

#include <stdint.h>

typedef struct {
	int16_t x;
	int16_t y;
	
} jcoord_t;


typedef enum {J_NOPRESS ,J_PRESS} jswitch_t;
typedef enum {JOY_ROTATE,JOY_NORMAL} jaxis_t;

#define J_INV_FALSE  1			// Keep Default x and y axis Direction
#define J_INV_TRUE  -1			// Invert default x and y axis Direction

#define forever for(;;)

// Joystick Services

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
int joy_update(void);

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

/*
void set_joy_axis(uint8_t orientation);                  ???????????????????????????? NO LAS NOMBRA EL PORONGA EFE
void set_joy_direction(int8_t dir_x,int8_t dir_y);       ????????????????????????????
*/
#endif // End of driver definitions