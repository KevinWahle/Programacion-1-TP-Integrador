#include <stdio.h>
#define NAME    6   // Implica que cada nombre tiene que tener 5 letras
#define OFFSET  '0'

void put_score (char* name, int score); //coloca los nombres y scores en un txt
//name: string con el nombres
//score: puntaje asignado al nombre

typedef struct          // Estructura que contiene al nombre del usuario con su correspondiente puntaje 
{
    char name[NAME];
    int pts;
} SCORE;

void lect_score (SCORE* mypun); // coloco en memoria los datos del score
//mypun: puntero a una posicion de memoria donde se almacenaran los datos del score

int main (void){
    SCORE arr[500];                     //ni lo comento porque esto es un main de prueba
    SCORE* pun=arr;
    put_score ("KEVIN", 200);
    put_score ("PERON", 999999);
    lect_score (pun);
    printf ("str: %s , num: %d", pun->name,pun->pts);
    printf ("str: %s , num: %d", (pun+4)->name,(pun+4)->pts);
   
}
void put_score (char* name, int score)
{
    FILE* fp;                           
    fp= fopen ("score.txt","a+");        // Abro el archivo correspondiente, pudiendolo escribir sin borrar lo anterior
    fprintf(fp, "%s %d\n", name, score); // Escribo el nombre con el score correspondiente en el archivo
    fclose(fp);                          // Cierro el archivo
}

void lect_score (SCORE* my_pun)
{
    FILE* fp;
    char str[NAME];             // Arreglo con el nombre
    SCORE score_data;           // Tipo de dato que almacena nombre y puntaje
    char c;                     // Caracter a leer
    int num;                    // Numero con el puntaje
    fp=fopen ("score.txt","r");

    do
    {
        num=0;
        fgets (str,NAME,fp);                    // Coloco el nombre en el Arreglo
        fgetc (fp);                             // Leo el espacio (basura)

        while ((c=fgetc (fp))!=EOF && c!='\n'){ // Mientras que no Lea un enter, o el archivo se termine
            num=num*10+(c-OFFSET);              // vamos conformando el numero con los caracteres
        }
        for (int i=0; i<NAME; i++){
            score_data.name[i]=str[i];          // Cargamos el nombre a la estructura
        }
        score_data.pts=num;                     // Cargamos el puntaje a la estructura
        *my_pun=score_data;
        my_pun++;                               // Apuntamos al siguiente nombre y puntaje
    }while (c!=EOF);                            // Repetimos lo anterior hasta que hayamos leido todo el archivo
    fclose(fp);                                 // Cerramos el archivo 
}