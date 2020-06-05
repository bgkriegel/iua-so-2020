/**************************************************************\
  Autor: Ivan Guerra
  Practico: 6
  Objetivo: Archivo estructurado.
  - Aprender a leer un archivo estructurado.
  - Se utilizará como ejemplo un archivo en formato ISO2709. Es un
  formato desarrollado para almacenar información bibliográfica, y se corresponde
  con el formato MARC21 que es utilizado en la Argentina. 
  - La relevancia para el tema de archivos es que se puede ver a un registro
  MARC21 como un mini-filesystem, con entradas de directorio de tamaño fijo
  y bloques de datos variables.
  - Un registro MARC21 se puede ver como lo siguiente:

  01030nam a22002657a 4500
  003 AR_CdUFM
  005 20160503150707.0
  008 111121s2015    nju||||| |||| 00| 0 eng d
  020    $a 013359162X
  020    $a 9780133591620
  040    $a AR_CdUFM $c AR_CdUFM
  100 1  $a Tanenbaum, Andrew S., $d 1944-
  245 10 $a Modern operating systems / $c Andrew S. Tanenbaum, Herbert Bos.
  250    $a 4a ed.
  260    $a New Jersey :  $b Pearson Education,  $c 2015.
  300    $a xxvi, 2001 p. : $b il. ; $c 25 cm.

  Podemos observar:
  1) Cabecera de 21 chars contando espacios
  2) Campos (003,005,...,300)
  3) Subcampos
    003 ninguno
    020 uno ($a)
    260 tres ($a,$b,$c)
  
  - Escribir un programa que lea e interprete el archivo de ejemplo osbooks.iso2709.
  - Procesar el archivo e imprimir su información.
 Fecha: 03/06/2020
\**************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "hashtable.c"

#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux. */

#define MAX 99999
#define HT_SIZE 65536

hashtable_t *hrs, *hrt, *hrbl, *hdt;

void  process_record ( char *record, int record_length );
void  process_leader ( char *leader );
int   get_base_data( char *leader );
void  process_directory ( char *directory );
char* get_directory_tag( char *directory, int position );
bool  should_tag_be_displayed ( char *tag );

int main() {
  char *filenameA = "osbooks.iso2709";
  int num_records = 0;
  int record_length = 0;
  char buff[ MAX ];
  char record[ MAX ];
  
  char length[6];

  int fdA = open(filenameA, O_RDONLY);

  if (fdA < 0) {
    printf("Hubo un error al leer el archivo '%s'\nSaliendo del programa...\n", filenameA);
    exit(EXIT_FAILURE);
  }

  // Creo estructura de tabla hash para los estados del registro
  hrs = ht_create( HT_SIZE );
  ht_set( hrs, "n", "Nuevo" );

  // Creo estructura de tabla hash para los tipos de registro
  hrt = ht_create( HT_SIZE );
  ht_set( hrt, "a", "Material textual" );

  // Creo estructura de tabla hash para los niveles bibliograficos del registro
  hrbl = ht_create( HT_SIZE );
  ht_set( hrbl, "m", "Monografía" );

  // Creo estructura de tabla hash para los tipos de etiqueta de un directorio
  hdt = ht_create( HT_SIZE );
  ht_set( hdt, "020", "ISBN" );
  ht_set( hdt, "100", "Autor" );
  ht_set( hdt, "245", "Título" );
  ht_set( hdt, "250", "Edición" );

  while ( read( fdA, length, 5 ) ) {
    num_records++;
    record_length = atoi( length );
    printf( "Registro #%d, Longitud = %d\n", num_records, record_length );
    strcpy( record, length );
    read( fdA, buff, record_length - 5 );
    strcat( record, buff );
    process_record ( record, record_length );
    printf( "Fin del registro #%d\n", num_records);
    printf( "-------------------\n\n" );
  }

  close(fdA);

	return EXIT_SUCCESS;
}

void process_record ( char *record, int record_length ) {
  char leader[25];
  char directory[MAX];

  // char data[ MAX ];

  strncpy ( leader, record, 24 );

  printf( "\n\tLeader: %s\n", leader );
  printf( "\t--------------------------------\n" );

  process_leader(leader);
  int base_data = get_base_data(leader);

  strncpy( directory, record + 24, base_data - 25 );

  printf( "\n\tDirectory: %s\n", directory );
  printf( "\t--------------------------------------------------------------------------------------------------------------------------\n" );

  process_directory(directory);
 
  printf( "\n" );
}

void process_leader ( char *leader ) {
  char key[1];
  
  key[0] = leader[5];
  printf("\n\tEstado del registro: \t\t\t%s\n", ht_get( hrs, key ));

  key[0] = leader[6];
  printf("\tTipo de registro: \t\t\t%s\n", ht_get( hrt, key ));
  
  key[0] = leader[7];
  printf("\tNivel bibliográfico: \t\t\t%s\n", ht_get( hrbl, key ));

  int base_data_position = get_base_data( leader );
  printf("\tPosición de inicio de los datos: \t%d\n", base_data_position );
}

int get_base_data( char *leader ) {
  char base_data_position_s[5];

  for ( int i = 0; i < 5; i++ ) {
    base_data_position_s[i] = leader[i+12];
  }

  return atoi( base_data_position_s );
}

void process_directory ( char *directory ) {
  char *tag;
  int directory_size = 12;

  for (int i = 0; i < strlen(directory) / directory_size; i++) {
    tag = get_directory_tag( directory, 12 * i);
    if (should_tag_be_displayed(tag)) printf("\n\tEtiqueta encontrada: \t%s => %s\n", tag, ht_get( hdt, tag ));
  }
}

char* get_directory_tag ( char *directory, int position ) {
  char tag[4];
  char c;
  char *tag_s = (char *) malloc(4);

  for ( int i = 0; i < 3; i++ ) {
    c = directory[position + i];
    tag[i] = c;
  }

  tag[3] = '\0';

  strcpy(tag_s, tag);

  return tag_s;
}

bool should_tag_be_displayed ( char *tag ) {
  return ( ht_get( hdt, tag ) != NULL );
}

// Para compilar: gcc -Wall -o proc_archivo_estruct proc_archivo_estruct.c
// Para ejecutar: ./proc_archivo_estruct