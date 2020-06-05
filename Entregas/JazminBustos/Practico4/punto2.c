#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
void main()
{
	pid_t pid_hijo1, pid_hijo2;
	pid_hijo1 = fork();
	int pd[2];
	pipe(pd);
	char buff[256] =
		{ 'H', 'o', 'l', 'a', ' ', 'h', 'e', 'r', 'm', 'a', 'n', 'o' };

	if (pid_hijo1 == 0) {
		printf("Soy el hijo 1, Mi padre es= %d, Mi PID= %d\n", getppid(),
			   getpid());
		close(pd[0]);
		write(pd[1], buff, strlen(buff));
		close(pd[1]);
		exit(0);
	}


	pid_hijo2 = fork();
	if (pid_hijo2 == 0) {
		char buf[256];
		printf("Soy el hijo 2, Mi padre es= %d, Mi PID= %d\n", getppid(),
			   getpid());
		sleep(1);
		close(pd[1]);
		read(pd[0], buf, 256);
		close(pd[0]);
		printf(buf);
	}

	sleep(2);
	printf("Proceso PADRE = %d\n", getpid());
	exit(0);
}
