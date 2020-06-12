#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void procesarRegistro (char *registro, int largoRegistro);

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
   printf ("\nLa cabecera es: %s\n", cabecera);
   strncpy (datosBase, registro + 12, 5);
   datosBase [6] = '\0';
   printf ("Los datos base comienzan en: %s\n", datosBase);
   datoBase = atoi (datosBase);
   strncpy (directorio, registro + 24, datoBase - 25);
   directorio [datoBase - 24] = '\0';
   printf ("El directorio es: %s\n\n", directorio);

   int nTag = strlen(directorio) / 12; 
   printf("****************** %d \n", nTag);
   printf ("%d\n", datoBase);

   for(i = 0; i<nTag;i++){  
      strncpy( directorio, registro + 24 + (i*12), 12 ); 
      for (size_t i = 0; i < 5; i++)
         aux [i] = ' ';
      strncpy( aux, directorio, 3 );
      tag[i] = atoi(aux);
      printf("tag: %d \n", tag[i]);
      strncpy( aux, directorio + 3 , 4 );
      tamanio[i] = atoi(aux);
      printf( "tamaño: %d \n", tamanio[i]);
      strncpy( aux, directorio + 7 , 5 );
      ubicacion[i] = atoi(aux) + datoBase;
      printf("ubicacion: %d \n", ubicacion[i]);
   }

   for(int j = 0; j < nTag; j++)
      strncpy( aux, registro + ubicacion[j] + 24 + strlen(directorio), tamanio[j] );

   for(int p = 0;p<tamanio[j];p++)
      printf("%c",aux[p]);

   printf ("\n");
      
}

int main(){

	int fd;
	char largoAux[6];
	int tamanio;
	char buffer [99999];
	char registro [ 99999 ];

	fd = open( "osbooks.iso2709", O_RDONLY );
   if (fd == -1) {
      printf( "Error de lectura\n");
      exit(1);
   } 

   while ( read( fd, largoAux, 5 ) ) {

      tamanio = atoi( largoAux );
      strcpy( registro, largoAux );
      read( fd, buffer, tamanio - 5 );
      strcat( registro, buffer );
      procesarRegistro ( registro, tamanio );
      return 0;
   }
}