//Sistemas Operativos - Archivo estructurado
//------------------------------------------
//ISO2709 - MARC21 Reader
//More info: http://www.loc.gov/marc/specifications/specrecstruc.html

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 99999

void process_record(char *record, int record_length);

int main() {
    int fd;
    char buff[MAX];
    char record[MAX];
    char length[6];
    int record_length;
    int num_records = 0;

    fd = open("osbooks.iso2709", O_RDONLY); /*read file*/
    if (fd == -1) {
        printf("ERROR. Can't read file. \n");
        exit(1);
    }

    while (read(fd, length, 5)) {
        num_records++;
        record_length = atoi(length);
        printf("Record %d, Length = %d\n", num_records, record_length); /* Record length (character positions 00-04) */
        strcpy(record, length);
        read(fd, buff, record_length - 5);
        strcat(record, buff);
        process_record(record, record_length);
    }

    close(fd);
    return 0;
}

void process_record(char *record, int record_length) {
    char leader[25];
    char directory[MAX];
    char data[MAX];
    char base_data_s[6];
    int base_data;


    printf("***LEADER INFO***\n");

    strncpy(data, record + 5, 1);
    data[1] = '\0';
    printf("Record Status: %s\n", data); /*Record status (character position 05)*/

    strncpy(data, record + 6, 1);
    data[1] = '\0';
    printf("Type of Record: %s\n", data); /*Type of record (character position 06)*/

    strncpy(data, record + 7, 2);
    data[2] = '\0';
    printf("Implementation-defined: %s\n", data); /*Implementation-defined (character positions 07-08)*/

    strncpy(data, record + 9, 1);
    data[1] = '\0';
    printf("Character coding scheme: %s\n", data); /*Character coding scheme (character position 09),*/

    strncpy(data, record + 10, 1);
    data[1] = '\0';
    printf("Indicator count: %s\n", data); /*Indicator count (character position 10)*/

    strncpy(data, record + 11, 1);
    data[1] = '\0';
    printf("Subfield code length: %s\n", data); /*Subfield code length (character position 11)*/

    strncpy(base_data_s, record + 12, 5);
    base_data_s[5] = '\0';
    base_data = atoi(base_data_s);
    printf("Base address of data: %s\n", base_data_s); /*Base address of data (character positions 12-16)*/

    strncpy(data, record + 17, 3);
    data[3] = '\0';
    printf("Implementation-defined: %s\n", data); /*Implementation-defined (character positions 17-19)*/

    strncpy(data, record + 20, 4);
    data[4] = '\0';
    printf("Entry map: %s\n", data); /*Entry map (character positions 20-23)*/

    printf("***DIRECTORY INFO***\n");


    int a = 0; /*counter*/

    do {
        /*Tag (character positions 00-02)*/
        strncpy(data, record + 24 + a, 3);
        data[3] = '\0';
        printf("%s\t", data);
        a = a + 3;

        /*Length of field (character positions 03-06)*/
        strncpy(data, record + 24 + a, 4);
        data[4] = '\0';
        int data_length = atoi(data);
        a = a + 4;

        /* Starting character position (character positions 07-11) */
        strncpy(data, record + 24 + a, 5);
        data[5] = '\0';
        int data_start = atoi(data);
        a = a + 5;

        /*showing data*/
        strncpy(data, record + data_start, data_length);
        data[data_length + 1] = '\0';
        printf("%s\n", data);

    } while (a < (base_data - 25));

    printf("\n\n\n\n");

}

