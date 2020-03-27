#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main(){

system("cd");  //me voy a la raiz
system("touch archivo.txt"); //si no llega a existir creo el archivo "archivo.txt"
system("ls -l ./* > archivo.txt"); //copio el nombre de las carpetas y archivos de "/" en "archivo.txt"


int fd;
char buf[1000];
ssize_t nr_bytes;





fd = open("archivo.txt", O_RDONLY); //  "O_RDONLY" me indica que solo hago lectura

if(fd == -1){

printf("Error ar leer el archivo");

}else{


nr_bytes = read(fd,buf,500); //Extraigo el contenido de "archivo.txt" , "solo los primeros 500 bytes de texto"
close((int)fd); //Muestro los archivos dentro de "/"

printf(buf);
}

}
