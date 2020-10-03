//####################                            #####################
//#################### COPIADO DEL GIT DEL PIBE   #####################
//####################                            #####################
#ifndef disdrv_h
#define disdrv_h

#include <stdint.h>

typedef enum {NORMAL ,ROTATE} daxis_t;

typedef enum {D_OFF, D_ON} dlevel_t;

#define MAX_X		    	15
#define MAX_Y		    	15
#define MIN_X		    	0
#define MIN_Y		    	0


typedef struct {
	uint8_t x;
	uint8_t y;
} dcoord_t;


#define set_coord(x,y) (dcoord_t){x,y}


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

//ESTA FUNCION NO NOS LA NOMBRARON EN EL PDF:
//void set_display_axis(uint8_t orientation);

#endif // End of driver definitions