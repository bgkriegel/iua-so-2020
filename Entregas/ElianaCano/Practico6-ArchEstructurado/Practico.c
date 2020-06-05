#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void obtenerDatos ( char *record, int record_length );

int main(){
	int fd;
	char lengthAux[6];
	int length;
	char buff[99999];
	char record[ 99999 ];

	 fd = open( "osbooks.iso2709", O_RDONLY );
    if ( fd == -1 ) {
        printf( "Error de lectura\n");
        exit(1);
    } 

    while ( read( fd, lengthAux, 5 ) ) {
 
        length = atoi( lengthAux );   //determino el tamaño del directorio
        strcpy( record, lengthAux );  // record = lengthAux
        read( fd, buff, length - 5 ); // leo lo que me falta del directorio
        strcat( record, buff );       // tamaño de directorio + directorio
        
	obtenerDatos ( record, length );

	printf("\n\n\n");
	return 0;
    }

}

    void obtenerDatos ( char *record, int record_length ) {
    char leader[25];
    char directory[ 99999 ];
    int  tag[3];
    int  ubicacion[99];
    int largo[99];
    char aux[999]; 
    int i = 0;

    strncpy ( leader, record, 24 );
    leader[25] = '\0';
    printf( "Leader: %s\n", leader );
    
    strcpy (directory, record + 24);
    int num = strlen(directory); //Divido por 12,porque cada tag tiene 12 de longitud

    printf("****************** %d \n", num);
    
    for(i = 0; i<2;i++){  //poner num en lugar de 2

    //printf("Entro al for \n");

    strncpy( directory, record + 24 + (i*12), 12 );  //voy buscando los datos de 12 en 12, porque
    //el directorio tiene longitud 12 para cada tag.
	
    strncpy( aux, directory, 3 );  //guardo el tag, son los primeros 3 del directorio encontrado
    tag[i] = atoi(aux);
    printf("tag: %d \n", tag[i]);

    strncpy( aux, directory + 3 , 4 ); //guardo el largo del dato, después del tag, los siguientes 4
    //me dicen el largo del dato.
    largo[i] = atoi(aux);
    printf("largo: %d \n", largo[i]);

    strncpy( aux, directory + 7 , 5 ); //guardo la ubicacion del dato, después del tag y del largo,
    //(3+4), está la ubicación/posición del dato
    ubicacion[i] = atoi(aux);
    printf("ubicacion: %d \n", ubicacion[i]);
    }
    
    for(int j = 0;j<=1;j++){

    //printf("%c \t",tag[j]);   //imprimo el tag, para ver si corresponde al dato

    if (tag[j] == 500) {
        strncpy( aux, record + ubicacion[j] /* + (i*12)*/  + 24, largo[j] ); //busco el dato (+24 para saltarse la etiqueta)
        printf ("\n *********************** ISBN: %s \n", aux);
    }

	

	strncpy( aux, record + ubicacion[j] + (i*12)  + 24, largo[j] ); //busco el dato

	//for(int p = 0;p<largo[j];p++) //imprimo el dato
	//printf("%c",aux[p]);
	
	//printf("\n");
    }
}
