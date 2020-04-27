#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int pid;

    pid = fork();

    if (pid == 0) {
        printf("I'm the son.\n");
    } else {
        printf("This is the father.\n");
    }
    return 0;
}