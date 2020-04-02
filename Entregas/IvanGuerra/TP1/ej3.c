#include <stdio.h>
#include <unistd.h>

int main()
{
  int pid;
  pid = fork();

  if (pid == -1)
  {
    printf("Error al crear el proceso hijo\n");
    return 1;
  }

  // La funcion getpid() retorna el valor del PID del proceso que llama a la funcion.
  // La funcion getppid() retorna el valor del PID del proceso padre del proceso que llama a la funcion.

  // Cuando se llama a fork(), en el proceso hijo la llamada al metodo getppid()
  // retorna el mismo valor que la llamada a la funcion getpid() en el proceso padre.

  if (pid == 0)
  {
    // Proceso hijo (Nuevo proceso creado)
    printf("Soy el proceso hijo. Mi PID es %d y el PID de mi padre es %d.\n", getpid(), getppid());
  }
  else
  {
    // Proceso padre (Proceso que creo el nuevo proceso)
    printf("Soy el proceso padre. Mi PID es %d y el PID de mi padre es %d.\n", getpid(), getppid());
  }

  return 0;
}