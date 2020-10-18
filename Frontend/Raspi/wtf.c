#include <stdio.h>

#include "timer/timer.h"

#define MAX_CANON_SHOT 1                // Es la mayor cantidad de disparos del canon que puede haber en el juego. Es decir la max cant. de balas visibles

#define FPS 60

typedef struct
{
    float x;              // su posicion
    float y;
    int shotState;       // si "existe" o no
} shot_t;

typedef struct 
{
    float y;
    float x;                                 // Cuidado la posicion es flotante. Para la la colision debe ser int, pero no pasa nada porque se castea
    // block_t blocks[CANON_BLOCKS];            // cuando dibuja tambien castea asi que no pasa nada
    // direction_t direction;
} canon_t;

void shoot_cannon(void);

static shot_t canonShotList[MAX_CANON_SHOT];



int main() {


    static own_timer_t myTimer;
    setTimer(&myTimer, 3);     // Aca declaro el timer y el tiempo
    
    startTimer(&myTimer);      // Recien aca empieza el timer

    while(1)
    {
        while(!checkTimer(&myTimer));
        shoot_cannon();
    }


}



void shoot_cannon(void)
{   
    // float x_shot = canon.blocks[0].x;      
    // float y_shot = canon.blocks[0].y - 1; 
    
    shot_t shot = { .x = 10,
                    .y = 10,
                    .shotState = 1
                  };
    int k = 0;    
    printf("WATAFAKK MAN ESTOY A PUNTO DE CHEQUIAR LA LISTA Y EL ESTADO DE LA BALA ES: %d  !!!\n", canonShotList[0].shotState );
    while( (canonShotList[k].shotState != 0) && (k < MAX_CANON_SHOT) ) 
    {
        k++;        // Busco un lugar en la lista (donde el disparo no este activo)
        printf("ENTRO AL WHILE!! k =%d\n", k);
    }
    if(k < MAX_CANON_SHOT) {       // Si hay lugar, creo la bala
        printf("Creo nuevo disparo en k=%d\n", k);
        printf("El estado antes de crear el disparo era %d:\n", canonShotList[k].shotState);
        canonShotList[k] = shot;
        // actualCanonShots++;
    }

}