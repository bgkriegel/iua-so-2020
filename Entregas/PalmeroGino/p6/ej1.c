#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#define MAX 99999
int convertToInt(char a[], int i){
	int resultado=0, contador=1;

	for(;i!=0;i--){
		resultado=resultado+( (a[i-1] - '0')*(contador));
		contador*=10;
	}
	return resultado;
}
int main(int argc, char *argv[]) {
	int fil=open("osbooks.iso2709",O_RDONLY), bytes_read=0;
	unsigned char buffer[MAX]; 
	struct marcH {
   		int record_length;
   		unsigned char record_status[1];
   		unsigned char type_of_record[1];
   		unsigned char implementation_defined[2];
   		unsigned char character_coding_scheme[1];
   		int indicator_count;
   		int subfield_code_length;
   		int base_address_of_data;
   		unsigned char implementation_defined_B[3];
   		unsigned char entry_map[4];
	};
	struct marcH marcLeader;
	char temp[5];
	int offsetA, min, offset;
	while ( read( fil, temp, 5 ) ) {
		offsetA=0;
		marcLeader.record_length=convertToInt(temp,5);
		bytes_read = bytes_read + read(fil, buffer, 19);
		//Guardo los datos del LEADER
		
		
		strncpy(marcLeader.record_status, buffer, 1);
		strncpy(marcLeader.type_of_record, buffer+1, 1);
		strncpy(marcLeader.implementation_defined, buffer+2, 2);
		strncpy(marcLeader.character_coding_scheme, buffer+4, 1);
		strncpy(temp, buffer+5, 1);
		marcLeader.indicator_count=convertToInt(temp,1);
		strncpy(temp, buffer+6, 1);
		marcLeader.subfield_code_length=convertToInt(temp,1);
		strncpy(temp, buffer+7, 5);
		marcLeader.base_address_of_data=convertToInt(temp,5);
		strncpy(marcLeader.implementation_defined_B, buffer+12, 3);
		strncpy(marcLeader.entry_map, buffer+15, 4);
		
		//Imprimo los datos del LEADER
		printf("Record length: %i", marcLeader.record_length);
		printf("\nRecord status: %.1s", marcLeader.record_status);
		printf("\nType of Record: %.1s", marcLeader.type_of_record);
		printf("\nImplementation-defined: %.2s", marcLeader.implementation_defined);
		printf("\nCharacter coding scheme: %.1s", marcLeader.character_coding_scheme);
		printf("\nIndicator count: %i", marcLeader.indicator_count);
		printf("\nSubfield code length: %i", marcLeader.subfield_code_length);
		printf("\nBase address of data: %i", marcLeader.base_address_of_data);
		printf("\nImplementation-defined: %.3s", marcLeader.implementation_defined_B);
		printf("\nEntry map: %.4s\n", marcLeader.entry_map);
		
		//-------------------------------------------------------------------------
		
		
		int largoDelCampo, posicionDeInicio;
		unsigned char tag[3];
		int cont=0;
			bytes_read = read(fil, buffer, marcLeader.record_length-25);
			
			offset=marcLeader.base_address_of_data-25;//guardo el offset de los datos
			//Leo registros
			do{	
				//leo y seteo parametros de la fila
				strncpy(tag, buffer+offsetA, 3);

				strncpy(temp, buffer+offsetA+3, 4);
				largoDelCampo=convertToInt(temp,4);
				
				strncpy(temp, buffer+offsetA+8, 5);
				posicionDeInicio=convertToInt(temp,5);
				
				offsetA=offsetA+12;				

				//Leo e imprimo valores de la fila
				
				printf("%.3s\t", tag);
				min=offset;
				offset=offset+1;
				for(; offset<min+largoDelCampo; offset++){
					if(buffer[offset]==''){
						offset=offset+1;
						printf(" $");
						printf("%c", buffer[offset]);
						printf(" ");
					}else{
						printf("%c", buffer[offset]);
					}
				}
				printf("\n");
				
			}while(offsetA<marcLeader.base_address_of_data-25);
			



			bytes_read = read(fil, buffer, 1);//corrijo offset

			
			
	}
	fil=close(fil);
}
