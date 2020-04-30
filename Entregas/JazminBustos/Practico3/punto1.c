#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main(){

int fd;
int i = 1;


while(i != 0){


fd = open("texto.txt", O_RDONLY);


if (fd == -1) {

		sleep(1);

	} else {
		return 0;
	}

}
}
