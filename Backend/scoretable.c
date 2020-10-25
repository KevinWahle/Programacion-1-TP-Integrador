/***************************************************************************//**
  @file     +scoretable.c+
  @brief    +Modifica y lee el golbal score+
  @author   +Grupo 3+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdio.h>
#include "scoretable.h"    


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define OFFSET  '0'

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Ordena los elementos de mayor a menor
 * @param arr: arreglo  con los elementos a ordenar
 * @param cont: cantidad de elementos a ordenar
*/
void BubbleSort(SCORE arr[], int cont); 

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void put_score (char* name, unsigned long int score, const int top, SCORE* my_pun)
{
    FILE* fp;
    if (score!=0){
        fp = fopen ("score.txt","a+");                   // Abro el archivo con los puntajes
        fprintf (fp,"%s %lu\n", name, score);           // Le escribo el nombre y puntaje que fue provisto
        fclose(fp);   
    }                                               // Cierro el archivo
    int cant = lect_score (my_pun);                 // Cuento cuantos nombres hay y lo coloco en memoria
    
    if (cant<=top){                                 // Si la cantidad no supera el top   
        BubbleSort(my_pun, cant);                   // Lo agrego en el orden correspondiendte
        fp = fopen ("score.txt","w");                // Abro el archivo
        for (int i=0; i<cant; i++){
            fprintf(fp, "%s %lu\n", my_pun[i].name, my_pun[i].pts); // Le coloco los nombres y puntajes
        }
        fclose(fp);                                 // Cierro el archivo
    }
    else {
        BubbleSort(my_pun, top+1);                  // Agrego el nuevo punteje con el nombre correspondiente y lo ordeno 
        fp = fopen ("score.txt","w");                // Abro el archivo
        for (int i=0; i<top; i++){
            fprintf(fp, "%s %lu\n", my_pun[i].name, my_pun[i].pts); // Le coloco los nombres y puntajes
        }
                
        fclose(fp);                                 // Cierro el archivo
    }
	
}


int lect_score (SCORE* my_pun)
{
    printf ("entre a lect score\n");
    FILE* fp;
    char str[NAME_SIZE+1];       // Arreglo con el nombre
    SCORE score_data;           // Tipo de dato que almacena nombre y puntaje
    char c;                     // Caracter a leer
    unsigned long int num;      // Numero con el puntaje
    int cant =-1;               // Contador. Cuenta  la canitdad de puntajes que tiene el archivo
    fp=fopen ("score.txt","r"); // Abro el archivo
    printf ("hago el fopen\n");
    do
    {
        num=0;

        fgets(str, NAME_SIZE+1, fp);            //Leo el string con el nombre
   //   char temp=fgetc (fp);                   // Leo el espacio (basura)
        fgetc(fp);
        printf ("leo el nombre\n");

        while ( (c = fgetc(fp) ) != EOF && c!= '\n'){ // Mientras que no Lea un enter, o el archivo se termine
            num=num*10+(c-OFFSET);              // vamos conformando el numero con los caracteres
            printf("C: %d\n",c); 
        }
        printf ("leo hasta un enter\n");
        if (c!=EOF)
        {
            for (int j=0; j<=NAME_SIZE; j++){
                score_data.name[j]=str[j];          // Cargamos el nombre a la memoria
            }
            printf ("cargo el nombre en la memoria\n");
            score_data.pts=num;                     // Cargamos el puntaje a la memoria
            *my_pun=score_data;
            printf ("cargo el puntaje en la memoria\n");
            my_pun++;                               // Apuntamos al siguiente nombre y puntaje
        }
        cant++; 
                                 
    } while (c!=EOF);                            // Repetimos lo anterior hasta que hayamos leido todo el archivo
    printf ("salgo del while \n");
    fclose(fp);                                 // Cerramos el archivo
    printf ("hago el fclose\n"); 
    return cant;
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


void BubbleSort (SCORE arr[], int cont){
	SCORE temp;
	for (int j=0; j<cont-1; j++){               // Mientras que no supere la cantidad        
		for (int i=0; i<cont-1; i++){	
			if (arr[i].pts<arr[i+1].pts){       // Voy ordenando el arreglo de mayor a menor
				temp= arr[i];
				arr [i]=arr[i+1];
				arr[i+1]=temp;
			}
		}
	}
}