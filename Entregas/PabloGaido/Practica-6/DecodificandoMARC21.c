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
    int  tag[99];
    int  ubicacion[99];
    int largo[99];
    char aux[999]; 
    int i = 0;
    int corte = 0;

    strncpy ( leader, record, 24 );
    leader[25] = '\0';
    printf( "Leader: %s\n", leader );
    
    
    for(i = 0; i<20 /*(corte >= 0)&&(corte <= 9)*/;i++){  //leo mientras haya direcciones de datos, por defecto hay 20

    strncpy( directory, record + 24 + (i*12), 12 );  //voy buscando los datos de 12 en 12
	
    strncpy( aux, directory, 3 );  //guardo el tag
    tag[i] = atoi(aux);

    strncpy( aux, directory + 3 , 4 ); //guardo el largo del dato
    largo[i] = atoi(aux);

    strncpy( aux, directory + 7 , 5 ); //guardo la ubicacion del dato
    ubicacion[i] = atoi(aux);

    // strncpy( aux, directory + 13 , 1 ); //establezco punto de corte..... en proceso
    //corte = atoi(aux);

    }

    
    for(int j = 0;j<= i;j++){
	printf("%i\t",tag[j]);   //imprimo el tag
	strncpy( aux, record + ubicacion[j] + (i*12)  + 24, largo[j] ); //busco el dato

	for(int p = 0;p<largo[j];p++) //imprimo el dato
	printf("%c",aux[p]);
	
	printf("\n");
    }
}
