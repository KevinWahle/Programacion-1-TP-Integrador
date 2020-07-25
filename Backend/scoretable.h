#define NAME    6 // Implica que cada nombre tiene que tener 5 letras como máximo

typedef struct          // Estructura que contiene al nombre del usuario con su correspondiente puntaje 
{
    char name[NAME];
    unsigned long int pts;
} SCORE;

void put_score (char* name, unsigned long int score, int top, SCORE* my_pun); //coloca los nombres y scores en un txt odenados
//name: string con el nombres
//score: puntaje asignado al nombre
//top: cantidad de puntjes a mostrar
//mypun: puntero a una posicion de memoria donde se almacenaran los datos del score

int lect_score (SCORE* my_pun); // Coloco en memoria los datos del score
//mypun: puntero a una posicion de memoria donde se almacenaran los datos del score
