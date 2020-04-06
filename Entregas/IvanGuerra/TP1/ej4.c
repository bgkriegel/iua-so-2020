#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

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

    printf("Soy el proceso hijo. Mi PID es %d y el PID de mi padre es %d.\n", getpid(), getppid());
  }
  else
  {
    // Proceso padre (Proceso que creo el nuevo proceso)
    wait(&status);

    printf("\nDatos del proceso padre\n");
    printf("-----------------------\n\n");

    if (WEXITSTATUS(status) == 0)
    {
      printf("El proceso hijo termino con el estado de salida %d (EXITO)\n", WEXITSTATUS(status));
    }
    else
    {
      printf("El proceso hijo termino con el estado de salida %d (SIN EXITO)\n", WEXITSTATUS(status));
    }

    printf("Soy el proceso padre. Mi PID es %d y el PID de mi padre es %d.\n", getpid(), getppid());
  }

  return 0;
}