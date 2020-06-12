#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 99999

void process_record(char *record, int record_length);

int main()
{
	int fd;
	char buff[MAX];
	char record[MAX];
	char length[6];
	int record_length;
	int num_records = 0;

	fd = open("osbooks.iso2709", O_RDONLY);
	if (fd == -1) {
		printf("Error de lectura\n");
		exit(1);
	}

	while (read(fd, length, 5)) {
		num_records++;
		record_length = atoi(length);
		printf("Record %d, Length = %d\n", num_records, record_length);
		strcpy(record, length);
		read(fd, buff, record_length - 5);
		strcat(record, buff);
		process_record(record, record_length);
		/*printf( "Record: %s\n", record ); */
	}

	close(fd);
	return 0;
}

void process_record(char *record, int record_length)
{
	char leader[25];
	char directory[MAX];
	char data[MAX];
	char base_data_s[6];
	int base_data;

	strncpy(leader, record, 24);
	leader[25] = '\0';
	printf("Leader: %s\n", leader);

	strncpy(base_data_s, record + 12, 5);	//(12, 13, 14, 15, 15) --> donde empiezan los datos
	base_data_s[6] = '\0';
	base_data = atoi(base_data_s);	//paso al valor numérico la posición donde empiezan los datos
	printf("base: %s\n", base_data_s);

	strncpy(directory, record + 24, base_data - 25);	//los primeros 24 son la cabecera, la salteo. Copio n caracteres
	//n = la direccion donde empiezan los datos - 25 --> Guardo en directory TODO lo que sea directorio
	directory[base_data - 25 + 1] = '\0';	// ???
	printf("Directory: %s\n", directory);
	printf("\n");
}
