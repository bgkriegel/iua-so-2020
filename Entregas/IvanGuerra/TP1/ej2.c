#include <stdio.h>

int main()
{
  int pid;
  pid = fork();

  if (pid == -1)
  {
    printf("Error al crear el proceso hijo\n");
    return 1;
  }

  if (pid == 0)
  {
    // Proceso hijo
    printf("Soy el proceso hijo :)\n");
  }
  else
  {
    // Proceso padre
    printf("Soy el proceso padre :)\n");
  }

  return 0;
}