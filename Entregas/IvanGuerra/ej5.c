#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
  int pid;
  int status;
  pid = fork();

  if (pid == -1)
  {
    printf("Error al crear el proceso hijo\n");
    return 1;
  }

  if (pid == 0)
  {
    // Proceso hijo (Nuevo proceso creado)

    printf("\nDatos del proceso hijo\n");
    printf("-----------------------\n\n");

    printf("Soy el proceso hijo. Mi PID es %d y el PID de mi padre es %d.\n\n", getpid(), getppid());

    while (1)
    {
      printf("Estoy esperando indefinidamente en el proceso hijo...\n");
      sleep(3);
    }
  }
  else
  {
    // Proceso padre (Proceso que creo el nuevo proceso)
    wait(&status);

    if (WIFEXITED(status))
    {
      printf("El proceso hijo termino con normalidad con el estado de salida %d.\n", status);
      WEXITSTATUS(status);
    }
    else
    {
      printf("\nHubo un error. El proceso hijo termino con el estado de salida %d (%s).\n", status, strsignal(status));
      return -1;
    }
  }

  return 0;
}