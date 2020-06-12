#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int int main() {

    int pid1, pid2, pid3, pd[2],a_inout, b_inout;
    pipe(pd);
    a_inout = creat("a-inout.txt", 0644);
	b_inout = creat("b-inout.txt", 0644);
    pid2 = fork();

    if(pid3==0) {
        printf("Soy el hijo 2, mi padre es= %d, mi pid es: %d\n",getppid(), getpid());
        char buf[256] = { 's', 'o', 'y', ' ', 'a', '-', 'i', 'n', 'o', 'u', 't' };
        a_inout = open("a-inout.txt", O_WRONLY, 0644);
		b_inout = open("b-inout.txt", O_WRONLY, 0644);
        write(a_inout, buf, strlen(buf));    
		buf[4] = 'b';
		write(b_inout, buf, strlen(buf));
        close(a_inout);
        close(b_inout);
    }

    pid3 = fork(); 
    
    if(pid2==0) {
        char = buf[256];
        printf("Soy hijo 1, mi padre es= %d, mi pid es: %d\n", getppid(), getpid());
        sleep(2);
        a_inout = open("a-inout.txt", O_RDONLY, 0644);
		b_inout = open("b-inout.txt", O_RDONLY, 0644);
        read(a_inout, &buf, 256);
        close(a_inout);
        printf(buf);
        read(b_inout, %buf, 256);
        close(b_inout);
        printf(buf)
        return 0;
    }
    return 0;
}