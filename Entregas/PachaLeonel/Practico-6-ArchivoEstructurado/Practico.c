/**************************************************************\
 Autor: Leonel Pacha
 Practico: 6
 Objetivo: Leer un archivo estructurado con formato MARC21 o ISO2709
 Fecha: 06/06/2020
\**************************************************************/

// Este ejercicio lo hicimos en conjunto con ELIANA CANO

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100000

void procesarRegistro (char *registro, int tamanioRegis);

int main () {

    int filedesc, tamanioRegis, cantRegis = 0;
    char buffer [MAX], registro [MAX], largo [6];

    filedesc = open ("osbooks2.iso2709.txt", O_RDONLY);

    if (filedesc < 0) {
        printf("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    while ( read (filedesc, largo, 5) ) {   // Leo 5 bytes (primeros del registro) 

        cantRegis++;    // Sumo un registro más (puede haber 1 o más registros)
        tamanioRegis = atoi(largo);     // Veo el largo del registro para luego leerlo completo

        printf ("Registro número: %d, con un tamaño de %d caracteres\n", cantRegis, tamanioRegis);

        strcpy (registro, largo);       // Copio los primeros 5 bytes que habia leido del registro

        read (filedesc, buffer, tamanioRegis - 5);      // Leo todo lo que falta del registro de una sola vez, menos los 5 bytes que ya leí

        strcat (registro, buffer);      // Concateno lo que leí al registro

        procesarRegistro (registro, tamanioRegis);      // Llamo a la funcion para decodificar el registro leido

    }

    close (filedesc);
    return 0;

}

void procesarRegistro (char *registro, int tamanioRegis) {

    char cabecera [25], directorio [MAX], datosBase [6], aux [MAX], directorioAux [MAX];
    int datoBase, cantTags;
    int tag [3], largoTag [4], ubicacTag [5];

    strncpy (cabecera, registro, 24);
    cabecera [25] = '\0';
    printf ("\nLa cabecera del registro es: %s\n", cabecera);

    strncpy (datosBase, registro + 12, 5);      // Cargo en datosBase 5 chars desde la posición 12 del registro, esto es para ver donde comienzan los datos
    datosBase [6] = '\0';
    printf ("Los datos base comienzan en: %s\n", datosBase);

    datoBase = atoi (datosBase);
    strncpy (directorio, registro + 24, datoBase - 25);
    directorio [datoBase - 24] = '\0';
    printf ("El directorio es: %s\n\n", directorio);

    cantTags = atoi(directorio) / 12;

    // Procedo a mostrar cada tag del directorio

    for (int i = 0; i < cantTags; i++){

        strncpy (directorioAux, directorio + (i * 12), 12);     //Copio las estructuras de los tags

        strncpy (aux, directorioAux, 3);
        tag [i] = atoi (aux);
        printf ("Tag: %d\n", tag[i]);

        strncpy (aux, directorioAux + 3, 4);
        largoTag [i] = atoi (aux);
        printf ("Largo del tag: %d\n", largoTag [i]);

        strncpy (aux, directorioAux + 7, 5);
        ubicacTag [i] = atoi (aux);
        printf ("La ubicación del tag es: %d\n", ubicacTag[i]);

    }

    for (int j = 0; j < cantTags; j++){

        strncpy (aux, registro + ubicacTag[j], largoTag[j]);





    }

    
}