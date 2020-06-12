/**************************************************************\
 Autor: Eliana Cano
 Practico: 6
 Objetivo: Leer un archivo estructurado con formato MARC21 o ISO2709
 Fecha: 06/06/2020
\**************************************************************/

// Este ejercicio lo hicimos en conjunto con LEONEL PACHA 

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void procesarRegistro (char *registro, int largoRegistro);

int main(){

	int fd;
	char largoAux[6];
	int tamanio;
	char buffer [99999];
	char registro [ 99999 ];

	fd = open( "osbooks.iso2709", O_RDONLY );
    if ( fd == -1 ) {
        printf( "Error de lectura\n");
        exit(1);
    } 

    while ( read( fd, largoAux, 5 ) ) {

     tamanio = atoi( largoAux );   //determino el tamaño del directorio

        strcpy( registro, largoAux );  // registro = largoAux

        read( fd, buffer, tamanio - 5 ); // leo lo que me falta del directorio
       
        strcat( registro, buffer );       // tamaño de directorio + directorio
        
	    procesarRegistro ( registro, tamanio );

	return 0;
    }

}

void procesarRegistro ( char *registro, int largoRegistro ) {
    char cabecera[25], datosBase [6];
    char directorio[ 99999 ];
    int  tag[3], datoBase;
    int  ubicacion[99];
    int tamanio[99];
    char aux[999]; 
    int i = 0;

    strncpy ( cabecera, registro, 24 );
    cabecera[25] = '\0';
    printf ("\nLa cabecera del registro es: %s\n", cabecera);

    strncpy (datosBase, registro + 12, 5);      // Cargo en datosBase 5 chars desde la posición 12 del registro, esto es para ver donde comienzan los datos
    datosBase [6] = '\0';
    printf ("Los datos base comienzan en: %s\n", datosBase);
    
    datoBase = atoi (datosBase);
    strncpy (directorio, registro + 24, datoBase - 25);
    directorio [datoBase - 24] = '\0';
    printf ("El directorio es: %s\n\n", directorio);

    int nTag = strlen(directorio) / 12; //Divido por 12,porque cada tag tiene 12 de longitud

    printf("****************** %d \n", nTag);

    printf ("%d\n", datoBase);
    
    for(i = 0; i<nTag;i++){  //poner nTag en lugar de 2

    //printf("Entro al for \n");

    strncpy( directorio, registro + 24 + (i*12), 12 );  //voy buscando los datos de 12 en 12, porque
    //el directorio tiene longitud 12 para cada tag.

    aux [0] = ' ';
    aux [1] = ' ';
    aux [2] = ' ';
    aux [3] = ' ';
    aux [4] = ' ';
	
    strncpy( aux, directorio, 3 );  //guardo el tag, son los primeros 3 del directorio encontrado
    tag[i] = atoi(aux);
    printf("tag: %d \n", tag[i]);

    strncpy( aux, directorio + 3 , 4 ); //guardo el tamanio del dato, después del tag, los siguientes 4
    //me dicen el tamanio del dato.
    tamanio[i] = atoi(aux);
    printf( "tamaño: %d \n", tamanio[i]);

    strncpy( aux, directorio + 7 , 5 ); //guardo la ubicacion del dato, después del tag y del tamanio,
    //(3+4), está la ubicación/posición del dato
    ubicacion[i] = atoi(aux) + datoBase;  //donde de verdad empiezan los datos
    printf("ubicacion: %d \n", ubicacion[i]);
    }
    
    for(int j = 0; j < nTag; j++){

	strncpy( aux, registro + ubicacion[j] + 24 + strlen(directorio), tamanio[j] ); //busco el dato

    for(int p = 0;p<tamanio[j];p++) //imprimo el dato
	printf("%c",aux[p]);

    printf ("\n");


    }
}
